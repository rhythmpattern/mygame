#include "ZombieWeaponSystem.h"
#include "Armory/Melee.h"



ZombieWeaponSystem::ZombieWeaponSystem(Character* owner,
                     double      ReactionTime,
                     double      AimAccuracy,
                     double      AimPersistance): WeaponSystem (owner,
                          ReactionTime,
                          AimAccuracy,
								AimPersistance){}




//------------------------------ Initialize -----------------------------------
//
//  initializes the weapons
//-----------------------------------------------------------------------------
void ZombieWeaponSystem::Initialize()
{
  //delete any existing weapons
  WeaponMap::iterator curW;
  for (curW = m_WeaponMap.begin(); curW != m_WeaponMap.end(); ++curW)
  {
    delete curW->second;
  }

  m_WeaponMap.clear();

  //set up the container
   m_pCurrentWeapon = new Melee(m_pOwner);

 
 
}


//--------------------------- TakeAimAndShoot ---------------------------------
//
//  this method aims the bots current weapon at the target (if there is a
//  target) and, if aimed correctly, fires a round
//-----------------------------------------------------------------------------
void ZombieWeaponSystem::TakeAimAndShoot()const
{
  
}
