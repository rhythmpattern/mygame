#ifndef PAUSESTATE_H
#define PAUSESTATE_H

#include "GameState.h"
#include "Level.h"
#include <vector>
#include "TextureManager.h"

class Entity;
class SDLGameObject;
class Level;

class PauseState : public GameState
{
public:
    
    virtual ~PauseState() { delete pLevel; }
    
    virtual void update();
    virtual void render();
    
    virtual bool onEnter();
    virtual bool onExit();
    
    virtual std::string getStateID() const { return s_pauseID; }
    
private:
    
    static const std::string s_pauseID;
    
    
    std::vector<Entity*> m_gameObjects;
    
    Level* pLevel;
};


#endif
