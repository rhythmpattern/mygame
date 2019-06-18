#include <iostream>
#include "Game.h"
#include "Map.h"
#include <SDL2/SDL.h>
#include <map>
#include "TextureManager.h"
#include "GameObjectFactory.h"
#include "BLayer.h"

int main( int argc, char* args[] )
{
  // freopen("CON", "w", stdout);
  SDL_Window* m_pWindow;
  SDL_Renderer* m_pRenderer;
  SDL_Event e;
  bool running = true;
  Game::Instance()->init("Test", 0,0,1455,796,false);
 
  //LevelParser* lp = new LevelParser();
  // lp->parseLevel("assets/test.xml");
 

 
  while (Game::Instance()->Running())
    {
     
      Game::Instance()->handleInput();
       Game::Instance()->Update();
       Game::Instance()->Render();


    }

   Game::Instance()->Clear();





}

 

