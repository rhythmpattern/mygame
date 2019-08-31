//The Map size created in Tiles must equal the Game::width and Game::height for this render function to run.

#include "TileLayer.h"
#include "TextureManager.h"
#include "Game.h"
#include <android/log.h>



TileLayer::TileLayer(int tileSize, const std::vector<Tileset>& tilesets) : m_tileSize(tileSize), m_tilesets(tilesets), m_position(0,0), m_velocity(0,0)
{ 
    m_numColumns = (Game::Instance()->getGameWidth() / m_tileSize) + 1;
    m_numRows = (Game::Instance()->getGameHeight() / m_tileSize);
   
    
}

void TileLayer::update(Level* pLevel)
{
    if(m_position.x < ((m_mapWidth * m_tileSize) - Game::Instance()->getGameWidth()) - m_tileSize)
    {
      m_velocity.x =0;
        m_position += m_velocity;

    }
    else
    {
        m_velocity.x =0;
	
    }
}

void TileLayer::render()
{
    int x, y, x2, y2 = 0;
    
    x = m_position.x / m_tileSize;
    y = m_position.y / m_tileSize;
    
     x2 = int(m_position.x) % m_tileSize;
     y2 = int(m_position.y) % m_tileSize;
    
    for(int i = 0; i < m_numRows; i++)
    {
        for(int j = 0; j < m_numColumns; j++)
        {
            int id = m_tileIDs[i + y][j + x];
            
            if(id == 0)
	      {  
                continue;
            }
            
            Tileset tileset = getTilesetByID(id);
	   
            id--;
            
	    TextureManager::Instance()->drawTile(tileset.name, tileset.margin, tileset.spacing, (j * m_tileSize) - x2, (i * m_tileSize) - y2, m_tileSize, m_tileSize, (id - (tileset.firstGridID - 1)) / tileset.numColumns, (id - (tileset.firstGridID - 1)) % tileset.numColumns, Game::Instance()->getRenderer());
        }
    }
}

Tileset TileLayer::getTilesetByID(int tileID)
{
    for(int i = 0; i < m_tilesets.size(); i++)
    {
        if( i + 1 <= m_tilesets.size() - 1)
        {
            if(tileID >= m_tilesets[i].firstGridID && tileID < m_tilesets[i + 1].firstGridID)
            {
                return m_tilesets[i];
            }
        }
        else
        {
            return m_tilesets[i];
        }
    }
    
    std::cout << "did not find tileset, returning empty tileset\n";
    Tileset t;
    return t;
}
