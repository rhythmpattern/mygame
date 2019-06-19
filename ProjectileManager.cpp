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

void ProjectileManager::Update()
{
   //update any current projectiles
  std::list<Projectile*>::iterator curW = m_Projectiles.begin();
  while (curW != m_Projectiles.end())
  {
    
    //test for any dead projectiles and remove them if necessary
    if (!(*curW)->isDead() && !(*curW) == NULL)
    {
      (*curW)->Update();
     

      ++curW;
    }
    else
    {    
      delete *curW;

      curW = m_Projectiles.erase(curW);
    }   
  }
}


void ProjectileManager::Render()
{
  std::list<Projectile*>::iterator curW = m_Projectiles.begin();
  while (curW != m_Projectiles.end())
    { if(!(*curW)->isDead() && !(*curW)==NULL)
      (*curW)->Render();
      ++curW;
    }
}

void ProjectileManager::AddShot(Character* shooter, Vector2D target)
{
  
  Projectile* rp = new Projectile_Shot(shooter, target);

  m_Projectiles.push_back(rp);
 
  #ifdef LOG
  // std::cout << "Adding a shot " << rp->ID() << " at pos " << rp->Pos() << "\n";
  #endif
}
