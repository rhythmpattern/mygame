#ifndef GOAL_THINK_FLY_H
#define GOAL_THINK_FLY_H
//-----------------------------------------------------------------------------
//
//  Name:   Goal_Think_Fly .h
//
//  Author: Shaun Hose
//
//  Desc:   class to arbitrate between a collection of high level goals, and
//          to process those goals.
//-----------------------------------------------------------------------------
#include <vector>
#include <string>
#include "../2D/Vector2D.h"
#include "Goal_Composite.h"
#include "Goal_Evaluator.h"
#include "../Character.h"
#include "Goal_Think.h"
#include "Goal_FlyExplore.h"


class Goal_Think_Fly : public Goal_Think
{


public:

  Goal_Think_Fly(Character* pBot);
  void AddGoal_AttackTarget();


};


#endif
