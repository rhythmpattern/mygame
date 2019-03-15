#ifndef GOAL_SEEK_TO_POSITION_H
#define GOAL_SEEK_TO_POSITION_H
#pragma warning (disable:4786)

#include "Goal.h"
#include "../2D/Vector2D.h"
#include "Goal_Types.h"
#include "../Character.h"


class Goal_SeekToPosition : public Goal<Character>
{
private:

  //the position the bot is moving to
  Vector2D  m_vPosition;

  //the approximate time the bot should take to travel the target location
  double     m_dTimeToReachPos;
  
  //this records the time this goal was activated
  double     m_dStartTime;

  //returns true if a bot gets stuck
  bool      isStuck()const;

public:

  Goal_SeekToPosition(Character* pBot, Vector2D target);

  //the usual suspects
  void Activate();
  int  Process();
  void Terminate();

  void Render();
};




#endif

