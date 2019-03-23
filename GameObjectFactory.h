#ifndef GAME_OBJECT_FACTORY_H
#define GAME_OBJECT_FACTORY_H

#include <string>
#include <map>
#include "Game/Entity.h"

class BaseCreator
{
 public:
  virtual Entity* createGameObject() const = 0;
  virtual ~BaseCreator() {}




  
};

class GameObjectFactory
{
 public:
  static GameObjectFactory* Instance()
  {
    if(pInstance == 0)
      {
	pInstance = new GameObjectFactory();
      }
    return pInstance;
  }



  
  bool registerType(std::string typeID, BaseCreator* pCreator)
  {
    std::map<std::string, BaseCreator*>::iterator it = m_creators.find(typeID);

    if(it != m_creators.end())
      {
	delete pCreator;
      }
    m_creators[typeID] = pCreator;
    return true;
  }




  Entity* create(std::string typeID)
  {
    std::map<std::string, BaseCreator*>::iterator it = m_creators.find(typeID);

    if(it == m_creators.end())
      {
	std::cout << "could not find type: " << typeID << "\n";
	return NULL;
      }
    BaseCreator* pCreator = (*it).second;
    return pCreator->createGameObject();
  }

 private:
  GameObjectFactory() {}
  ~GameObjectFactory() {}

  std::map<std::string, BaseCreator*> m_creators;

  static GameObjectFactory* pInstance;
  

};



#endif
