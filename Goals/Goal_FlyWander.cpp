#include "Goal_FlyWander.h"
#include "../Character.h"
#include "../SteeringBehaviors.h"
#include "../Time/CrudeTimer.h"





//---------------------------- Initialize -------------------------------------
//-----------------------------------------------------------------------------  
void Goal_FlyWander::Activate()
{
  m_iStatus = active;
   m_dEndTime = Clock->GetCurrentTime() + 1;
  m_pOwner->GetSteering()->WanderOn();
}

//------------------------------ Process --------------------------------------
//-----------------------------------------------------------------------------
int Goal_FlyWander::Process()
{
  //if status is inactive, call Activate()
  ActivateIfInactive();
 if (Clock->GetCurrentTime() - m_dEndTime > 0) m_iStatus = completed;
  return m_iStatus;
}

//---------------------------- Terminate --------------------------------------
//-----------------------------------------------------------------------------
void Goal_FlyWander::Terminate()
{
  m_pOwner->GetSteering()->WanderOff();
}
