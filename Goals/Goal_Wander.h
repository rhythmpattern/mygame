#ifndef GOAL_WANDER_H
#define GOAL_WANDER_H
#pragma warning (disable:4786)
//-----------------------------------------------------------------------------
//
//  Name:   Goal_Wander.h
//
//  Author: Shaun Hose
//
//  Desc:   Causes a bot to wander until terminated
//-----------------------------------------------------------------------------
#include "Goal.h"
#include "Goal_Types.h"
#include "../Character.h"


class Goal_Wander : public Goal<Character>
{
private:

public:

  Goal_Wander(Character* pBot):Goal<Character>(pBot,goal_wander)
  {}

  void Activate();

  int  Process();

  void Terminate();
};





#endif
