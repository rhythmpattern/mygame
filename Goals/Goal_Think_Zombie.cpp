#include "Goal_Think_Zombie.h"
#include "Goal_Zombie.h"

Goal_Think_Zombie::Goal_Think_Zombie(Character* pBot) : Goal_Think(pBot){}

void Goal_Think_Zombie::AddGoal_AttackTarget()
{
  if (notPresent(goal_zombie) || notPresent(goal_pause))
  {
    RemoveAllSubgoals();
    AddSubgoal( new Goal_Zombie(m_pOwner));
  }
}
