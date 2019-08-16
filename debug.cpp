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

int main( int argc, char* args[] )
{srand(time(NULL));
  // freopen("CON", "w", stdout);
  SDL_Window* m_pWindow;
  SDL_Renderer* m_pRenderer;
  SDL_Event e;
  bool running = true;
  Scriptor::Instance();


  Game::Instance()->init("Test", 0,0,script->getNum("width"),script->getNum("height"),false);
 
  //LevelParser* lp = new LevelParser();
  //lp->parseLevel("assets/test.xml");
 

  
   while (Game::Instance()->Running())
    {
     
       Game::Instance()->handleInput();
      Game::Instance()->Update();
      Game::Instance()->Render();


    }
  
  Game::Instance()->Clear();
  




}

 

