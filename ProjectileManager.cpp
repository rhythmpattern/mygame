#include "ProjectileManager.h"

ProjectileManager* ProjectileManager::pInstance = 0;

void ProjectileManager::Clear()
{
   //delete any active projectiles
  std::list<Projectile*>::iterator curW = m_Projectiles.begin();
  for (curW; curW != m_Projectiles.end(); ++curW)
  {
#ifdef LOG
    std::cout << "deleting projectile id: " << (*curW)->ID() << endl;
#endif

    delete *curW;
  }

  //clear the containers
  m_Projectiles.clear();


  
}
