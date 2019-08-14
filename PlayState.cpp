#include <iostream>
#include "PlayState.h"
//#include "GameOverState.h"
#include "PauseState.h"
#include "Game.h"
#include "InputHandler.h"
//#include "LevelParser.h"
#include "Level.h"
//#include "BulletHandler.h"
#include "GraveManager.h"
#include "ProjectileManager.h"
#include "CharManager.h"
#include "LevelCreator.h"
//#define debug


const std::string PlayState::s_playID = "PLAY";

void PlayState::update()
{
    if(m_loadingComplete && !m_exiting)
    {
      
        if(InputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE))
	  {   
            Game::Instance()->Quit();
        }

	if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_RETURN))
	  {
	    m_exiting = true; 
	    Game::Instance()->getStateMachine()->pushState(new PauseState());
	    
	  }
       
//        if(TheInputHandler::Instance()->getButtonState(0, 8))
//        {
//            TheGame::Instance()->getStateMachine()->pushState(new PauseState());
//        }
        
      //  TheBulletHandler::Instance()->updateBullets();
        
      //   if(TheGame::Instance()->getPlayerLives() == 0)
      //   {
      //       TheGame::Instance()->getStateMachine()->changeState(new GameOverState());
      //   }
        
       if(pLevel != 0)
        {
            pLevel->update();
        }
    }
}

void PlayState::render()
{
    if(m_loadingComplete)
    {
      //TextureManager::Instance()->drawFrame("background",  0, 0, 1455, 796,0,0, Game::Instance()->getRenderer(),0,100);
        if(pLevel != 0)
	  { 
	   pLevel->render();
	  
        }

	//  for(int i = 0; i < TheGame::Instance()->getPlayerLives(); i++)
	//   {
	//       TheTextureManager::Instance()->drawFrame("lives", i * 30, 0, 32, 30, 0, 0, TheGame::Instance()->getRenderer(), 0.0, 255);
	//   }
	//    
	//   TheBulletHandler::Instance()->drawBullets();
    }
}

bool PlayState::onEnter()
{
  //Game::Instance()->setPlayerLives(3);
  if (!m_loadingComplete) {
   
   
    pLevel = LevelCreator::Instance()->Create();
   
  
   // TextureManager::Instance()-> load("assets/background.png", "background", Game::Instance()->getRenderer());
   // TextureManager::Instance()-> load("assets/isaac.png", "isaac", Game::Instance()->getRenderer());
   // TextureManager::Instance()->load("assets/dot.bmp","dot",Game::Instance()->getRenderer());
  //  TheTextureManager::Instance()->load("assets/bullet1.png", "bullet1", TheGame::Instance()->getRenderer());
  //  TheTextureManager::Instance()->load("assets/bullet2.png", "bullet2", TheGame::Instance()->getRenderer());
  //  TheTextureManager::Instance()->load("assets/bullet3.png", "bullet3", TheGame::Instance()->getRenderer());
  //  TheTextureManager::Instance()->load("assets/lives.png", "lives", TheGame::Instance()->getRenderer());

      m_loadingComplete = true;
  }
    if(pLevel != 0)
    {
      
        m_loadingComplete = true;
    }
    #ifdef debug
    std::cout << "entering PlayState\n";
    #endif
    return true;
}

bool PlayState::onExit()
{
    m_exiting = true;
    
    InputHandler::Instance()->reset();
    //TheBulletHandler::Instance()->clearBullets();
    
    std::cout << "exiting PlayState\n";
    return true;
}

void PlayState::resume()
{
  std::cout << "resuming Playstate";
  Game::Instance()->TogglePause();
  m_exiting = false; 
}
