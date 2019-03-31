#ifndef GOAL_ZOMBIE_H
#define GOAL_ZOMBIE_H
//-----------------------------------------------------------------------------
//
//  Name:   Goal_Zombie.h
//
//  Author: Shaun Hose
//
//  Desc:   Goal to run straight at target.
//
//-----------------------------------------------------------------------------
#include "Goal_Composite.h"
#include "Goal_Types.h"
#include "../Character.h"
#include "../Time/CrudeTimer.h"




class Goal_Zombie : public Goal_Composite<Character>
{

 private:
  bool m_bInRange;
  double m_dEndTime;
public:

  Goal_Zombie(Character* pOwner):Goal_Composite<Character>(pOwner, goal_zombie)
  {}

  void Activate();

  int  Process();

  void Terminate(){m_iStatus = completed;}

};






#endif
