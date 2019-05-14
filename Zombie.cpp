#include "Zombie.h"
Zombie::Zombie(Game* world, Vector2D pos) : Character(world,pos)
					   
{
  SetEntityType(type_zomb);
  
   m_pWeaponSys = new ZombieWeaponSystem(this,
                                        0.2,
                                        0,
                                       1);
   m_pBrain = new Goal_Think_Zombie(this);

}

void Zombie::Update()
{ 


  
  //process the currently active goal. Note this is required even if the bot
  //is under user control. This is because a goal is created whenever a user 
  //clicks on an area of the map that necessitates a path planning request.
  m_pBrain->Process();
  
  //Calculate the steering force and update the bot's velocity and position
  UpdateMovement();

  //if the bot is under AI control but not scripted
  if (!isPossessed())
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
   // if (m_pWeaponSelectionRegulator->isReady())
   // {       
   //   m_pWeaponSys->SelectWeapon();       
  //  }

    //this method aims the bot's current weapon at the current target
    //and takes a shot if a shot is possible
    m_pWeaponSys->ChangeWeapon(type_melee);
    m_pWeaponSys->TakeAimAndShoot();
    
  }

}


//--------------------------- HandleMessage -----------------------------------
//-----------------------------------------------------------------------------
bool Zombie::HandleMessage(const Telegram& msg)
{ 
  //first see if the current goal accepts the message
  if (GetBrain()->HandleMessage(msg)) return true;
  
  //handle any messages not handles by the goals
  switch(msg.Msg)

    {


 case Msg_OpenSesame:
   // m_pWorld->SetMessage(String(String(to_string(msg.Sender).c_str())+" open_door"));
      return true;
      
  case Msg_TakeThatMF:
    {
    //just return if already dead or spawning
    if (isDead() || isSpawning()) return true;

    //the extra info field of the telegram carries the amount of damage
    ReduceHealth(DereferenceToType<int>(msg.ExtraInfo));

    //THIS CHANGE TEXTURE CODE WORKS GOOD
    /* assert (sprite->has_node(NodePath("hurt")));
    assert ( sprite->has_node(NodePath("Sprite")));
    Texture* tex = sprite->get_node(NodePath("hurt"))->cast_to<Texture>();
    sprite->get_node(NodePath("Sprite"))->cast_to<Sprite>()->set_texture(tex);*/
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
    }
  case Msg_YouGotMeYouSOB:
    {
    IncrementScore();
    // RES b = ResourceLoader::load("res://Zombie.tscn","PackedScene");
    // Node2D* n =b->cast_to<PackedScene>()->instance()->cast_to<Node2D>();
    // Texture* tex = n->get_node(NodePath("hurt"))->cast_to<Texture>();
   
    
    //the bot this bot has just killed should be removed as the target
    m_pTargSys->ClearTarget();

    return true;
    }
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


  default: return false;
  }
}

