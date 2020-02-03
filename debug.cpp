#include <iostream>
#include <cstdlib>
#include "Game.h"
#include "Map.h"
#include <SDL2/SDL.h>
#include <map>
#include "TextureManager.h"
#include "GameObjectFactory.h"
#include "BLayer.h"
#include "Scriptor.h"
#include "CollisionTests.h"
#include "Time/advanced_timers.h"

int main( int argc, char* args[] )
{
 
  // freopen("CON", "w", stdout);
  SDL_Window* m_pWindow;
  SDL_Renderer* m_pRenderer;
  SDL_Event e;
  bool running = true;
  Scriptor::Instance();
  LTimer fpsTimer;
   fpsTimer.start();
  int fpsCount = 0;
  double startCount = 0;
  double endCount = 0;
  double avgFPS = 0;
  int SCREEN_TICKS = (1000/60);
  Game::Instance()->init("Test", 0,0,script->getNum("width"),script->getNum("height"),false);
  
  //LevelParser* lp = new LevelParser();
  //lp->parseLevel("assets/test.xml");
 

   while (Game::Instance()->Running())
     { 
       startCount = (double)SDL_GetTicks();    
       avgFPS = fpsCount/(fpsTimer.getTicks()/1000.f);
       if (avgFPS > 2000000)
	 avgFPS = 0;
       //std::cout << avgFPS << "\n";
       Game::Instance()->handleInput();
      Game::Instance()->Update();
      Game::Instance()->Render();
      ++fpsCount;
      //std::cout << "endcount is: " << endCount << "\n";
      // if (endCount < SCREEN_TICKS)
      //	SDL_Delay(SCREEN_TICKS - endCount);
      endCount = (double)SDL_GetTicks();
      float dif = endCount - startCount;
      Game::Instance()->setDeltaTime(dif);
      

    }
  
  Game::Instance()->Clear();
  




}

 

