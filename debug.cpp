#include <iostream>
#include "Game.h"
#include "Map.h"
#include <SDL.h>
#include <map>
#include "TextureManager.h"
#include "GameObjectFactory.h"
#include "BLayer.h"
#include <assert.h>
//#include <android/log.h>

int main( int argc, char* args[] )
{
  //freopen("CON", "w", stdout);
 
  
  // SDL_Event e;
   bool running = true;
    Game::Instance()->init("Test", 0,0,640,480,false);
    //LevelParser* lp = new LevelParser();
     //lp->parseLevel("DM1.tmx");
   
    
  
   while (Game::Instance()->Running())
    {
     
       Game::Instance()->handleInput();
         Game::Instance()->Update();
      	Game::Instance()->Render();


    }
  
    Game::Instance()->Clear();
  
    

 while(true){}

}

 

