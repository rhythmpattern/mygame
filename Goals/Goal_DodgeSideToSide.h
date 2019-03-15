#ifndef GOAL_DODGE_SIDE_H
#define GOAL_DODGE_SIDE_H
#pragma warning (disable:4786)
//-----------------------------------------------------------------------------
//
//  Name:   Goal_DodgeSideToSide.h
//
//  Author: Shaun Hose
//
//  Desc:   this goal makes the bot dodge from side to side
//
//-----------------------------------------------------------------------------
#include "Goal.h"
#include "Goal_Types.h"
#include "../Character.h"





class Goal_DodgeSideToSide : public Goal<Character>
{
private:

  Vector2D    m_vStrafeTarget;

  bool        m_bClockwise;

  Vector2D  GetStrafeTarget()const;


public:

  Goal_DodgeSideToSide(Character* pBot):Goal<Character>(pBot, goal_strafe),
                                        m_bClockwise(RandBool())
  {}


  void Activate();

  int  Process();

  void Render();

  void Terminate();
 
};






#endif
