#ifndef STATE_PARSER_H
#define STATE_PARSER_H

#include <vector>
#include "tinyxml.h"
#include <memory>
#include "GameObjectFactory.h"
#include "TextureManager.h"
#include "Game.h"

class Entity;

class StateParser
{
 public:
  bool parseState(const char* stateFile, std::string stateID, std::vector<Entity*>* pObjects, std::vector<std::string> *pTextureIDs);

 private:
  void parseObjects(TiXmlElement* pStateRoot, std::vector<Entity*>* pObjects);
  void parseTextures(TiXmlElement* pStateRoot, std::vector<std::string>* pTextureIDs);
  
};



#endif
