#ifndef GAME_H
#define GAME_H

#include <vector>
#include <string>
#include <list>

#include "Graph/SparseGraph.h"
#include "ObjectEnumerations.h"
#include "2D/Wall2D.h"
#include "misc/utils.h"
#include "Character.h"
#include "Navigation/PathManager.h"
#include "Game/EntityFunctionTemplates.h"


class Entity;
class Projectile;
class Map;
class GraveMarkers;

class Game {


  private:

   
    Map* m_pMap;
    std::vector<Character*>       m_Bots; 
    Character* m_pSelectedBot;
    PathManager<PathPlanner>* m_pPathManager;
    bool m_bPaused;
    bool m_bRemoveABot;
    void UpdateTriggers();
    void Clear();
    bool AttemptToAddBot(Character* pBot);
    void NotifyAllBotsOfRemoval(Character* pRemovedBot)const;
     //when a bot is killed a "grave" is displayed for a few seconds. This
  //class manages the graves
  GraveMarkers*                    m_pGraveMarkers;
//this list contains any active projectiles
  std::list<Projectile*>     m_Projectiles;



public:
 
Game();
~Game();

void Update();
bool LoadMap(const std::string& FileName);



void AddBots(unsigned int NumBotsToAdd);
void RemoveBot();

void AddShooter(Character* shooter, Vector2D target);
void AddShot(Character* shooter, Vector2D target);

bool isPathObstructed(Vector2D A, Vector2D B, double BoundingRadius = 0)const;
std::vector<Character*> GetAllBotsInFOV(const Character* pBot)const;
bool isSecondVisibleToFirst(const Character* pFirst,
			    const Character* pSecond)const;
bool isLOSOkay(Vector2D A, Vector2D B)const;
double GetDistanceToClosestWall(Vector2D Origin, Vector2D Heading)const;
Vector2D GetPosOfClosestSwitch(Vector2D botPos, unsigned int doorID)const;
Character* GetBotAtPosition(Vector2D CursorPos)const;
void TogglePause(){m_bPaused = !m_bPaused;}
void ExorciseAnyPossessedBot();
void GetPlayerInput()const;
Character* PossessedBot()const{return m_pSelectedBot;}
const Map* const GetMap()const{return m_pMap;}
Map* const GetMap(){return m_pMap;}
const std::vector<Character*> GetAllBots()const{return m_Bots;}
int GetNumBots()const{return m_Bots.size();}
PathManager<PathPlanner>* const    GetPathManager(){return m_pPathManager;}


void TagCharactersWithinViewRange(Entity* pBot , double range)
		{TagNeighbors(pBot, m_Bots, range);}










    
};



#endif
