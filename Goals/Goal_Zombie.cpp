#include "Goal_Zombie.h"
#include "Goal_SeekToPosition.h"
#include "Goal_HuntTarget.h"
#include "Goal_DodgeSideToSide.h"
#include "../Character.h"
#include "Goal_Pause.h"






//------------------------------- Activate ------------------------------------
//-----------------------------------------------------------------------------
void Goal_Zombie::Activate()
{
  m_iStatus = active;
  m_dEndTime = Clock->GetCurrentTime() + 3;
  //if this goal is reactivated then there may be some existing subgoals that
  //must be removed
  RemoveAllSubgoals();
  //it is possible for a bot's target to die whilst this goal is active so we
  //must test to make sure the bot always has an active target

  if (!m_pOwner->GetTargetSys()->isTargetPresent())
  {
     m_iStatus = completed;

     return;
  }

  //if the bot is able to shoot the target (there is LOS between bot and
  //target), then select a tactic to follow while shooting
  if (m_pOwner->GetTargetSys()->isTargetShootable())
    {std::cout << "CHEKCING";
   
      AddSubgoal(new Goal_SeekToPosition(m_pOwner, m_pOwner->GetTargetBot()->Pos()));
    
  }

  //if the target is not visible, go hunt it.
  else
  {
    AddSubgoal(new Goal_HuntTarget(m_pOwner));
  }
}

//-------------------------- Process ------------------------------------------
//-----------------------------------------------------------------------------
int Goal_Zombie::Process()
{
  //if status is inactive, call Activate()
  ActivateIfInactive();
    
  //process the subgoals
  m_iStatus = ProcessSubgoals();

  ReactivateIfFailed();
  if (Clock->GetCurrentTime() - m_dEndTime > 0) m_iStatus = completed;
  return m_iStatus;
}




