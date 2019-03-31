#include "Goal_Think_Fly.h"
#include "Goal_Fly.h"

Goal_Think_Fly::Goal_Think_Fly(Character* pBot) : Goal_Think(pBot){}

void Goal_Think_Fly::AddGoal_AttackTarget()
{
 
  if (notPresent(goal_fly) && notPresent(goal_wander))
    {
    
    AddSubgoal( new Goal_Fly(m_pOwner));
    AddSubgoal( new Goal_FlyExplore(m_pOwner));
  }



}
