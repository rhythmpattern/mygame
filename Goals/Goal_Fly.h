#ifndef GOAL_FLY_H
#define GOAL_FLY_H
//-----------------------------------------------------------------------------
//
//  Name:   Goal_Fly.h
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




class Goal_Fly : public Goal_Composite<Character>
{

 private:
  bool m_bInRange;
  double m_dEndTime;
public:

  Goal_Fly(Character* pOwner):Goal_Composite<Character>(pOwner, goal_fly)
  {}

  void Activate();

  int  Process();

  void Terminate(){m_iStatus = completed;}

};






#endif
