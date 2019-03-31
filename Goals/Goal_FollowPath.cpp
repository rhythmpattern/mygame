#include "Goal_FollowPath.h"
#include "../Character.h"
#include "../Game.h"

#include "Goal_TraverseEdge.h"
#include "Goal_NegotiateDoor.h"



//------------------------------ ctor -----------------------------------------
//-----------------------------------------------------------------------------
Goal_FollowPath::
Goal_FollowPath(Character*          pBot,
                std::list<PathEdge> path):Goal_Composite<Character>(pBot, goal_follow_path),
                                                  m_Path(path)
{
}


//------------------------------ Activate -------------------------------------
//-----------------------------------------------------------------------------
void Goal_FollowPath::Activate()
{
  m_iStatus = active;
  
  //get a reference to the next edge
  PathEdge edge = m_Path.front();

  //remove the edge from the path
  m_Path.pop_front(); 

  //some edges specify that the bot should use a specific behavior when
  //following them. This switch statement queries the edge behavior flag and
  //adds the appropriate goals/s to the subgoal list.
  switch(edge.Behavior())
  {
  case NavGraphEdge::normal:
    {
      AddSubgoal(new Goal_TraverseEdge(m_pOwner, edge, m_Path.empty()));
    }

    break;

  case NavGraphEdge::goes_through_door:
    {

      //also add a goal that is able to handle opening the door
      AddSubgoal(new Goal_NegotiateDoor(m_pOwner, edge, m_Path.empty()));
    }

    break;

  case NavGraphEdge::jump:
    {
      //add subgoal to jump along the edge
    }

    break;

  case NavGraphEdge::grapple:
    {
      //add subgoal to grapple along the edge
    }

    break;

  default:
break;
    //throw std::runtime_error("<Goal_FollowPath::Activate>: Unrecognized edge type");
  }
}


//-------------------------- Process ------------------------------------------
//-----------------------------------------------------------------------------
int Goal_FollowPath::Process()
{
  //if status is inactive, call Activate()
  ActivateIfInactive();

  m_iStatus = ProcessSubgoals();

  //if there are no subgoals present check to see if the path still has edges.
  //remaining. If it does then call activate to grab the next edge.
  if (m_iStatus == completed && !m_Path.empty())
  {
    Activate(); 
  }

  return m_iStatus;
}
 





