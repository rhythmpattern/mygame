#ifndef EXPLORE_GOAL_EVALUATOR
#define EXPLORE_GOAL_EVALUATOR
#pragma warning (disable:4786)
//-----------------------------------------------------------------------------
//
//  Name:   ExploreGoal_Evaluator.h
//
//  Author: Shaun Hose
//
//  Desc:  class to calculate how desirable the goal of exploring is
//-----------------------------------------------------------------------------

#include "Goal_Evaluator.h"
#include "../Character.h"


class ExploreGoal_Evaluator : public Goal_Evaluator
{ 
public:

  ExploreGoal_Evaluator(double bias):Goal_Evaluator(bias){}
  
   double CalculateDesirability(Character* pBot);

  void  SetGoal(Character* pEnt);


};

#endif
