#include "AttackTargetGoal_Evaluator.h"
#include "Goal_Think.h"
#include "Goal_Types.h"
#include "../ObjectEnumerations.h"
#include "../misc/Stream_Utility_Functions.h"
#include "Feature.h"



//------------------ CalculateDesirability ------------------------------------
//
//  returns a value between 0 and 1 that indicates the Rating of a bot (the
//  higher the score, the stronger the bot).
//-----------------------------------------------------------------------------
double AttackTargetGoal_Evaluator::CalculateDesirability(Character* pBot)
{
  double Desirability = 0.0;

  //only do the calculation if there is a target present
  if (pBot->GetTargetSys()->isTargetPresent()) 
  {
     const double Tweaker = 1.0;

     Desirability = Tweaker *
                    Feature::Health(pBot);

     //bias the value according to the personality of the bot
     Desirability *= m_dCharacterBias;
  }
    
  return Desirability;
}

//----------------------------- SetGoal ---------------------------------------
//-----------------------------------------------------------------------------
void AttackTargetGoal_Evaluator::SetGoal(Character* pBot)
{
  pBot->GetBrain()->AddGoal_AttackTarget(); 
}


