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
  SDL_Window* m_pWindow;
  SDL_Renderer* m_pRenderer;
  SDL_Event e;
  bool running = true;
  
  
   Game::Instance()->init("Test", 0,0,1455,796,false);
 
  // LevelParser* lp = new LevelParser();
  // lp->parseLevel("assets/test.xml");


  while (running)
    {
     
      
      // Game::Instance()->Update();

		        
				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
					  running = false;
					}
				}
      
				  

				  

    }
  






}

 

