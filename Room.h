#ifndef ROOM_H
#define ROOM_H

#include <string>
#include <vector>
#include "Map.h"

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
  bool init(std::string sMap);  
 private:
  CharManager* m_pCharManager; 
  Map* m_pMap;
  Room* m_pNorth;
  Room* m_pEast;
  Room* m_pSouth;
  Room* m_pWest;
};


#endif
