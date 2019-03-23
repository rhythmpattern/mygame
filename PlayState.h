#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include "GameState.h"
#include "Level.h"
#include <vector>

class Entity;
class SDLGameObject;
class Level;

class PlayState : public GameState
{
public:
    
    virtual ~PlayState() { delete pLevel; }
    
    virtual void update();
    virtual void render();
    
    virtual bool onEnter();
    virtual bool onExit();
    
    virtual std::string getStateID() const { return s_playID; }
    
private:
    
    static const std::string s_playID;
    
    
    std::vector<Entity*> m_gameObjects;
    
    Level* pLevel;
};


#endif
