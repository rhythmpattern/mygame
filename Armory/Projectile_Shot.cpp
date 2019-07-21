#include "Projectile_Shot.h"
#include "../Character.h"
#include "../Game.h"
#include "../constants.h"
#include "../2D/WallIntersectionTests.h"
#include "../Map.h"
#include "../Scriptor.h"
#include "../Messages.h"
#include "../Messaging/MessageDispatcher.h"


//-------------------------- ctor ---------------------------------------------
//-----------------------------------------------------------------------------
Projectile_Shot::Projectile_Shot(Character* shooter, Vector2D target):

        Projectile(target,
		   shooter->GetRoom(),
                         shooter->ID(),
                         shooter->Pos(),
                         shooter->Facing(),
		   script->getInt("boltdamage"),
		   script->getNum("boltscale"),
		   script->getNum("boltmaxspeed"),
		   script->getNum("boltmass"),
		   script->getNum("boltmaxforce"))
{
   assert (target != Vector2D());
    
}


//------------------------------ Update ---------------------------------------
//-----------------------------------------------------------------------------
void Projectile_Shot::Update()
{
  if (!m_bImpacted)
  {
    m_vVelocity = MaxSpeed() * Heading();
    
    //make sure vehicle does not exceed maximum velocity
    m_vVelocity.Truncate(m_dMaxSpeed);

    //update the position
    m_vPosition += m_vVelocity;
    
   
    //TextureManager::Instance()->drawFrame("isaac",  m_vPosition.x, m_vPosition.y, 20, 20,0,0, Game::Instance()->getRenderer(),0,100);
    
    //if the projectile has reached the target podotsition or it hits an entity
    //or wall it should explode/inflict damage/whatever and then mark itself
    //as dead


    //test to see if the line segment connecting the bolt's current position
    //and previous position intersects with any bots.
    Character* hit = GetClosestIntersectingBot(m_vPosition - m_vVelocity,
                                               m_vPosition);
    
    //if hit
    if (hit)
    { 
      m_bImpacted = true;
      m_bDead     = true;
      
      //send a message to the bot to let it know it's been hit, and who the
      //shot came from
      Dispatcher->DispatchMsg(SEND_MSG_IMMEDIATELY,
                              m_iShooterID,
                              hit->ID(),
                              Msg_TakeThatMF,
                              (void*)&m_iDamageInflicted);
    }

    //test for impact with a wall
    double dist;
     if( FindClosestPointOfIntersectionWithWalls(m_vPosition - m_vVelocity,
                                                 m_vPosition,
                                                 dist,
                                                 m_vImpactPoint,
                                                 m_pRoom->GetMap()->GetWalls()))
     {
      
       m_bDead     = true;
       m_bImpacted = true;

       m_vPosition = m_vImpactPoint;

       return;
     }
    
     
  }
}

void Projectile_Shot::Render()
{
  
   TextureManager::Instance()->drawFrame("dot",  m_vPosition.x -20, m_vPosition.y-20, 20, 20,0,0, Game::Instance()->getRenderer(),0,100);
}
