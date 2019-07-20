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
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "GameStateMachine.h"
#include "GameState.h"
#include "PlayState.h"
#include "GameObjectFactory.h"

class Entity;
class Projectile;
class Map;
class GraveMarkers;

class Game {


  private:

    bool m_bRunning;
    Map* m_pMap;
    std::vector<Character*>       m_Bots; 
    Character* m_pSelectedBot;
    PathManager<PathPlanner>* m_pPathManager;
    bool m_bPaused;
    bool m_bRemoveABot;
    void UpdateTriggers();
   
    bool AttemptToAddBot(Character* pBot);
    void NotifyAllBotsOfRemoval(Character* pRemovedBot)const;
  static Game* s_pInstance;
  int m_gameWidth;
  int m_gameHeight;
  
    SDL_Window* m_pWindow;
    SDL_Renderer* m_pRenderer;
    
    GameStateMachine* m_pGameStateMachine;
      std::vector<std::string> m_levelFiles;
      int m_currentLevel;
      Player* m_pPlayer;
public:
 
Game();
~Game();
 void Clear();
 static Game* Instance()
    {
        if(s_pInstance == 0)
        {
            s_pInstance = new Game();
            return s_pInstance;
        }
        
        return s_pInstance;
    }
 GameStateMachine* getStateMachine() {return m_pGameStateMachine;}
  int getCurrentLevel(){return m_currentLevel;}
  std::vector<std::string> getLevelFiles() {return m_levelFiles;}
SDL_Renderer* getRenderer() const { return m_pRenderer; }
    SDL_Window* getWindow() const { return m_pWindow; }
    int getGameWidth(){return m_gameWidth;}
    int getGameHeight(){return m_gameHeight;}
  Room* getRoom() { getStateMachine()->getGameStates().back()->getLevel()->getRooms()->back();}

    void Render();
void Update();
bool LoadMap(const std::string& FileName);
 bool Running() {return m_bRunning;}

 bool init(const char* title, int xpos, int ypos, int width , int height, bool fullscreen);
void AddBots(unsigned int NumBotsToAdd);
void RemoveBot();
 void Quit() {m_bRunning = false;}
void AddShooter(Character* shooter, Vector2D target);

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
 void handleInput();
Character* GetPlayer()const{return m_pPlayer;}
const Map* const GetMap()const{return m_pMap;}
Map* const GetMap(){return m_pMap;}
const std::vector<Character*> GetAllBots()const{return m_Bots;}
int GetNumBots()const{return m_Bots.size();}
PathManager<PathPlanner>* const    GetPathManager(){return m_pPathManager;}


void TagCharactersWithinViewRange(Entity* pBot , double range)
		{TagNeighbors(pBot, m_Bots, range);}




 Player* GetPlayer() { return m_pPlayer;} 





    
};



#endif
