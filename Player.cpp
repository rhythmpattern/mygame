 #include "Player.h"
 #include "ObjectEnumerations.h"
#include "SteeringBehaviors.h"
class PlayerSteering;


//-------------------------- ctor ---------------------------------------------
Player::Player(Game* world,Vector2D pos):
  Character(world,pos)
           
{
  SetEntityType(type_player);
  SetID(0);
   m_pSteering->WallAvoidanceOn();
    
    Spawn(Vector2D(150,150));
    TakePossession();

}


//--------------------------- HandleMessage -----------------------------------
//-----------------------------------------------------------------------------
bool Player::HandleMessage(const Telegram& msg)
{
    
  
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
     
    }
  default: return false;
  }
}
