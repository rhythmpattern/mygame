#include "ExploreGoal_Evaluator.h"
#include "../Navigation/PathPlanner.h"
#include "../ObjectEnumerations.h"
#include "../misc/Stream_Utility_Functions.h"
#include "Feature.h"

#include "Goal_Think.h"
#include "Goal_Types.h"




//---------------- CalculateDesirability -------------------------------------
//-----------------------------------------------------------------------------
double ExploreGoal_Evaluator::CalculateDesirability(Character* pBot)
{
  double Desirability = 0.05;

  Desirability *= m_dCharacterBias;

  return Desirability;
}

//----------------------------- SetGoal ---------------------------------------
//-----------------------------------------------------------------------------
void ExploreGoal_Evaluator::SetGoal(Character* pBot)
{ 
  pBot->GetBrain()->AddGoal_Explore();
}


