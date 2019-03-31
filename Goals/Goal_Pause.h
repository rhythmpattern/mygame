#ifndef GOAL_PAUSE_H
#define GOAL_PAUSE_H


#include "Goal.h"
#include "../2D/Vector2D.h"
#include "Goal_Types.h"
#include "../Character.h"
#include "Goal_Composite.h"


class Goal_Pause : public Goal_Composite<Character>
{

 private:
  bool m_bInRange;
  double m_dStartTime;
  double m_dTimeToEnd;
public:

  Goal_Pause(Character* pOwner):Goal_Composite<Character>(pOwner, goal_pause)
  {}

  void Activate();

  int  Process();

  void Terminate(){m_iStatus = completed;}

};




#endif

