#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include "Layer.h"
#include "LevelParser.h"
//#include "Player.h"
//#include "CollisionManager.h"
#include "Map.h"
#include "Navigation/PathManager.h"
#include "Room.h"

//class TileLayer;
class GraveMarkers;
class Projectile;

struct Tileset
{
    int firstGridID;
    int tileWidth;
    int tileHeight;
    int spacing;
    int margin;
    int width;
    int height;
    int numColumns;
    std::string name;
};

class Level
{
public:
    
    ~Level();
    
    void update();
    void render();
    
     std::vector<Tileset>* getTilesets() { return &m_tilesets; }
     std::vector<Layer*>* getLayers() { return &m_layers; }    
     std::vector<TileLayer*>* getCollisionLayers() { return &m_collisionLayers; }
     std::vector<Room*>* getRooms(){ return &m_rooms;}     
     const std::vector<TileLayer*>& getCollidableLayers() { return m_collisionLayers; }
    
     // Player* getPlayer() { return m_pPlayer; }
     // void setPlayer(Player* pPlayer) { m_pPlayer = pPlayer; }
    
private:
    
    friend class LevelParser;
    Room* currentRoom;
    Level();
    
    //  Player* m_pPlayer;
    Map* m_pMap;
    std::vector<Character*> m_Bots;
    PathManager* m_pPathManager;
     std::vector<Layer*> m_layers;
     std::vector<Room*> m_rooms;
      std::vector<Tileset> m_tilesets;
     std::vector<TileLayer*> m_collisionLayers;
};

#endif
