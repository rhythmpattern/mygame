#ifndef PROJECTILE_MANAGER_H
#define PROJECTILE_MANAGER_H

#include <vector>
#include "Armory/Projectile.h"
#include "Character.h"
#include "Armory/Projectile_Shot.h"

class ProjectileManager
{

 public:
   static ProjectileManager* Instance()
  {
    if(pInstance == 0)
      {
	pInstance = new ProjectileManager();
      }
    return pInstance;
  }
   void AddShot(Character* shooter, Vector2D target);
   void Clear();
   void Update();
 private:

   ProjectileManager(){}
   ~ProjectileManager(){}
   
   static ProjectileManager* pInstance;
   std::list<Projectile*> m_Projectiles;

};


#endif
