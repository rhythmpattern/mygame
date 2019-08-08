#ifndef ROOM_H
#define ROOM_H

#include <string>
#include <vector>
#include "Map.h"
#include "Navigation/PathManager.h"
#include "Door.h"
#include "ProjectileManager.h"
#include "Navigation/PathPlanner.h"

class CharManager;

class Room
{
 public:
  Room();
  ~Room();
  void Update();
  void Render();
  void Clear();
  bool LoadMap(const std::string& filename , int numChars);
  bool init(const std::string sMap);
  void AddChar(Character* pChar);
  void AddChars(unsigned int NumCharsToAdd);
  Map* GetMap() { return m_pMap; }
  bool isSecondVisibleToFirst(const Character* pFirst, const Character* pSecond) const;
  bool isLOSOkay(Vector2D A, Vector2D B)const ;
  bool isPathObstructed(Vector2D A, Vector2D B, double BoundingRadius)const;
  Vector2D GetPosOfClosestSwitch(Vector2D botPos, unsigned int doorID)const;
  void TagCharactersWithinViewRange(Entity* pChar, double range);
  PathManager<PathPlanner>* GetPathManager() { return m_pPathManager;}
  CharManager* GetCharManager() { return m_pCharManager;}
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
