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

