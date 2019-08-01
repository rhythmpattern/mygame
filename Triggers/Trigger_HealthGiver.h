#ifndef HEALTH_GIVER_H
#define HEALTH_GIVER_H
#pragma warning (disable:4786)
//-----------------------------------------------------------------------------
//
//  Name:     Trigger_HealthGiver.h
//
//  Author:   Shaun Hose
//
//  Desc:     If a bot runs over an instance of this class its health is
//            increased. 
//
//-----------------------------------------------------------------------------
#include "Trigger_Respawning.h"
#include "TriggerRegion.h"
#include <iosfwd>
#include "../Character.h"



class Trigger_HealthGiver : public Trigger_Respawning<Character>
{
private:

  //the amount of health an entity receives when it runs over this trigger
  int   m_iHealthGiven;
  
public:

  Trigger_HealthGiver(std::istringstream& datafile);

  //if triggered, the bot's health will be incremented
  void Try(Character* pBot);
   void load(const LoadParams* pParams){}
  //draws a box with a red cross at the trigger's location
  void Render();

  void Read (std::istringstream& is);
};



#endif
