#include "Goal_Think.h"
#include <list>
#include "../ObjectEnumerations.h"
#include "../misc/utils.h"

#include "Goal_MoveToPosition.h"
#include "Goal_Explore.h"
#include "Goal_GetItem.h"
#include "Goal_Wander.h"
#include "Goal_Types.h"
#include "Goal_AttackTarget.h"
#include "ExploreGoal_Evaluator.h"
#include "AttackTargetGoal_Evaluator.h"
//#define debug


Goal_Think::Goal_Think(Character* pBot):Goal_Composite<Character>(pBot, goal_think)
{
  #ifdef debug
  std::cout<< "Goal_Think called";
  #endif
  //these biases could be loaded in from a script on a per bot basis
  //but for now we'll just give them some random values
  const double LowRangeOfBias = 0.5;
  const double HighRangeOfBias = 1.5;


  double ExploreBias = RandInRange(LowRangeOfBias, HighRangeOfBias);
  double AttackBias = RandInRange(LowRangeOfBias, HighRangeOfBias);

  //create the evaluator objects

  m_Evaluators.push_back(new ExploreGoal_Evaluator(ExploreBias));
  m_Evaluators.push_back(new AttackTargetGoal_Evaluator(AttackBias));
  AddGoal_Explore();
 
}

//----------------------------- dtor ------------------------------------------
//-----------------------------------------------------------------------------
Goal_Think::~Goal_Think()
{
  GoalEvaluators::iterator curDes = m_Evaluators.begin();
  for (curDes; curDes != m_Evaluators.end(); ++curDes)
  {
    delete *curDes;
  }
}

//------------------------------- Activate ------------------------------------
//-----------------------------------------------------------------------------
void Goal_Think::Activate()
{
  if (!m_pOwner->isPossessed())
  {
     Arbitrate();
  }

  m_iStatus = active;
}

//------------------------------ Process --------------------------------------
//
//  processes the subgoals
//-----------------------------------------------------------------------------
int Goal_Think::Process()
{
   ActivateIfInactive();
 
  int SubgoalStatus = ProcessSubgoals();
   if (SubgoalStatus == completed || SubgoalStatus == failed)
  {
    if (!m_pOwner->isPossessed())
    {
      m_iStatus = inactive;
    }
  }
 
 

  return m_iStatus;
}

//----------------------------- Update ----------------------------------------
// 
//  this method iterates through each goal option to determine which one has
//  the highest desirability.
//-----------------------------------------------------------------------------
void Goal_Think::Arbitrate()
{
  double best = 0;
  Goal_Evaluator* MostDesirable = 0;

  //iterate through all the evaluators to see which produces the highest score
  GoalEvaluators::iterator curDes = m_Evaluators.begin();
  for (curDes; curDes != m_Evaluators.end(); ++curDes)
  {
    double desirabilty = (*curDes)->CalculateDesirability(m_pOwner);
   
    if (desirabilty >= best)
    {
      best = desirabilty;
      MostDesirable = *curDes;
    }
  }

  assert(MostDesirable && "<Goal_Think::Arbitrate>: no evaluator selected");

  MostDesirable->SetGoal(m_pOwner);
}


//---------------------------- notPresent --------------------------------------
//
//  returns true if the goal type passed as a parameter is the same as this
//  goal or any of its subgoals
//-----------------------------------------------------------------------------
bool Goal_Think::notPresent(unsigned int GoalType)const
{
  if (!m_SubGoals.empty())
  {
    return m_SubGoals.front()->GetType() != GoalType;
  }

  return true;
}

void Goal_Think::AddGoal_MoveToPosition(Vector2D pos)
{
  #ifdef debug
  std::cout << "Moving to Position";
  #endif
  AddSubgoal( new Goal_MoveToPosition(m_pOwner, pos));
}

void Goal_Think::AddGoal_Explore()
{
  if (notPresent(goal_explore))
  {
    RemoveAllSubgoals();
    AddSubgoal( new Goal_Explore(m_pOwner));
  }
}



void Goal_Think::AddGoal_AttackTarget()
{
  if (notPresent(goal_attack_target))
  {
    #ifdef debug
    std::cout << "attacking target";
    #endif
    RemoveAllSubgoals();
    AddSubgoal( new Goal_AttackTarget(m_pOwner));
  }
}

//-------------------------- Queue Goals --------------------------------------
//-----------------------------------------------------------------------------
void Goal_Think::QueueGoal_MoveToPosition(Vector2D pos)
{
   m_SubGoals.push_back(new Goal_MoveToPosition(m_pOwner, pos));
}



   
