#ifndef SHOOTER_H
#define SHOOTER_H

#include "Weapon.h"

class Character;

class Shooter : public Weapon
{
 private: 

     void InitializeFuzzyModule() ;

public:

 Shooter(Character* owner );
 

void ShootAt(Vector2D pos);

double GetDesirability(double DistToTarget) ;

};

#endif
