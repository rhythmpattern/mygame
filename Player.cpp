 #include "Player.h"
 #include "ObjectEnumerations.h"
 #include "PlayerSteering.h"

//-------------------------- ctor ---------------------------------------------
Player::Player(Game* world,Vector2D pos):
  Character(world,pos)
           
{
  SetEntityType(type_player);
  SetID(0);

}

