#include "Projectile.h"
#include "../Game.h"
#include <list>
#include "../CharManager.h"

//------------------ GetClosestIntersectingBot --------------------------------

Character* Projectile::GetClosestIntersectingBot(Vector2D    From,
                                                       Vector2D    To)const
{
  Character* ClosestIntersectingBot = 0;
  double ClosestSoFar = MaxDouble;

  //iterate through all entities checking against the line segment FromTo
  std::vector<Character*>::const_iterator curBot;
  //Creating new variable here is critical to avoid Segmentation Faults! Straight m_pWorld->GetAllBots() leads to faulty memory.
  const std::vector<Character* > allbots = CharManager::Instance()->GetAllChars();
 
  for (curBot =  allbots.begin();
       curBot != allbots.end();
       ++curBot)
    {
     
      if ((*curBot) != NULL) {
    //make sure we don't check against the shooter of the projectile
    if ( ((*curBot)->ID() != m_iShooterID))
    {
      //if the distance to FromTo is less than the entity's bounding radius then
      //there is an intersection
      if (DistToLineSegment(From, To, (*curBot)->Pos()) < (*curBot)->BRadius())
      {
        //test to see if this is the closest so far
        double Dist = Vec2DDistanceSq((*curBot)->Pos(), m_vOrigin);

        if (Dist < ClosestSoFar)
        {
          Dist = ClosestSoFar;
          ClosestIntersectingBot = *curBot;
        }
      }
    }
      }
  }

  return ClosestIntersectingBot;
}


//---------------------- GetListOfIntersectingBots ----------------------------
std::vector<Character*> Projectile::GetListOfIntersectingBots(Vector2D From,
                                                                  Vector2D To)const
{
  //this will hold any bots that are intersecting with the line segment
  std::vector<Character*> hits;

  //iterate through all entities checking against the line segment FromTo
  std::vector<Character*>::const_iterator curBot;
  for (curBot =  CharManager::Instance()->GetAllChars().begin();
       curBot != CharManager::Instance()->GetAllChars().end();
       ++curBot)
  {
    if ((*curBot != NULL))
    //make sure we don't check against the shooter of the projectile
    if ( ((*curBot)->ID() != m_iShooterID))
    {
      //if the distance to FromTo is less than the entities bounding radius then
      //there is an intersection so add it to hits
      if (DistToLineSegment(From, To, (*curBot)->Pos()) < (*curBot)->BRadius())
      {
        hits.push_back(*curBot);
      }
    }

  }

  return hits;
}


