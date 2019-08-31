#ifndef LEVEL_CREATOR_H
#define LEVEL_CREATOR_H

#include "Game.h"
#include "LevelParser.h"

class Level;



class LevelCreator
{
   public:
    static LevelCreator* Instance()
  {
    if(pInstance == 0)
      {
	pInstance = new LevelCreator();
      }
    return pInstance;
  }

  
  LevelCreator();
    ~LevelCreator();


    Level* Create();

 private:
  static  LevelCreator* pInstance;
};

#endif
