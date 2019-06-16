#include "PauseState.h"
#include "Game.h"

const std::string PauseState::s_pauseID = "PAUSE";


void PauseState::update()
{
   
}

void PauseState::render()
{
    if(m_loadingComplete)
    {
      TextureManager::Instance()->drawFrame("pause",  0, 0, 1455, 796,0,0, Game::Instance()->getRenderer(),0,100);
       
    }
}

bool PauseState::onEnter()
{
 
 
      m_loadingComplete = true;
  
    #ifdef debug
    std::cout << "entering PauseState\n";
    #endif
    return true;
}

bool PauseState::onExit()
{
    m_exiting = true;
    
  
    std::cout << "exiting PauseState\n";
    return true;
}
