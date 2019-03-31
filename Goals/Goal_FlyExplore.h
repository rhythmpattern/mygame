#ifndef GOAL_FLYEXPLORE_H
#define GOAL_FLYEXPLORE_H

#include "Goal_Composite.h"
#include "Goal_Types.h"


class Character;


class Goal_FlyExplore : public Goal_Composite<Character>
{
private:
  
  double m_dEndTime;
  Vector2D  m_CurrentDestination;

  //set to true when the destination for the exploration has been established
  bool      m_bDestinationIsSet;

public:

  Goal_FlyExplore(Character* pOwner):Goal_Composite<Character>(pOwner,
                                                            goal_flyexplore),
                                  m_bDestinationIsSet(false)
  {}


  void Activate();

  int Process();

  void Terminate(){}

  bool HandleMessage(const Telegram& msg);
};





#endif
