#ifndef GOAL_FACTORY_H
#define GOAL_FACTORY_H

#include <string>
#include <iostream>
#include <map>
#include "Goals/Goal.h"
#include "Character.h"

class GoalCreator
{
 public:
  virtual Goal<Character>* createGoal() const = 0;
  virtual ~GoalCreator() {}




  
};


class GoalFactory
{
 public:
  static GoalFactory* Instance()
  {
    if(pInstance == 0)
      {
	pInstance = new GoalFactory();
      }
    return pInstance;
  }



  
  bool registerType(std::string typeID, GoalCreator* pCreator)
  {
    std::map<std::string, GoalCreator*>::iterator it = m_creators.find(typeID);

    if(it != m_creators.end())
      {
	delete pCreator;
      }
    m_creators[typeID] = pCreator;
    return true;
  }



  
  Goal<Character>* create(std::string typeID)
  {
    std::map<std::string, GoalCreator*>::iterator it = m_creators.find(typeID);

    if(it == m_creators.end())
      {
	std::cout << "could not find type: " << typeID << "\n";
	return NULL;
      }
    GoalCreator* pCreator = (*it).second;
    return pCreator->createGoal();
  }

 private:
  GoalFactory() {}
  ~GoalFactory() {}

  std::map<std::string, GoalCreator*> m_creators;

  static GoalFactory* pInstance;
  

};



#endif
