#ifndef ATTACK_GOAL_EVALUATOR
#define ATTACK_GOAL_EVALUATOR
#pragma warning (disable:4786)
//-----------------------------------------------------------------------------
//
//  Name:   AttackTargetGoal_Evaluator.h
//
//  Author: Shaun Hose
//
//  Desc:  class to calculate how desirable the goal of attacking the bot's
//         current target is
//-----------------------------------------------------------------------------

#include "Goal_Evaluator.h"
#include "../Character.h"


class AttackTargetGoal_Evaluator : public Goal_Evaluator
{ 
public:

  AttackTargetGoal_Evaluator(double bias):Goal_Evaluator(bias){}
  
  double CalculateDesirability(Character* pBot);

  void  SetGoal(Character* pEnt);

};



#endif
