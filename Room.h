#ifndef ROOM_H
#define ROOM_H

#include <string>
#include <vector>

class Map;
class Character;
class GraveMarkers;

class Room
{
 public:
  Room(std::string mapName);
  ~Room();
  void Update();
  void Render();

 private:
  Map* m_pMap;
  std::vector<Character*> m_Chars;
  void clear();
  void NotifyAllCharsOfRemoval(Character* pRemovedChar)const;
  GraveMarkers* m_pGraveMarkers;
  void LoadMap(const std::string& FileName);
};


#endif
