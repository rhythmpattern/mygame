
#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <string>
#include <vector>
#include "Level.h"

class GameState
{
public:
    
    virtual ~GameState() {}
    
    virtual void update() = 0;
    virtual void render() = 0;
    
    virtual bool onEnter() = 0;
    virtual bool onExit() = 0;
    
    virtual void resume() {}
  Level* getLevel() { return pLevel;}
    
    virtual std::string getStateID() const = 0;
    
protected:
    
    GameState() : m_loadingComplete(false), m_exiting(false)
    {
        
    }
  Level* pLevel;
    bool m_loadingComplete;
    bool m_exiting;
    
    std::vector<std::string> m_textureIDList;
};

#endif
