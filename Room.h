#ifndef ROOM_H
#define ROOM_H

#include <string>
#include <vector>
#include "Map.h"

class Room
{
 public:
  Room(std::string mapName);
  ~Room();
  void Update();
  void Render();
  bool LoadMap(const std::string& filename);
 private:
  Map* m_pMap;
  void Clear();
};


#endif
