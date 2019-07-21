#include "PauseState.h"
#include "Game.h"
#include "InputHandler.h"

const std::string PauseState::s_pauseID = "PAUSE";


void PauseState::update()
{
  std::cout << "UPDATING\n";
  if (!m_exiting && InputHandler::Instance()->isKeyDown(SDL_SCANCODE_B))
    { m_exiting = true;
      Game::Instance()->getStateMachine()->popState();
    }
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
      //Game::Instance()->TogglePause();  
    #ifdef debug
    std::cout << "entering PauseState\n";
    #endif
    return true;
}

bool PauseState::onExit()
{
    m_exiting = true;
    Game::Instance()->TogglePause();
  
    std::cout << "exiting PauseState\n";
    return true;
}
