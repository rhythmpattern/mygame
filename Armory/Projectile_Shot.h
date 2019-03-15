
#ifndef PROJECTILE_SHOT_H
#define PROJECTILE_SHOT_H
#pragma warning (disable:4786)
//-----------------------------------------------------------------------------
//
//  Name:   Projectile_Shot.h
//
//  Author: Shaun Hose
//
//  Desc:   class to implement a bolt type projectile
//
//-----------------------------------------------------------------------------
#include "Projectile.h"

class Character;
class Projectile;



class Projectile_Shot : public Projectile
{
private:

  //tests the trajectory of the shell for an impact
  void TestForImpact();
  
public:

  Projectile_Shot(Character* shooter, Vector2D target);
  
 

  void Update();
  
};


#endif
