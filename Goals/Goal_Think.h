#ifndef GOAL_THINK_H
#define GOAL_THINK_H
#pragma warning (disable:4786)
//-----------------------------------------------------------------------------
//
//  Name:   Goal_Think .h
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



class Goal_Think : public Goal_Composite<Character>
{
private:
  
  typedef std::vector<Goal_Evaluator*>   GoalEvaluators;


  
  GoalEvaluators  m_Evaluators;

public:

  Goal_Think(Character* pBot);
  ~Goal_Think();

  //this method iterates through each goal evaluator and selects the one
  //that has the highest score as the current goal
  void Arbitrate();

  //returns true if the given goal is not at the front of the subgoal list
  bool notPresent(unsigned int GoalType)const;

  //the usual suspects
  int  Process();
  void Activate();
  void Terminate(){}
  
  //top level goal types
  void AddGoal_MoveToPosition(Vector2D pos);
  void AddGoal_Explore();
  void AddGoal_AttackTarget();

  //this adds the MoveToPosition goal to the *back* of the subgoal list.
  void QueueGoal_MoveToPosition(Vector2D pos);




};


#endif
