#ifndef CHAR_MANAGER_H
#define CHAR_MANAGER_H

#include <vector>
#include "Character.h"
#include "GraveManager.h"
#include "Game.h"
#include "Game/EntityManager.h"
#include "SteeringBehaviors.h"
#include "Player.h"
#include "LoadParams.h"

class CharManager
{
 public:

  static CharManager* Instance()
  {
    if (pInstance == 0)
      {
      pInstance = new CharManager();
      }

    return pInstance;
  }
  CharManager();
 CharManager(Room* pRoom);
  ~CharManager();
  void Clear();
  void Update();
  void Render();
   void AddChars(unsigned int NumCharsToAdd);
  void AddChar(Character* pChar , LoadParams* lp);
  const std::vector<Character*> GetAllChars()const{ return m_Chars;}
 private:
  static CharManager* pInstance;
  Room* m_pRoom;
  std::vector<Character*> m_Chars;
  bool AttemptToAddChar(Character* pChar);

};

#endif
