 #include "Player.h"
 #include "ObjectEnumerations.h"


//-------------------------- ctor ---------------------------------------------
Player::Player(Game* world,Vector2D pos):
  Character(world,pos)
           
{
  SetEntityType(type_player);
  
  
}

void Player::handleinput()
{
  if (!isDead())
    {
       if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_UP) && m_vPosition.y > 0)
        {
            m_vVelocity.setY(-m_dMaxSpeed);
        }
    }
}
