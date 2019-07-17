#ifndef ROOM_H
#define ROOM_H

#include <string>
#include <vector>
#include "Map.h"
#include "Navigation/PathManager.h"
#include "Door.h"

class CharManager;


class Room
{
 public:
  Room(std::string mapName);
  ~Room();
  void Update();
  void Render();
  void Clear();
  bool LoadMap(const std::string& filename);
  bool init(const std::string sMap);
  void AddChar(Character* pChar);
  void AddChars(unsigned int NumCharsToAdd);
 private:
  CharManager* m_pCharManager;
  PathManager<PathPlanner>* m_pPathManager;
  std::vector<Character*> m_Chars;
  Map* m_pMap;
  Room* m_pNorth;
  Room* m_pEast;
  Room* m_pSouth;
  Room* m_pWest;
};


#endif
