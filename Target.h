#ifndef TARGET_H
#define TARGET_H
//-----------------------------------------------------------------------------
//
//  Name:   Target
//
//  Author: Shaun Hose
//
//  Desc:   struct to hold data about a target
//
//-----------------------------------------------------------------------------
#include "Character.h"
struct Target
{
    //the current target (this will be null if there is no target assigned)
  Character*         Instance;

  //a vector marking the last visible position of the target.
  Vector2D           LastVisiblePosition;

  //true if target is within the field of view of the owner
  bool               isWithinFOV;

  //true if there is no obstruction between the target and the owner, 
  //permitting a shot. (for example, a the target may be behind the owner
  //but in the open. In this situation m_bWithinFOV is false but m_bShootable
  //is true). This value is utilized by the owner to determine whether or not
  //to turn around and face the target when approached from behind
  bool               isShootable;

  Target():Instance(0), isWithinFOV(false), isShootable(false){}

  void Reset(){Instance = 0; isWithinFOV = false; isShootable = false;}
};


#endif
