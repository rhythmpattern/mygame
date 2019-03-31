#include "Goal_Pause.h"
#include "../Character.h"
#include "../SteeringBehaviors.h"
#include "../Time/CrudeTimer.h"
#include "../Navigation/PathPlanner.h"


//------------------------------- Activate ------------------------------------
//-----------------------------------------------------------------------------
void Goal_Pause::Activate()
{
  m_iStatus = active;

  //if this goal is reactivated then there may be some existing subgoals that
  //must be removed
  RemoveAllSubgoals();
  m_dStartTime = Clock->GetCurrentTime();
  m_dTimeToEnd = m_dStartTime + 5;
 
}

//-------------------------- Process ------------------------------------------
//-----------------------------------------------------------------------------
int Goal_Pause::Process()
{
  //if status is inactive, call Activate()
  ActivateIfInactive();
    
 
  ReactivateIfFailed();
  if (Clock->GetCurrentTime() - m_dTimeToEnd > 0) m_iStatus = completed;
  return m_iStatus;
}




