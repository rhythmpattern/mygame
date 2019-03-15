#include "TargetingSystem.h"
#include "Character.h"
#include "SensoryMemory.h"



//-------------------------------- ctor ---------------------------------------
//-----------------------------------------------------------------------------
TargetingSystem::TargetingSystem(Character* owner):m_pOwner(owner),
                                                               m_pCurrentTarget(0)
{}



//----------------------------- Update ----------------------------------------

//-----------------------------------------------------------------------------
void TargetingSystem::Update()
{
  double ClosestDistSoFar = MaxDouble;
  m_pCurrentTarget       = 0;

  //grab a list of all the opponents the owner can sense
  std::vector<Character*> SensedBots;
  SensedBots = m_pOwner->GetSensoryMem()->GetListOfRecentlySensedOpponents();
  
  std::vector<Character*>::const_iterator curBot = SensedBots.begin();
  for (curBot; curBot != SensedBots.end(); ++curBot)
  {
    //make sure the bot is alive and that it is not the owner
    if ((*curBot)->isAlive() && (*curBot != m_pOwner) )
    {
      double dist = Vec2DDistanceSq((*curBot)->Pos(), m_pOwner->Pos());

      if (dist < ClosestDistSoFar)
      {
        ClosestDistSoFar = dist;
        m_pCurrentTarget = *curBot;
      }
    }
  }
}




bool TargetingSystem::isTargetWithinFOV()const
{
  return m_pOwner->GetSensoryMem()->isOpponentWithinFOV(m_pCurrentTarget);
}

bool TargetingSystem::isTargetShootable()const
{
  return m_pOwner->GetSensoryMem()->isOpponentShootable(m_pCurrentTarget);
}

Vector2D TargetingSystem::GetLastRecordedPosition()const
{
  return m_pOwner->GetSensoryMem()->GetLastRecordedPositionOfOpponent(m_pCurrentTarget);
}

double TargetingSystem::GetTimeTargetHasBeenVisible()const
{
  return m_pOwner->GetSensoryMem()->GetTimeOpponentHasBeenVisible(m_pCurrentTarget);
}

double TargetingSystem::GetTimeTargetHasBeenOutOfView()const
{
  return m_pOwner->GetSensoryMem()->GetTimeOpponentHasBeenOutOfView(m_pCurrentTarget);
}
