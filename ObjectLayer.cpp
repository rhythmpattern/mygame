#include "ObjectLayer.h"
#include "Game/Entity.h"
#include "2D/Vector2D.h"
#include "Game.h"
#include "Level.h"


ObjectLayer::~ObjectLayer()
{
    for(std::vector<Character*>::iterator it = m_gameObjects.begin(); it != m_gameObjects.end(); ++it)// < m_gameObjects.size(); i++)
    {
        delete (*it);
    }
    m_gameObjects.clear();
}


void ObjectLayer::render()
{
    for(int i = 0; i < m_gameObjects.size(); i++)
   {
       if(m_gameObjects[i]->Pos().x <= Game::Instance()->getGameWidth())
      {
           m_gameObjects[i]->draw();
       }
    }
}

void ObjectLayer::update(Level* pLevel)
{

}
