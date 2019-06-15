#include "Character.h"
#include "misc/utils.h"
#include "2D/Transformations.h"
#include "2D/Geometry.h"
#include "Game.h"
#include "Navigation/PathPlanner.h"
#include "SteeringBehaviors.h"
#include "UserOptions.h"
#include "Time/Regulator.h"
#include "WeaponSystem.h"
#include "SensoryMemory.h"
#include "TextureManager.h"
#include "Messaging/Telegram.h"
#include "Messages.h"
#include "Messaging/MessageDispatcher.h"
#include "Scriptor.h"
#include "Goals/Goal_Types.h"
#include "Goals/Goal_Think.h"
#include "Goals/Goal_Think_Zombie.h"
#include "InputHandler.h"
//#define debug

//-------------------------- ctor ---------------------------------------------
Character::Character(Game* world,Vector2D pos):

  MovingEntity(pos,
               script->getNum("charscale"),
               Vector2D(0,0),
               script->getNum("charmaxspeed"),
               Vector2D(1,0),
               script->getNum("charmass"),
               Vector2D(script->getNum("charscale"),script->getNum("charscale")),
	       script->getNum("charmaxheadturnrate"),
		 script->getNum("charmaxforce")),
                 
	       m_iMaxHealth(script->getInt("charmaxhealth")),
	       m_iHealth(script->getInt("charmaxhealth")),
                 m_pPathPlanner(NULL),
                 m_pSteering(NULL),
                 m_pWorld(world),
                 m_pBrain(NULL),
	       m_iNumUpdatesHitPersistant((int)(FrameRate * script->getNum("hitflashtime"))),
                 m_bHit(false),
                 m_iScore(0),
                 m_Status(spawning),
                 m_bPossessed(false),
  m_dFieldOfView(DegsToRads(script->getNum("charfov")))
           
{
  SetEntityType(type_bot);

  SetUpVertexBuffer();
  
  //a bot starts off facing in the direction it is heading
  m_vFacing = m_vHeading;

  //create the navigation module
  m_pPathPlanner = new PathPlanner(this);

  //create the steering behavior class
  m_pSteering = new Steering(world, this);

  //create the regulators
  m_pWeaponSelectionRegulator = new Regulator(script->getNum("weaponselectionfrequency"));
  m_pGoalArbitrationRegulator =  new Regulator(script->getNum("goalappraisalupdatefreq"));
  m_pTargetSelectionRegulator = new Regulator(script->getNum("targetingupdatefreq"));
  m_pTriggerTestRegulator = new Regulator(script->getNum("triggerupdatefreq"));
  m_pVisionUpdateRegulator = new Regulator(script->getNum("visionupdatefreq"));

  
  
  //create the goal queue
  m_pBrain = new Goal_Think(this);

  //create the targeting system
  m_pTargSys = new TargetingSystem(this);

  m_pWeaponSys = new WeaponSystem(this,
                                        script->getNum("charreactiontime"),
                                        script->getNum("charaimaccuracy"),
					script->getNum("charaimpersistance"));

  m_pSensoryMem = new SensoryMemory(this, script->getNum("charmemoryspan"));
}





//-------------------------------- dtor ---------------------------------------
//-----------------------------------------------------------------------------
Character::~Character()
{
  std::cout << "deleting  bot (id = " << ID() << ")" << "";
 
  delete m_pBrain;
  delete m_pPathPlanner;
  delete m_pSteering;
  delete m_pWeaponSelectionRegulator;
  delete m_pTargSys;
  delete m_pGoalArbitrationRegulator;
  delete m_pTargetSelectionRegulator;
  delete m_pTriggerTestRegulator;
  delete m_pVisionUpdateRegulator;
  delete m_pWeaponSys;
  delete m_pSensoryMem;
}

//-------------------------------load-------------------------
//
//---------------------------------------------------
void Character::load()
{
  m_bTag = false;
  SetID(GetNextValidID());
  m_vHeading = Vector2D(1,0);
  m_vVelocity = Vector2D(0,0);
  m_dMass = script->getNum("charmass");
  m_vSide = m_vHeading.Perp();
  m_dMaxSpeed = script->getNum("charmaxspeed");
  m_dMaxTurnRate = script->getNum("charmaxheadturnrate");
  m_dMaxForce = script->getNum("charmaxforce");
  m_iMaxHealth = script->getInt("charmaxhealth");
  m_pWorld = Game::Instance();
  m_iNumUpdatesHitPersistant = (int)(FrameRate * script->getNum("hitflashtime"));
  m_bHit = false;
  m_iScore = 0;
  m_Status = spawning;
  m_bPossessed = false;
  m_dFieldOfView = DegsToRads(script->getNum("charfov"));
  m_vPosition = Vector2D(100,100);
  m_dBoundingRadius = script->getNum("charscale");
  m_vScale = Vector2D(m_dBoundingRadius,m_dBoundingRadius);
  SetEntityType(type_bot);
  SetUpVertexBuffer();
  m_vFacing = m_vHeading;
  m_pPathPlanner = new PathPlanner(this);
  m_pSteering = new Steering(Game::Instance(), this);
  m_pWeaponSelectionRegulator = new Regulator(script->getNum("weaponselectionfrequency"));
   m_pGoalArbitrationRegulator =  new Regulator(script->getNum("goalappraisalupdatefreq"));
  m_pTargetSelectionRegulator = new Regulator(script->getNum("targetingupdatefreq"));
  m_pTriggerTestRegulator = new Regulator(script->getNum("triggerupdatefreq"));
  m_pVisionUpdateRegulator = new Regulator(script->getNum("visionupdatefreq"));
  //create the goal queue
  m_pBrain = new Goal_Think(this);

  //create the targeting system
  m_pTargSys = new TargetingSystem(this);

  m_pWeaponSys = new WeaponSystem(this,
                                        script->getNum("charreactiontime"),
                                        script->getNum("charaimaccuracy"),
					script->getNum("charaimpersistance"));

  m_pSensoryMem = new SensoryMemory(this, script->getNum("charmemoryspan"));
}


//-------------------------------draw------------------------
//
//-----------------------------------------------------------
void Character::draw()
{
    TextureManager::Instance()->drawFrame("isaac",  m_vPosition.x, m_vPosition.y, 148, 125,0,0, Game::Instance()->getRenderer(),0,100);
}


//------------------------------- Spawn ---------------------------------------
//
//  spawns the bot at the given position
//-----------------------------------------------------------------------------
void Character::Spawn(Vector2D pos)
{
#ifdef debug
    std::cout << "Bot Spawning";
    #endif
    SetAlive();
    m_pBrain->RemoveAllSubgoals();
    m_pTargSys->ClearTarget();
    SetPos(pos);
    m_pWeaponSys->Initialize();
    RestoreHealthToMaximum();

}
//-------------------------------- Update -------------------------------------
//
void Character::Update()
{


  
  //process the currently active goal. Note this is required even if the bot
  //is under user control. This is because a goal is created whenever a user 
  //clicks on an area of the map that necessitates a path planning request.
  m_pBrain->Process();
   //if the bot is under AI control but not scripted
  if (isPossessed())
    {
      handleinput();
    }

 
  //Calculate the steering force and update the bot's velocity and position
  //UpdateMovement();


  if(!isPossessed())
    {          
    //examine all the opponents in the bots sensory memory and select one
    //to be the current target
    if (m_pTargetSelectionRegulator->isReady())
      {      
      m_pTargSys->Update();
    }

    //appraise and arbitrate between all possible high level goals
    if (m_pGoalArbitrationRegulator->isReady())
    {
       m_pBrain->Arbitrate(); 
    }

    //update the sensory memory with any visual stimulus
    if (m_pVisionUpdateRegulator->isReady())
    {
      m_pSensoryMem->UpdateVision();
    }
  
    //select the appropriate weapon to use from the weapons currently in
    //the inventory
    //  if (m_pWeaponSelectionRegulator->isReady())
    // {      
    //    m_pWeaponSys->SelectWeapon();       
    //  }

    //this method aims the bot's current weapon at the current target
    //and takes a shot if a shot is possible
   
    m_pWeaponSys->TakeAimAndShoot();
  }
}

//--------------------------HandleInput----------------------------------------
//
//
//
Vector2D Character::handleinput()
{
  Vector2D force;
  TheInputHandler::Instance()->update();
  if (!isDead())
    { 
      if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_SPACE))
	{
	  //FireWeapon(Pos());
	}
      
       if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_W))
        {
	 
           force.y = -1;
        }
        if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_S))
        {
	 
            force.y = 1;
        }
	 if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_A))
        {
	 
           force.x = -1;
        }
	  if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_D))
        {
	 
           force.x=1;
        }
	  force.Normalize();
    }
  return force - Velocity();
}




//------------------------- UpdateMovement ------------------------------------
//
//  this method is called from the update method. It calculates and applies
//  the steering force for this time-step.
//-----------------------------------------------------------------------------
void Character::UpdateMovement()
{
  //calculate the combined steering force
  Vector2D force = m_pSteering->Calculate();

  //if no steering force is produced decelerate the player by applying a
  //braking force
  if (m_pSteering->Force().isZero())
  {
    const double BrakingRate = 0.8; 

    m_vVelocity = m_vVelocity * BrakingRate;                                     
  }

  //calculate the acceleration
  Vector2D accel = force / m_dMass;

  //update the velocity
  m_vVelocity += accel;

  //make sure vehicle does not exceed maximum velocity
  m_vVelocity.Truncate(m_dMaxSpeed);

  //update the position
  m_vPosition += m_vVelocity;

  //if the vehicle has a non zero velocity the heading and side vectors must 
  //be updated
  if (!m_vVelocity.isZero())
  {    
    m_vHeading = Vec2DNormalize(m_vVelocity);

    m_vSide = m_vHeading.Perp();
  }
}
//---------------------------- isReadyForTriggerUpdate ------------------------
//
//  returns true if the bot is ready to be tested against the world triggers
//-----------------------------------------------------------------------------
bool Character::isReadyForTriggerUpdate()const
{
  return m_pTriggerTestRegulator->isReady();
}

//--------------------------- HandleMessage -----------------------------------
//-----------------------------------------------------------------------------
bool Character::HandleMessage(const Telegram& msg)
{
  
  //std::cout << "MSSAGE IS : " <<MessageToString(msg.Msg);
  //if (msg.Sender==NULL || msg.Receiver  == NULL) return false;
  //first see if the current goal accepts the message
  if (GetBrain()->HandleMessage(msg)) return true;
 
  //handle any messages not handles by the goals
  switch(msg.Msg)
  {
  case Msg_TakeThatMF:
     #ifdef debug
    std::cout << "HIT";
    #endif
    //just return if already dead or spawning
    if (isDead() || isSpawning()) return true;

    //the extra info field of the telegram carries the amount of damage
    ReduceHealth(DereferenceToType<int>(msg.ExtraInfo));

    //if this bot is now dead let the shooter know
    if (isDead())
    {
      Dispatcher->DispatchMsg(SEND_MSG_IMMEDIATELY,
                              ID(),
                              msg.Sender,
                              Msg_YouGotMeYouSOB,
                              NULL);
    }

    return true;

  case Msg_YouGotMeYouSOB:
    
    IncrementScore();
    
    //the bot this bot has just killed should be removed as the target
    m_pTargSys->ClearTarget();

    return true;

  case Msg_GunshotSound:

    //add the source of this sound to the bot's percepts
    GetSensoryMem()->UpdateWithSoundSource((Character*)msg.ExtraInfo);

    return true;

  case Msg_UserHasRemovedBot:
    {

      Character* pRemovedBot = (Character*)msg.ExtraInfo;

      GetSensoryMem()->RemoveBotFromMemory(pRemovedBot);

      //if the removed bot is the target, make sure the target is cleared
      if (pRemovedBot == GetTargetSys()->GetTarget())
      {
        GetTargetSys()->ClearTarget();
      }

      return true;
    }

  case Msg_OpenSesame:
    {
      std::cout << "OPEN SESAME";
    }
  default: return false;
  }
}

//------------------ RotateFacingTowardPosition -------------------------------
//
//  given a target position, this method rotates the bot's facing vector
//  by an amount not greater than m_dMaxTurnRate until it
//  directly faces the target.
//
//  returns true when the heading is facing in the desired direction
//----------------------------------------------------------------------------
bool Character::RotateFacingTowardPosition(Vector2D target)
{
  Vector2D toTarget = Vec2DNormalize(target - m_vPosition);

  double dot = m_vFacing.Dot(toTarget);

  //clamp to rectify any rounding errors
  Clamp(dot, -1, 1);

  //determine the angle between the heading vector and the target
  double angle = acos(dot);

  //return true if the bot's facing is within WeaponAimTolerance degs of
  //facing the target
  const double WeaponAimTolerance = 0.01; //2 degs approx

  if (angle < WeaponAimTolerance)
  {
    m_vFacing = toTarget;
    return true;
  }

  //clamp the amount to turn to the max turn rate
  if (angle > m_dMaxTurnRate) angle = m_dMaxTurnRate;
  
  //The next few lines use a rotation matrix to rotate the player's facing
  //vector accordingly
  C2DMatrix RotationMatrix;
  
  //notice how the direction of rotation has to be determined when creating
  //the rotation matrix
  RotationMatrix.Rotate(angle * m_vFacing.Sign(toTarget));	
  RotationMatrix.TransformVector2Ds(m_vFacing);

  return false;
}




//--------------------------------- ReduceHealth ----------------------------
void Character::ReduceHealth(unsigned int val)
{
  m_iHealth -= val;

  if (m_iHealth <= 0)
  {
    SetDead();
  }

  m_bHit = true;

  m_iNumUpdatesHitPersistant = (int)(FrameRate *script->getNum("hitflashtime"));
}

//--------------------------- Possess -----------------------------------------
//
//  this is called to allow a human player to control the bot
//-----------------------------------------------------------------------------
void Character::TakePossession()
{
  if ( !(isSpawning() || isDead()))
  {
    m_bPossessed = true;

    std::cout << "Player Possesses bot " << this->ID() << "";
  }
}
//------------------------------- Exorcise ------------------------------------
//
//  called when a human is exorcised from this bot and the AI takes control
//-----------------------------------------------------------------------------
void Character::Exorcise()
{
  m_bPossessed = false;

  //when the player is exorcised then the bot should resume normal service
  m_pBrain->AddGoal_Explore();
  
  std::cout << "Player is exorcised from bot " << this->ID() << "";
}




//---------------------------- FireWeapon -------------------------------------
//
//  fires the current weapon at the given position
//-----------------------------------------------------------------------------
void Character::FireWeapon(Vector2D pos)
{
  #ifdef debug
  std::cout << "Weapon fired";
  #endif
  m_pWeaponSys->ShootAt(pos);
}

//----------------- CalculateExpectedTimeToReachPosition ----------------------
//
//  returns a value indicating the time in seconds it will take the bot
//  to reach the given position at its current speed.
//-----------------------------------------------------------------------------
double Character::CalculateTimeToReachPosition(Vector2D pos)const
{
  return Vec2DDistance(Pos(), pos) / (MaxSpeed() * FrameRate);
}

//------------------------ isAtPosition ---------------------------------------
//
//  returns true if the bot is close to the given position
//-----------------------------------------------------------------------------
bool Character::isAtPosition(Vector2D pos)const
{
  const static double tolerance = 10.0;
  
  return Vec2DDistanceSq(Pos(), pos) < tolerance * tolerance;
}

//------------------------- hasLOSt0 ------------------------------------------
//
//  returns true if the bot has line of sight to the given position.
//-----------------------------------------------------------------------------
bool Character::hasLOSto(Vector2D pos)const
{
  return m_pWorld->isLOSOkay(Pos(), pos);
}

//returns true if this bot can move directly to the given position
//without bumping into any walls
bool Character::canWalkTo(Vector2D pos)const
{
  return !m_pWorld->isPathObstructed(Pos(), pos, BRadius());
}

//similar to above. Returns true if the bot can move between the two
//given positions without bumping into any walls
bool Character::canWalkBetween(Vector2D from, Vector2D to)const
{
 return !m_pWorld->isPathObstructed(from, to, BRadius());
}

//--------------------------- canStep Methods ---------------------------------
//
//  returns true if there is space enough to step in the indicated direction
//  If true PositionOfStep will be assigned the offset position
//-----------------------------------------------------------------------------
bool Character::canStepLeft(Vector2D& PositionOfStep)const
{
  static const double StepDistance = BRadius() * 2;

  PositionOfStep = Pos() - Facing().Perp() * StepDistance - Facing().Perp() * BRadius();

  return canWalkTo(PositionOfStep);
}

bool Character::canStepRight(Vector2D& PositionOfStep)const
{
  static const double StepDistance = BRadius() * 2;

  PositionOfStep = Pos() + Facing().Perp() * StepDistance + Facing().Perp() * BRadius();

  return canWalkTo(PositionOfStep);
}

bool Character::canStepForward(Vector2D& PositionOfStep)const
{
  static const double StepDistance = BRadius() * 2;

  PositionOfStep = Pos() + Facing() * StepDistance + Facing() * BRadius();

  return canWalkTo(PositionOfStep);
}

bool Character::canStepBackward(Vector2D& PositionOfStep)const
{
  static const double StepDistance = BRadius() * 2;

  PositionOfStep = Pos() - Facing() * StepDistance - Facing() * BRadius();

  return canWalkTo(PositionOfStep);
}



//------------------------- SetUpVertexBuffer ---------------------------------
//-----------------------------------------------------------------------------
void Character::SetUpVertexBuffer()
{
  //setup the vertex buffers and calculate the bounding radius
  const int NumBotVerts = 4;
  const Vector2D bot[NumBotVerts] = {Vector2D(-3, 8),
                                     Vector2D(3,10),
                                     Vector2D(3,-10),
                                     Vector2D(-3,-8)};

  m_dBoundingRadius = 0.0;
  double scale = script->getNum("charscale");
  
  for (int vtx=0; vtx<NumBotVerts; ++vtx)
  {
    m_vecBotVB.push_back(bot[vtx]);

    //set the bounding radius to the length of the 
    //greatest extent
    if (fabs(bot[vtx].x)*scale > m_dBoundingRadius)
    {
      m_dBoundingRadius = fabs(bot[vtx].x*scale);
    }

    if (fabs(bot[vtx].y)*scale > m_dBoundingRadius)
    {
      m_dBoundingRadius = fabs(bot[vtx].y)*scale;
    }
  }
}



void Character::RestoreHealthToMaximum(){m_iHealth = m_iMaxHealth;}

void Character::IncreaseHealth(unsigned int val)
{
  m_iHealth+=val; 
  Clamp(m_iHealth, 0, m_iMaxHealth);
}

