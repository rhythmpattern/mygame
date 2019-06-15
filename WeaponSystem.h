#ifndef WEAPONSYSTEM
#define WEAPONSYSTEM
#pragma warning (disable:4786)
//-----------------------------------------------------------------------------
//
//  Name:   WeaponSystem.h
//
//  Author: Shaun Hose
//
//  Desc:   class to manage all operations specific to weapons and their
//          deployment
//
//-----------------------------------------------------------------------------
#include <map>
#include "2D/Vector2D.h"

class Weapon;
class Character;

class WeaponSystem
{
 protected:
  //a pointer to the weapon the bot is currently holding
  Weapon*    m_pCurrentWeapon;
   //a map of weapon instances indexed into by type
  typedef std::map<int, Weapon*>  WeaponMap;
   Character*       m_pOwner;
 //pointers to the weapons the bot is carrying (a bot may only carry one
  //instance of each weapon)
  WeaponMap        m_WeaponMap;

  
  


private:

 
 

  //this is the minimum amount of time a bot needs to see an opponent before
  //it can react to it. This variable is used to prevent a bot shooting at
  //an opponent the instant it becomes visible.
  double            m_dReactionTime;

  //each time the current weapon is fired a certain amount of random noise is
  //added to the the angle of the shot. This prevents the bots from hitting
  //their opponents 100% of the time. The lower this value the more accurate
  //a bot's aim will be. Recommended values are between 0 and 0.2 (the value
  //represents the max deviation in radians that can be added to each shot).
  double            m_dAimAccuracy;

  //the amount of time a bot will continue aiming at the position of the target
  //even if the target disappears from view.
  double            m_dAimPersistance;

  //predicts where the target will be by the time it takes the current weapon's
  //projectile type to reach it. Used by TakeAimAndShoot
  Vector2D    PredictFuturePositionOfTarget()const;

  //adds a random deviation to the firing angle not greater than m_dAimAccuracy 
  //rads
  void        AddNoiseToAim(Vector2D& AimingPos)const;

public:

  WeaponSystem(Character* owner,
                     double      ReactionTime,
                     double      AimAccuracy,
                     double      AimPersistance);
  
  ~WeaponSystem();

  //sets up the weapon map with just one weapon: the blaster
  virtual void          Initialize();

  //this method aims the bot's current weapon at the target (if there is a
  //target) and, if aimed correctly, fires a round. (Called each update-step
  //from Character::Update)
  virtual void          TakeAimAndShoot()const;

void          SelectWeapon();
  //this will add a weapon of the specified type to the bot's inventory. 
  //If the bot already has a weapon of this type only the ammo is added. 
  //(called by the weapon giver-triggers to give a bot a weapon)
  void          AddWeapon(unsigned int weapon_type);
//changes the current weapon to one of the specified type (provided that type
  //is in the bot's possession)
  void          ChangeWeapon(unsigned int type);

  //shoots the current weapon at the given position
  void          ShootAt(Vector2D pos)const;

 Weapon* GetCurrentWeapon()const{return m_pCurrentWeapon;} 
Weapon* GetWeaponFromInventory(int weapon_type);
int           GetAmmoRemainingForWeapon(unsigned int weapon_type);
  
  double         ReactionTime()const{return m_dReactionTime;}

};

#endif
