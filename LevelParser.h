
#ifndef LEVELPARSER_H
#define LEVELPARSER_H


#include <vector>
#include "tinyxml.h"

class Level;
struct Tileset;
class Layer;
class TileLayer;
class Room;

class LevelParser
{
public:
    
   Level* parseLevel(const char* stateFile);
     Room* m_pRoom;
  Level* pLevel;
private:
 
    void parseTextures(TiXmlElement* pTextureRoot);
     void parseTilesets(TiXmlElement* pTilesetRoot, std::vector<Tileset>* pTilesets);
     void parseObjectLayer(TiXmlElement* pObjectElement, std::vector<Layer*> *pLayers, Level* pLevel);
     void parseTileLayer(TiXmlElement* pTileElement, std::vector<Layer*> *pLayers, const std::vector<Tileset>* pTilesets, std::vector<TileLayer*> *pCollisionLayers);
    
    int m_tileSize;
    int m_width;
    int m_height;
  int numChars;
};



#endif

