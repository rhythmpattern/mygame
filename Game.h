#ifndef GAME_H
#define GAME_H




#include "misc/utils.h"
#include "Navigation/PathManager.h"
#include "Game/EntityFunctionTemplates.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "2D/Vector2D.h"
#include "GameStateMachine.h"

class Entity;
class Map;
class Character;
class Player;
class Room;

class Game {


  private:
  
    bool m_bRunning;
    Map* m_pMap;
    std::vector<Character*>       m_Bots; 
    Character* m_pSelectedBot;
    PathManager* m_pPathManager;
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
   float deltaTime;
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
  float getDeltaTime() {return deltaTime;}
  void setDeltaTime(float amt) {deltaTime = amt;}
    void Render();
void Update();
 bool Running() {return m_bRunning;}

  bool init(const char* title, int xpos, int ypos, int width , int height, bool fullscreen);
 void Quit() {m_bRunning = false;}
void TogglePause(){m_bPaused = !m_bPaused;}
 void handleInput();





    
};



#endif
