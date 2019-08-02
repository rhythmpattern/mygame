#include "Goal_2DMove.h"
#include "../Character.h"
#include "../SteeringBehaviors.h"
#include "Goal_SeekToPosition.h"




//-----------------------nextDir--------------------------------------------
void Goal_2DMove::nextDir()
{

  int x = RandInt(-1,1);
  int y = RandInt(-1,1);

  if (Vector2D(x,y) == dir || x==y || x==-y)
    nextDir();
  else dir = Vector2D(x,y);


}


//---------------------------- Initialize -------------------------------------
//-----------------------------------------------------------------------------  
void Goal_2DMove::Activate()
{
  m_iStatus = active;
  
  nextDir();
  AddSubgoal(new Goal_SeekToPosition(m_pOwner, m_pOwner->Pos()+100000*dir));

 
}

//------------------------------ Process --------------------------------------
//-----------------------------------------------------------------------------
int Goal_2DMove::Process()
{
  //if status is inactive, call Activate()
  ActivateIfInactive();
  if (!m_pOwner->canWalkBetween(m_pOwner->Pos() , m_pOwner->Pos()+dir*100)){  nextDir();
      RemoveAllSubgoals();
      AddSubgoal(new Goal_SeekToPosition(m_pOwner, m_pOwner->Pos()+100000*dir)); }
  return m_iStatus = ProcessSubgoals();
}

//---------------------------- Terminate --------------------------------------
//-----------------------------------------------------------------------------
void Goal_2DMove::Terminate()
{
 
}

