#ifndef MELEE_H
#define MELEE_H

#include "Weapon.h"

class Character;

class Melee : public Weapon
{

 private:

  void InitializeFuzzyModule() ;
  int m_iDamageInflicted;

 public:

  Melee(Character* owner);

  void ShootAt(Vector2D pos);

  double GetDesirability(double DistToTarget);
  


};

#endif
