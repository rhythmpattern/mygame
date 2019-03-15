#ifndef GOAL_ATTACKTARGET_H
#define GOAL_ATTACKTARGET_H
#pragma warning (disable:4786)
//-----------------------------------------------------------------------------
//
//  Name:   Goal_AttackTarget.h
//
//  Author: Shaun Hose
//
//  Desc:   
//
//-----------------------------------------------------------------------------
#include "Goal_Composite.h"
#include "Goal_Types.h"
#include "../Character.h"





class Goal_AttackTarget : public Goal_Composite<Character>
{
public:

  Goal_AttackTarget(Character* pOwner):Goal_Composite<Character>(pOwner, goal_attack_target)
  {}

  void Activate();

  int  Process();

  void Terminate(){m_iStatus = completed;}

};






#endif
