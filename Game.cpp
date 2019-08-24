#include "Game.h"
#include "ObjectEnumerations.h"
#include "Navigation/PathPlanner.h"
#include "Game/EntityManager.h"
#include "2D/WallIntersectionTests.h"
#include "UserOptions.h"
#include "Messages.h"
#include "GraveMarkers.h"
#include "Scriptor.h"
#include "Goals/Goal_Types.h"
#include "GameObjectFactory.h"
#include "InputHandler.h"
#include "CharManager.h"
#include "PlayState.h"
#include <vector>
#include <string>
#include <list>
#include "GoalFactory.h"
#include "Goals/Goal_Explore.h"
#include "Goals/Goal_MoveToPosition.h"

//uncomment to write object creation/deletion to debug console
//#define  LOG

class Steering;
class Map;
class Door;
class SensoryMemory;
class WeaponSystem;
class MessageDispatcher;
class Projectile;
class Projectile_Shot;
class Shooter;
class Goal_Think;
class Player;
class Character;
class Zombie;
class ProjectileManager;

Game* Game::s_pInstance = 0;
//----------------------------- ctor ------------------------------------------
//-----------------------------------------------------------------------------
Game::Game():m_pSelectedBot(NULL),
                         m_bPaused(false),
                         m_bRemoveABot(false),
                         m_pMap(NULL),
                         m_pPathManager(NULL)
{
  GameObjectFactory::Instance()->registerType("Character" , new CharacterCreator());
    GoalFactory::Instance()->registerType("GoalExplore" , new GoalExploreCreator());
    GoalFactory::Instance()->registerType("GoalMove" , new GoalMoveCreator());
   
    deltaTime = 0;
}


//------------------------------ dtor ----------------------------------------
//-----------------------------------------------------------------------------
Game::~Game()
{
 
  SDL_Quit();
 
}


bool Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen){

 
  m_levelFiles.push_back(script->getString("level"));
   m_currentLevel = 1;
  
  
 int flags = 0;
 m_bRunning = true;
 m_bPaused = false;
    // store the game width and height
    m_gameWidth = width;
    m_gameHeight = height;

    //GraveManager::Instance()->load();

    
    if(fullscreen)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }
    
    // attempt to initialise SDL
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
      
      std::cout << "SDL init success\n";
        // init the window
        m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, SDL_WINDOW_SHOWN);
        
        if(m_pWindow != 0) // window init success
        {
            std::cout << "window creation success\n";
            m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
            
            if(m_pRenderer != 0) // renderer init success
            {
                std::cout << "renderer creation success\n";
                SDL_SetRenderDrawColor(m_pRenderer,0,0,0,255);
            }
            else
            {
                std::cout << "renderer init fail\n";
                return false; // renderer init fail
            }
        }
        else
        {
            std::cout << "window init fail\n";
            return false; // window init fail
        }
    }
    else
    {
        std::cout << "SDL init fail\n";
        return false; // SDL init fail
    }


    
    
     m_pGameStateMachine = new GameStateMachine();
     m_pGameStateMachine->changeState(new PlayState());

 
  
   return true;

    
}



void Game::Render()
{ SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(m_pRenderer);
  SDL_SetRenderDrawColor(m_pRenderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
              
  
 
  m_pGameStateMachine->render();
  SDL_RenderPresent(m_pRenderer);
 
}




//---------------------------- Clear ------------------------------------------
//
//  deletes all the current objects ready for a map load
//-----------------------------------------------------------------------------
void Game::Clear()
{
#ifdef LOG
    std::cout << "\n------------------------------ Clearup -------------------------------" << endl;
#endif


  

}

void Game::handleInput()
{
  InputHandler::Instance()->update();
}

//-------------------------------- Update -------------------------------------
//
//  calls the update function of each entity
//-----------------------------------------------------------------------------
void Game::Update()
{
  
    
    //don't update if the user has paused the game
  if (m_bPaused) return;
  
  m_pGameStateMachine->update(); 


  
}



