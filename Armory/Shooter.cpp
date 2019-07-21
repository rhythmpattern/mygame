#include "Shooter.h"
#include "../Character.h"
#include "../Game.h"
#include "../Map.h"
#include "../Fuzzy/FuzzyOperators.h"
#include "../Scriptor.h"
#include "../ProjectileManager.h"
#include "Weapon.h"

//--------------------------- ctor --------------------------------------------
//-----------------------------------------------------------------------------
Shooter::Shooter(Character*   owner):

                      Weapon(type_shooter,
			     script->getInt("blasterdefaultrounds"),
			     script->getInt("blastermaxroundscarried"),
			     script->getNum("blasterfiringfreq"),
			     script->getNum("blasteridealrange"),
			     script->getNum("boltmaxspeed"),
                                   owner)
{
  //setup the vertex buffer
  const int NumWeaponVerts = 4;
  const Vector2D weapon[NumWeaponVerts] = {Vector2D(0, -1),
                                           Vector2D(10, -1),
                                           Vector2D(10, 1),
                                           Vector2D(0, 1)
                                           };

  
  for (int vtx=0; vtx<NumWeaponVerts; ++vtx)
  {
    m_vecWeaponVB.push_back(weapon[vtx]);
  }

  //setup the fuzzy module
  //InitializeFuzzyModule();
}



//------------------------------ ShootAt --------------------------------------

inline void Shooter::ShootAt(Vector2D pos)
{
 
  if (isReadyForNextShot())
  {
    
    //fire!
    ProjectileManager::Instance()->AddShot(m_pOwner, pos);

    UpdateTimeWeaponIsNextAvailable();

    //add a trigger to the game so that the other bots can hear this shot
    //(provided they are within range)
     m_pOwner->GetRoom()->GetMap()->AddSoundTrigger(m_pOwner, script->getNum("blastersoundrange"));
  }
}



//---------------------------- Desirability -----------------------------------
//
//-----------------------------------------------------------------------------
double Shooter::GetDesirability(double DistToTarget)
{
  //fuzzify distance and amount of ammo
  m_FuzzyModule.Fuzzify("DistToTarget", DistToTarget);

   m_dLastDesirabilityScore = m_FuzzyModule.DeFuzzify("Desirability", FuzzyModule::max_av);

  return m_dLastDesirabilityScore;
}

//----------------------- InitializeFuzzyModule -------------------------------
//
//  set up some fuzzy variables and rules
//-----------------------------------------------------------------------------
void Shooter::InitializeFuzzyModule()
{
  FuzzyVariable& DistToTarget = m_FuzzyModule.CreateFLV("DistToTarget");

  FzSet Target_Close = DistToTarget.AddLeftShoulderSet("Target_Close",0,25,150);
  FzSet Target_Medium = DistToTarget.AddTriangularSet("Target_Medium",25,150,300);
  FzSet Target_Far = DistToTarget.AddRightShoulderSet("Target_Far",150,300,1000);

  FuzzyVariable& Desirability = m_FuzzyModule.CreateFLV("Desirability"); 
  FzSet VeryDesirable = Desirability.AddRightShoulderSet("VeryDesirable", 50, 75, 100);
  FzSet Desirable = Desirability.AddTriangularSet("Desirable", 25, 50, 75);
  FzSet Undesirable = Desirability.AddLeftShoulderSet("Undesirable", 0, 25, 50);
  FuzzyTerm t = FzVery(Undesirable);
  m_FuzzyModule.AddRule(Target_Close, Desirable);
  m_FuzzyModule.AddRule(Target_Medium, t);
  m_FuzzyModule.AddRule(Target_Far, FzVery(Undesirable));
}



