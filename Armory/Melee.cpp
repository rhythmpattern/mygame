#include "Melee.h"
#include "../Character.h"
#include "../Game.h"
#include "../Fuzzy/FuzzyOperators.h"
#include "../Messages.h"
#include "../Messaging/MessageDispatcher.h"

//--------------------------- ctor --------------------------------------------
//-----------------------------------------------------------------------------
Melee::Melee(Character*   owner):

                      Weapon(type_melee,
                                   10,
                                   10,
                                   1,
                                   1,
                                   1,
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
  m_iDamageInflicted = 5;
  //setup the fuzzy module
  //InitializeFuzzyModule();
}



//------------------------------ ShootAt --------------------------------------

inline void Melee::ShootAt(Vector2D pos)
{ 
  if (isReadyForNextShot())
    {
    //fire!
      if((pos - m_pOwner->Pos()).Length() < m_pOwner->BRadius()*5) 
	 Dispatcher->DispatchMsg(SEND_MSG_IMMEDIATELY,
				 m_pOwner->ID(),
				 m_pOwner->GetTargetSys()->GetTarget()->ID(),
                              Msg_TakeThatMF,
                              (void*)&m_iDamageInflicted);
   

    UpdateTimeWeaponIsNextAvailable();

    //add a trigger to the game so that the other bots can hear this shot
    //(provided they are within range)
    m_pOwner->GetRoom()->GetMap()->AddSoundTrigger(m_pOwner, 10);
  }
}



//---------------------------- Desirability -----------------------------------
//
//-----------------------------------------------------------------------------
double Melee::GetDesirability(double DistToTarget)
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
void Melee::InitializeFuzzyModule()
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



