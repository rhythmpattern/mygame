#ifndef GOAL_FIND_TARGET_H
#define GOAL_FIND_TARGET_H
#pragma warning (disable:4786)
//-----------------------------------------------------------------------------
//
//  Name:   Goal_HuntTarget.h
//
//  Author: Shaun Hose
//
//  Desc:   Causes a bot to search for its current target. Exits when target
//          is in view
//-----------------------------------------------------------------------------
#include "Goal_Composite.h"
#include "Goal_Types.h"
#include "../Character.h"


class Goal_HuntTarget : public Goal_Composite<Character>
{
private:

  //this value is set to true if the last visible position of the target
  //bot has been searched without success
  bool  m_bLVPTried;

public:

  Goal_HuntTarget(Character* pBot):Goal_Composite<Character>(pBot, goal_hunt_target),
                                   m_bLVPTried(false)
  {}

   //the usual suspects
  void Activate();
  int  Process();
  void Terminate(){}

  void Render();


};





#endif
