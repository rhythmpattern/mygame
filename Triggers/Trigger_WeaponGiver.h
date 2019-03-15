#ifndef WEAPON_GIVER_H
#define WEAPON_GIVER_H
#pragma warning (disable:4786)
//-----------------------------------------------------------------------------
//
//  Name:     Trigger_WeaponGiver.h
//
//  Author:   Shaun Hose
//
//  Desc:     This trigger 'gives' the triggering bot a weapon of the
//            specified type 
//
//-----------------------------------------------------------------------------
#include "Trigger_Respawning.h"
#include "../Character.h"
#include <iosfwd>




class Trigger_WeaponGiver : public Trigger_Respawning<Character>
{
private:

  //vrtex buffers for rocket shape
  std::vector<Vector2D>         m_vecRLVB;
  std::vector<Vector2D>         m_vecRLVBTrans;
  
public:

  //this type of trigger is created when reading a map file
  Trigger_WeaponGiver(std::ifstream& datafile);

  //if triggered, this trigger will call the PickupWeapon method of the
  //bot. PickupWeapon will instantiate a weapon of the appropriate type.
  void Try(Character*);
  
 

  void Read (std::ifstream& is);
};




#endif
