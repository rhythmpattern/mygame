#include "Game.h"
#include "ObjectEnumerations.h"
#include "SteeringBehaviors.h"
#include "Navigation/PathPlanner.h"
#include "Game/EntityManager.h"
#include "2D/WallIntersectionTests.h"
#include "Map.h"
#include "Door.h"
#include "UserOptions.h"
#include "SensoryMemory.h"
#include "WeaponSystem.h"
#include "Messaging/MessageDispatcher.h"
#include "Messages.h"
#include "GraveMarkers.h"
#include "Scriptor.h"
#include "Armory/Projectile.h"
#include "Armory/Projectile_Shot.h"
#include "Armory/Shooter.h"
#include "Goals/Goal_Think.h"
#include "Goals/Goal_Types.h"
#include "Player.h"
#include "InputHandler.h"
#include "Zombie.h"
#include "ProjectileManager.h"
#include "GraveManager.h"
#include "CharManager.h"

//uncomment to write object creation/deletion to debug console
#define  LOG


Game* Game::s_pInstance = 0;
//----------------------------- ctor ------------------------------------------
//-----------------------------------------------------------------------------
Game::Game():m_pSelectedBot(NULL),
                         m_bPaused(false),
                         m_bRemoveABot(false),
                         m_pMap(NULL),
                         m_pPathManager(NULL)
{
  GameObjectFactory::Instance()->registerType("Character" , new CharacterCreator());
  
 
   
   
}


//------------------------------ dtor ----------------------------------------
//-----------------------------------------------------------------------------
Game::~Game()
{
  Clear();
  delete m_pPathManager;
  delete m_pMap;
  
  GraveManager::Instance()->Clear();
  ProjectileManager::Instance()->Clear();
}


bool Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen){

  
 LoadMap("DM1.map");
    m_levelFiles.push_back("assets/test.xml");
   m_currentLevel = 1;

    
    Player* player = new Player(this, Vector2D());
    //switch the default steering behaviors on
   
    CharManager::Instance()->AddChar(player);
    //register the bot with the entity manager
     EntityMgr->RegisterEntity(player);

  
 int flags = 0;
 m_bRunning = true;
    // store the game width and height
    m_gameWidth = width;
    m_gameHeight = height;

   

    
    if(fullscreen)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }
    
    // attempt to initialise SDL
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
      std::cout << "SDL init success\n";
        // init the window
        m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, SDL_WINDOW_SHOWN);
        
        if(m_pWindow != 0) // window init success
        {
            std::cout << "window creation success\n";
            m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED);
            
            if(m_pRenderer != 0) // renderer init success
            {
                std::cout << "renderer creation success\n";
                SDL_SetRenderDrawColor(m_pRenderer,0,0,0,255);
            }
            else
            {
                std::cout << "renderer init fail\n";
                return false; // renderer init fail
            }
        }
        else
        {
            std::cout << "window init fail\n";
            return false; // window init fail
        }
    }
    else
    {
        std::cout << "SDL init fail\n";
        return false; // SDL init fail
    }


    // GameObjectFactory::Instance();
    
     m_pGameStateMachine = new GameStateMachine();
     m_pGameStateMachine->changeState(new PlayState());

   return true;

    
}



void Game::Render()
{
 

    	m_pGameStateMachine->render();

 
}




//---------------------------- Clear ------------------------------------------
//
//  deletes all the current objects ready for a map load
//-----------------------------------------------------------------------------
void Game::Clear()
{
#ifdef LOG
    std::cout << "\n------------------------------ Clearup -------------------------------" << endl;
#endif

    CharManager::Instance()->Clear();
 
  GraveManager::Instance()->load();
 
 

}

//-------------------------------- Update -------------------------------------
//
//  calls the update function of each entity
//-----------------------------------------------------------------------------
void Game::Update()
{

 
   SDL_RenderClear(m_pRenderer);
  
  Render();
 
  //don't update if the user has paused the game
  if (m_bPaused) return;
  
  GraveManager::Instance()->Update();
  CharManager::Instance()->Update();
 
  
  //update all the queued searches in the path manager
  m_pPathManager->UpdateSearches();

  //update any doors
  std::vector<Door*>::iterator curDoor =m_pMap->GetDoors().begin();
  for (curDoor; curDoor != m_pMap->GetDoors().end(); ++curDoor)
  {
    (*curDoor)->Update();
  }

  ProjectileManager::Instance()->Update();
  
 

  //update the triggers
  m_pMap->UpdateTriggerSystem(m_Bots);


 

   SDL_RenderPresent(m_pRenderer);
}


//----------------------------- AttemptToAddBot -------------------------------
//-----------------------------------------------------------------------------
bool Game::AttemptToAddBot(Character* pBot)
{//g_screenLog->log(LL_INFO, "Attempting to add bot");
  //make sure there are some spawn points available
  if (m_pMap->GetSpawnPoints().size() <= 0)
  {
    std::cout << ("Map has no spawn points!"); return false;
  }

  //we'll make the same number of attempts to spawn a bot this update as
  //there are spawn points
  int attempts = m_pMap->GetSpawnPoints().size();
  //g_screenLog->log(LL_INFO, "attempts = %d",attempts);

  while (--attempts >= 0)
  { 
    //select a random spawn point
    Vector2D pos = m_pMap->GetRandomSpawnPoint();

    //check to see if it's occupied
    std::vector<Character*>::const_iterator curBot = m_Bots.begin();

    bool bAvailable = true;

    for (curBot; curBot != m_Bots.end(); ++curBot)
    {
      //if the spawn point is unoccupied spawn a bot
      if (Vec2DDistance(pos, (*curBot)->Pos()) < (*curBot)->BRadius())
      {
        bAvailable = false;
      }
    }

    if (bAvailable)
    {  
      pBot->Spawn(pos);

      return true;   
    }
  }

  return false;
}

//-------------------------- AddBots --------------------------------------
//
//  Adds a bot and switches on the default steering behavior
//-----------------------------------------------------------------------------
void Game::AddBots(unsigned int NumBotsToAdd)
{
#ifdef LOG
    std::cout << "Adding Bots\n";
  #endif

 
    
   while (NumBotsToAdd--)
  {
    //create a bot. (its position is irrelevant at this point because it will
    //not be rendered until it is spawned)
    #ifdef LOG
    std::cout << "Creating new Character()\n";
    #endif
    //Character* rb = new Character(this, Vector2D(0,0));
    Character* rb =  GameObjectFactory::Instance()->create("Character");
    //Zombie* rb = new Zombie(this, Vector2D(0,0));

    rb->load();
    //switch the default steering behaviors on
    rb->GetSteering()->WallAvoidanceOn();
    rb->GetSteering()->SeparationOn();

    m_Bots.push_back(rb);
    //register the bot with the entity manager
     EntityMgr->RegisterEntity(rb);
   
    
#ifdef LOG
     std::cout << "Adding bot with ID " << rb->ID() << "\n";
#endif
} 
}

//---------------------------- NotifyAllBotsOfRemoval -------------------------
//
//  when a bot is removed from the game by a user all remianing bots
//  must be notifies so that they can remove any references to that bot from
//  their memory
//-----------------------------------------------------------------------------
void Game::NotifyAllBotsOfRemoval(Character* pRemovedBot)const
{
    std::vector<Character*>::const_iterator curBot = m_Bots.begin();
    for (curBot; curBot != m_Bots.end(); ++curBot)
    {
      Dispatcher->DispatchMsg(SEND_MSG_IMMEDIATELY,
                              SENDER_ID_IRRELEVANT,
                              (*curBot)->ID(),
                              Msg_UserHasRemovedBot,
                              pRemovedBot);

    }
}
//-------------------------------RemoveBot ------------------------------------
//
//  removes the last bot to be added from the game
//-----------------------------------------------------------------------------
void Game::RemoveBot()
{
  m_bRemoveABot = true;
}




//----------------------------- GetBotAtPosition ------------------------------
//
//  given a position on the map this method returns the bot found with its
//  bounding radius of that position.
//  If there is no bot at the position the method returns NULL
//-----------------------------------------------------------------------------
Character* Game::GetBotAtPosition(Vector2D CursorPos)const
{
  std::vector<Character*>::const_iterator curBot = m_Bots.begin();

  for (curBot; curBot != m_Bots.end(); ++curBot)
  {
    if (Vec2DDistance((*curBot)->Pos(), CursorPos) < (*curBot)->BRadius())
    {
      if ((*curBot)->isAlive())
      {
        return *curBot;
      }
    }
  }

  return NULL;
}

//-------------------------------- LoadMap ------------------------------------
//
//  sets up the game environment from map file
//-----------------------------------------------------------------------------
bool Game::LoadMap(const std::string& filename)
{ 
  //clear any current bots and projectiles
   Clear();
  
  //out with the old
  delete m_pMap;
  delete m_pPathManager;

  //in with the new
  GraveManager::Instance()->load();
  m_pPathManager = new PathManager<PathPlanner>(script->getInt("maxsearchcyclesperupdatestep"));
  m_pMap = new Map();
  
  //make sure the entity manager is reset
  EntityMgr->Reset();

 
  //load the new map data
  if (m_pMap->LoadMap(filename))
  {
    #ifdef LOG
    std::cout << "LoadMap called succesfully" <<endl;
    #endif
    CharManager::Instance()->AddChars(3);
  
    return true;
  }
  
  return false;
}


//------------------------- ExorciseAnyPossessedBot ---------------------------
//
//  when called will release any possessed bot from user control
//-----------------------------------------------------------------------------
void Game::ExorciseAnyPossessedBot()
{
  if (m_pSelectedBot) m_pSelectedBot->Exorcise();
}







//---------------------------- isLOSOkay --------------------------------------
//
//  returns true if the ray between A and B is unobstructed.
//------------------------------------------------------------------------------
bool Game::isLOSOkay(Vector2D A, Vector2D B)const
{
  return !doWallsObstructLineSegment(A, B, m_pMap->GetWalls());
}

//------------------------- isPathObstructed ----------------------------------
//
//  returns true if a bot cannot move from A to B without bumping into 
//  world geometry. It achieves this by stepping from A to B in steps of
//  size BoundingRadius and testing for intersection with world geometry at
//  each point.
//-----------------------------------------------------------------------------
bool Game::isPathObstructed(Vector2D A,
                                  Vector2D B,
                                  double    BoundingRadius)const
{
  Vector2D ToB = Vec2DNormalize(B-A);

  Vector2D curPos = A;

  while (Vec2DDistanceSq(curPos, B) > BoundingRadius*BoundingRadius)
  {   
    //advance curPos one step
    curPos += ToB * 0.5 * BoundingRadius;
    
    //test all walls against the new position
    if (doWallsIntersectCircle(m_pMap->GetWalls(), curPos, BoundingRadius))
    {
      return true;
    }
  }

  return false;
}


//----------------------------- GetAllBotsInFOV ------------------------------
//
//  returns a vector of pointers to bots within the given bot's field of view
//-----------------------------------------------------------------------------
std::vector<Character*>
Game::GetAllBotsInFOV(const Character* pBot)const
{
  std::vector<Character*> VisibleBots;

  std::vector<Character*>::const_iterator curBot = m_Bots.begin();
  for (curBot; curBot != m_Bots.end(); ++curBot)
  {
    //make sure time is not wasted checking against the same bot or against a
    // bot that is dead or re-spawning
    if (*curBot == pBot ||  !(*curBot)->isAlive()) continue;

    //first of all test to see if this bot is within the FOV
    if (isSecondInFOVOfFirst(pBot->Pos(),
                             pBot->Facing(),
                             (*curBot)->Pos(),
                             pBot->FieldOfView()))
    {
      //cast a ray from between the bots to test visibility. If the bot is
      //visible add it to the vector
      if (!doWallsObstructLineSegment(pBot->Pos(),
                              (*curBot)->Pos(),
                              m_pMap->GetWalls()))
      {
        VisibleBots.push_back(*curBot);
      }
    }
  }

  return VisibleBots;
}

//---------------------------- isSecondVisibleToFirst -------------------------

bool
Game::isSecondVisibleToFirst(const Character* pFirst,
                                   const Character* pSecond)const
{
  //if the two bots are equal or if one of them is not alive return false
  if ( !(pFirst == pSecond) && pSecond->isAlive())
  {
    //first of all test to see if this bot is within the FOV
    if (isSecondInFOVOfFirst(pFirst->Pos(),
                             pFirst->Facing(),
                             pSecond->Pos(),
                             pFirst->FieldOfView()))
    {
      //test the line segment connecting the bot's positions against the walls.
      //If the bot is visible add it to the vector
      if (!doWallsObstructLineSegment(pFirst->Pos(),
                                      pSecond->Pos(),
                                      m_pMap->GetWalls()))
      {
        return true;
      }
    }
  }

  return false;
}

void Game::GetPlayerInput()const
{
  if (m_pSelectedBot && m_pSelectedBot->isPossessed())
  {
      
   }
}



//--------------------- GetPosOfClosestSwitch -----------------------------
//
//  returns the position of the closest visible switch that triggers the
//  door of the specified ID
//-----------------------------------------------------------------------------
Vector2D 
Game::GetPosOfClosestSwitch(Vector2D botPos, unsigned int doorID)const
{
  std::vector<unsigned int> SwitchIDs;
  
  //first we need to get the ids of the switches attached to this door
  std::vector<Door*>::const_iterator curDoor;
  for (curDoor = m_pMap->GetDoors().begin();
       curDoor != m_pMap->GetDoors().end();
       ++curDoor)
  {
    if ((*curDoor)->ID() == doorID)
    {
       SwitchIDs = (*curDoor)->GetSwitchIDs(); break;
    }
  }

  Vector2D closest;
  double ClosestDist = MaxDouble;
  
  //now test to see which one is closest and visible
  std::vector<unsigned int>::iterator it;
  for (it = SwitchIDs.begin(); it != SwitchIDs.end(); ++it)
  {
    Entity* trig = EntityMgr->GetEntityFromID(*it);

    if (isLOSOkay(botPos, trig->Pos()))
    {
      double dist = Vec2DDistanceSq(botPos, trig->Pos());

      if ( dist < ClosestDist)
      {
        ClosestDist = dist;
        closest = trig->Pos();
      }
    }
  }

  return closest;
}





