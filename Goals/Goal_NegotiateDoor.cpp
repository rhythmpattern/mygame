#include "Goal_NegotiateDoor.h"
#include "../Character.h"
#include "../Game.h"
#include "../Navigation/PathPlanner.h"


#include "Goal_MoveToPosition.h"
#include "Goal_TraverseEdge.h"





//---------------------------- ctor -------------------------------------------
//-----------------------------------------------------------------------------
Goal_NegotiateDoor::
Goal_NegotiateDoor(Character*   pBot,
                   PathEdge     edge,
                   bool         LastEdge):Goal_Composite<Character>(pBot, goal_negotiate_door),
                                        m_PathEdge(edge),
                                        m_bLastEdgeInPath(LastEdge)

{
}

//---------------------------- Activate ---------------------------------------
//-----------------------------------------------------------------------------
void Goal_NegotiateDoor::Activate()
{
  m_iStatus = active;
  
  //if this goal is reactivated then there may be some existing subgoals that
  //must be removed
  RemoveAllSubgoals();
  
  //get the position of the closest navigable switch
  Vector2D posSw = m_pOwner->GetRoom()->GetPosOfClosestSwitch(m_pOwner->Pos(),
                                                          m_PathEdge.DoorID());

  //because goals are *pushed* onto the front of the subgoal list they must
  //be added in reverse order.
  
  //first the goal to traverse the edge that passes through the door
  AddSubgoal(new Goal_TraverseEdge(m_pOwner, m_PathEdge, m_bLastEdgeInPath));

  //next, the goal that will move the bot to the beginning of the edge that
  //passes through the door
  AddSubgoal(new Goal_MoveToPosition(m_pOwner, m_PathEdge.Source()));
  
  //finally, the Goal that will direct the bot to the location of the switch
  AddSubgoal(new Goal_MoveToPosition(m_pOwner, posSw));
}


//------------------------------ Process --------------------------------------
//-----------------------------------------------------------------------------
int Goal_NegotiateDoor::Process()
{
  //if status is inactive, call Activate()
  ActivateIfInactive();

  //process the subgoals
  m_iStatus = ProcessSubgoals();

  return m_iStatus;
}




