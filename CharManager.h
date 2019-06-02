#ifndef CHAR_MANAGER_H
#define CHAR_MANAGER_H

#include <vector>
#include "Character.h"
#include "GraveManager.h"
#include "Game.h"
#include "Game/EntityManager.h"
#include "SteeringBehaviors.h"

class CharManager
{
 public:
  CharManager();
  ~CharManager();
  void Clear();
  void Update();
 private:
  std::vector<Character*> m_Chars;
  bool AttemptToAddChar(Character* pChar);
 void AddChars(unsigned int NumCharsToAdd);
};

#endif
