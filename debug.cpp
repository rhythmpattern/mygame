#include <iostream>
#include "Game.h"
#include "Map.h"
#include <SDL2/SDL.h>
#include <map>
#include "TextureManager.h"
#include "GameObjectFactory.h"

int main( int argc, char* args[] )
{
  SDL_Window* m_pWindow;
  SDL_Renderer* m_pRenderer;
  SDL_Event e;
  bool running = true;
   Game* game = Game::Instance();
  game->init("Test", 100,100,640,480,false);
  TextureManager::Instance()-> load("assets/bg.png", "lives", game->getRenderer());
  while (running)
    {
      

		        
				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
					  running = false;
					}
				}
      
      SDL_RenderClear(game->getRenderer());
      TextureManager::Instance()->drawFrame("lives",  30, 30, 640, 280,0,0, Game::Instance()->getRenderer(), 0.0,100);
      SDL_RenderPresent(game->getRenderer());

    }
  


  //---------basic input from file -------superceded by XML data driven design.
  /* std::ifstream params("params");
if (params.is_open() && params.good()) {
    std::string buffer;
    while (std::getline(params, buffer)) {
        //Do something about the buffer.
      if (buffer.front() != '-' && !buffer.empty()) {
      
   
   vector<string> results;
   stringstream s(buffer);
   while(!s.eof()) {
      string tmp;
      s >> tmp;
      std::cout << tmp;
   }
   std::cout  <<endl;
      
        //Then clear the buffer once you're done with it.
        buffer.clear();
      }
    };
    }*/

}

 

