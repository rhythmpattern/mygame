#ifndef GRAVE_MANAGER_H
#define GRAVE_MANAGER_H

#include "GraveMarkers.h"


class GraveManager
{
 public:
  static GraveManager* Instance()
  {
    if (pInstance == 0)
      {
	pInstance = new GraveManager();
      }
    return pInstance;
  }

  void Clear();
  void Update();
  void AddGrave(Vector2D pos);
  void load();
 private:
  static GraveManager* pInstance;
  GraveMarkers* m_pGraveMarkers;



  
};



#endif
