#include "Goal_HuntTarget.h"
#include "Goal_Explore.h"
#include "Goal_MoveToPosition.h"
#include "../Character.h"
#include "../SteeringBehaviors.h"


//---------------------------- Initialize -------------------------------------
//-----------------------------------------------------------------------------  
void Goal_HuntTarget::Activate()
{
  m_iStatus = active;
  
  //if this goal is reactivated then there may be some existing subgoals that
  //must be removed
  RemoveAllSubgoals();
  
  //it is possible for the target to die whilst this goal is active so we
  //must test to make sure the bot always has an active target
  if (m_pOwner->GetTargetSys()->isTargetPresent())
  {
    //grab a local copy of the last recorded position (LRP) of the target
    const Vector2D lrp = m_pOwner->GetTargetSys()->GetLastRecordedPosition();

    //if the bot has reached the LRP and it still hasn't found the target
    //it starts to search by using the explore goal to move to random
    //map locations
    if (lrp.isZero() || m_pOwner->isAtPosition(lrp))
    {
      AddSubgoal(new Goal_Explore(m_pOwner));
    }

    //else move to the LRP
    else
    {
      AddSubgoal(new Goal_MoveToPosition(m_pOwner, lrp));
    }
  }

  //if their is no active target then this goal can be removed from the queue
  else
  {
    m_iStatus = completed;
  }
    
}

//------------------------------ Process --------------------------------------
//-----------------------------------------------------------------------------
int Goal_HuntTarget::Process()
{
  //if status is inactive, call Activate()
  ActivateIfInactive();

  m_iStatus = ProcessSubgoals();

  //if target is in view this goal is satisfied
  if (m_pOwner->GetTargetSys()->isTargetWithinFOV())
  {
     m_iStatus = completed;
  }

  return m_iStatus;
}



