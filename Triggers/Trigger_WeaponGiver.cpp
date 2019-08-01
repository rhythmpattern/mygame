#include "Trigger_WeaponGiver.h"
#include "../misc/Stream_Utility_Functions.h"
#include <fstream>
#include "../constants.h"
#include "../ObjectEnumerations.h"
#include "../WeaponSystem.h"


///////////////////////////////////////////////////////////////////////////////

Trigger_WeaponGiver::Trigger_WeaponGiver(std::istringstream& datafile):
      
          Trigger_Respawning<Character>(GetValueFromStream<int>(datafile))
{
  Read(datafile);

  //create the vertex buffer for the rocket shape
  const int NumRocketVerts = 8;
  const Vector2D rip[NumRocketVerts] = {Vector2D(0, 3),
                                       Vector2D(1, 2),
                                       Vector2D(1, 0),
                                       Vector2D(2, -2),
                                       Vector2D(-2, -2),
                                       Vector2D(-1, 0),
                                       Vector2D(-1, 2),
                                       Vector2D(0, 3)};
  
  for (int i=0; i<NumRocketVerts; ++i)
  {
    m_vecRLVB.push_back(rip[i]);
  }
}


void Trigger_WeaponGiver::Try(Character* pBot)
{
  if (this->isActive() && this->isTouchingTrigger(pBot->Pos(), pBot->BRadius()))
  {
    pBot->GetWeaponSys()->AddWeapon(EntityType());

    Deactivate();
  } 
}




void Trigger_WeaponGiver::Read(std::istringstream& in)
{
  double x, y, r;
  int GraphNodeIndex;
  
  in >>  x >> y  >> r >> GraphNodeIndex;

  SetPos(Vector2D(x,y)); 
  SetBRadius(r);
  SetGraphNodeIndex(GraphNodeIndex);

  //create this trigger's region of fluence
  AddCircularTriggerRegion(Pos(), 10);


  SetRespawnDelay((unsigned int)(10 * FrameRate));
}



