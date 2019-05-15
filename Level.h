#ifndef LEVEL_H
#define LEVEL_H

#include <iostream>
#include <vector>
#include "Layer.h"
#include "LevelParser.h"
//#include "Player.h"
//#include "CollisionManager.h"
#include "Map.h"
#include "Navigation/PathManager.h"

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
    
      const std::vector<TileLayer*>& getCollidableLayers() { return m_collisionLayers; }
    
     // Player* getPlayer() { return m_pPlayer; }
     // void setPlayer(Player* pPlayer) { m_pPlayer = pPlayer; }
    
private:
    
    friend class LevelParser;
    
    Level();
    
    //  Player* m_pPlayer;
    Map* m_pMap;
    std::vector<Character*> m_Bots;
    PathManager<PathPlanner>* m_pPathManager;
    GraveMarkers* m_pGraveMarkers;
    std::list<Projectile*>     m_Projectiles;
     std::vector<Layer*> m_layers;
      std::vector<Tileset> m_tilesets;
     std::vector<TileLayer*> m_collisionLayers;
};

#endif
