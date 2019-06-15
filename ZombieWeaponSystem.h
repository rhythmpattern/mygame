#ifndef ZOMBIEWEAPONSYSTEM_H
#define ZOMBIEWEAPONSYSTEM_H

#include "WeaponSystem.h"


class ZombieWeaponSystem : public WeaponSystem
{
 public:
  ZombieWeaponSystem(Character* owner,
                     double      ReactionTime,
                     double      AimAccuracy,
                     double      AimPersistance);
  void Initialize();
  void TakeAimAndShoot()const;
 
 
};
#endif
