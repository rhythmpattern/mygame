#include "Trigger_HealthGiver.h"
#include "../misc/Stream_Utility_Functions.h"
#include <fstream>
#include "../constants.h"
#include "../ObjectEnumerations.h"


///////////////////////////////////////////////////////////////////////////////
Trigger_HealthGiver::Trigger_HealthGiver(std::ifstream& datafile):
      
     Trigger_Respawning<Character>(GetValueFromStream<int>(datafile))
{
  Read(datafile);
}


void Trigger_HealthGiver::Try(Character* pBot)
{
  if (isActive() && isTouchingTrigger(pBot->Pos(), pBot->BRadius()))
  {
    pBot->IncreaseHealth(m_iHealthGiven);

    Deactivate();
  } 
}




void Trigger_HealthGiver::Read(std::ifstream& in)
{
  double x, y, r;
  int GraphNodeIndex;
  
  in >> x >> y  >> r >> m_iHealthGiven >> GraphNodeIndex;

  SetPos(Vector2D(x,y)); 
  SetBRadius(r);
  SetGraphNodeIndex(GraphNodeIndex);

  //create this trigger's region of fluence
  AddCircularTriggerRegion(Pos(), 10);

  SetRespawnDelay((unsigned int)(2));
  SetEntityType(type_health);
}
