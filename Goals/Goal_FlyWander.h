#ifndef GOAL_FLYWANDER_H
#define GOAL_FLYWANDER_H
//-----------------------------------------------------------------------------
//
//  Name:   Goal_FlyWander.h
//
//  Author: Shaun Hose
//
//  Desc:   Causes a bot to wander until terminated
//-----------------------------------------------------------------------------
#include "Goal.h"
#include "Goal_Types.h"
#include "../Character.h"


class Goal_FlyWander : public Goal<Character>
{
 private:
  bool m_bInRange;
  double m_dEndTime;
public:

  Goal_FlyWander(Character* pBot):Goal<Character>(pBot,goal_flywander)
  {}

  void Activate();

  int  Process();

  void Terminate();
};





#endif
