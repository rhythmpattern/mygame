#ifndef GOAL_2DMOVE_H
#define GOAL_2DMOVE_H
//-----------------------------------------------------------------------------
//
//  Name:   Goal_2DMove.h
//
//  Author: Shaun Hose
//
//  Desc:   Straight line movement, turning at walls.
//-----------------------------------------------------------------------------
#include "Goal_Composite.h"
#include "Goal_Types.h"
#include "../Character.h"


class Goal_2DMove : public Goal_Composite<Character>
{
private:

  Vector2D dir;
  void nextDir();

public:

  Goal_2DMove(Character* pBot):Goal_Composite<Character>(pBot,goal_2dmove)
  {}

  void Activate();

  int  Process();

  void Terminate();
};





#endif
