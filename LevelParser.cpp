
#include <string>
#include "LevelParser.h"
#include "TextureManager.h"
#include "Game.h"
#include "ObjectLayer.h"
#include "TileLayer.h"
#include "GameObjectFactory.h"
#include "base64.h"
#include "zlib.h"
#include "Map.h"

Level* LevelParser::parseLevel(const char *levelFile)
{
    // create a tinyXML document and load the map xml
    TiXmlDocument levelDocument;
    levelDocument.LoadFile(levelFile);
    
    // create the level object
    Level* pLevel = new Level();
    
     
    // get the root node and display some values
    TiXmlElement* pRoot = levelDocument.RootElement();
    std::cout << pRoot->Value();
 
    for (TiXmlElement* e = pRoot->FirstChildElement(); e != NULL ; e = e->NextSiblingElement())
      {
	parseTextures(e);
      }
 
    //  pRoot->Attribute("width", &m_width);
    // pRoot->Attribute("height", &m_height);
    
   
    
    return pLevel;
}


void LevelParser::parseTextures(TiXmlElement* pTextureRoot)
{
    std::cout << "adding texture " << pTextureRoot->Attribute("value") << " with ID " << pTextureRoot->Attribute("name") << std::endl;
    TextureManager::Instance()->load(pTextureRoot->Attribute("value"), pTextureRoot->Attribute("name"), Game::Instance()->getRenderer());
}

void LevelParser::parseTilesets(TiXmlElement* pTilesetRoot, std::vector<Tileset>* pTilesets)
{
	std::string assetsTag = "assets/";
    // first add the tileset to texture manager
    std::cout << "adding texture " << pTilesetRoot->FirstChildElement()->Attribute("source") << " with ID " << pTilesetRoot->Attribute("name") << std::endl;
	TheTextureManager::Instance()->load(assetsTag.append(pTilesetRoot->FirstChildElement()->Attribute("source")), pTilesetRoot->Attribute("name"), Game::Instance()->getRenderer());
    
    // create a tileset object
    Tileset tileset;
    pTilesetRoot->FirstChildElement()->Attribute("width", &tileset.width);
    pTilesetRoot->FirstChildElement()->Attribute("height", &tileset.height);
    pTilesetRoot->Attribute("firstgid", &tileset.firstGridID);
    pTilesetRoot->Attribute("tilewidth", &tileset.tileWidth);
    pTilesetRoot->Attribute("tileheight", &tileset.tileHeight);
    pTilesetRoot->Attribute("spacing", &tileset.spacing);
    pTilesetRoot->Attribute("margin", &tileset.margin);
    tileset.name = pTilesetRoot->Attribute("name");
    
    tileset.numColumns = tileset.width / (tileset.tileWidth + tileset.spacing);
    
    pTilesets->push_back(tileset);
}

void LevelParser::parseObjectLayer(TiXmlElement* pObjectElement, std::vector<Layer*> *pLayers, Level* pLevel)
{
    // create an object layer
    ObjectLayer* pObjectLayer = new ObjectLayer();
    
    for(TiXmlElement* e = pObjectElement->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
    {
        if(e->Value() == std::string("object"))
        {
            int x, y, width, height, numFrames, callbackID = 0, animSpeed = 0;
            std::string textureID;
            std::string type;
            
            // get the initial node values type, x and y
            e->Attribute("x", &x);
            e->Attribute("y", &y);
            
            type = e->Attribute("type");
            Entity* pGameObject = GameObjectFactory::Instance()->create(type);
            
            // get the property values
            for(TiXmlElement* properties = e->FirstChildElement(); properties != NULL; properties = properties->NextSiblingElement())
            {
                if(properties->Value() == std::string("properties"))
                {
                    for(TiXmlElement* property = properties->FirstChildElement(); property != NULL; property = property->NextSiblingElement())
                    {
                        if(property->Value() == std::string("property"))
                        {
                            if(property->Attribute("name") == std::string("numFrames"))
                            {
                                property->Attribute("value", &numFrames);
                            }
                            else if(property->Attribute("name") == std::string("textureHeight"))
                            {
                                property->Attribute("value", &height);
                            }
                            else if(property->Attribute("name") == std::string("textureID"))
                            {
                                textureID = property->Attribute("value");
                            }
                            else if(property->Attribute("name") == std::string("textureWidth"))
                            {
                                property->Attribute("value", &width);
                            }
                            else if(property->Attribute("name") == std::string("callbackID"))
                            {
                                property->Attribute("value", &callbackID);
                            }
                            else if(e->Attribute("name") == std::string("animSpeed"))
                            {
                                property->Attribute("value", &animSpeed);
                            }
                        }
                    }
                }
            }
            //int x, int y, int width, int height, std::string textureID, int numFrames, void()
	    //      pGameObject->load(std::unique_ptr<LoaderParams>(new LoaderParams(x, y, width, height, textureID, numFrames,callbackID, animSpeed)));
            
	    //     if(type == "Player")
	    //     {
	    //        pLevel->setPlayer(dynamic_cast<Player*>(pGameObject));
	    //    }
            
	        pObjectLayer->getGameObjects()->push_back(pGameObject);
        }
    }
    
    pLayers->push_back(pObjectLayer);
}


void LevelParser::parseTileLayer(TiXmlElement* pTileElement, std::vector<Layer*> *pLayers, const std::vector<Tileset>* pTilesets, std::vector<TileLayer*> *pCollisionLayers)
{
    TileLayer* pTileLayer = new TileLayer(m_tileSize, *pTilesets);
    
    bool collidable = false;
    
    // tile data
    std::vector<std::vector<int>> data;
    
    std::string decodedIDs;
    TiXmlElement* pDataNode;
    
    for(TiXmlElement* e = pTileElement->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
    {
        if(e->Value() == std::string("properties"))
        {
            for(TiXmlElement* property = e->FirstChildElement(); property != NULL; property = property->NextSiblingElement())
            {
                if(property->Value() == std::string("property"))
                {
                    if(property->Attribute("name") == std::string("collidable"))
                    {
                        collidable = true;
                    }
                }
            }
        }
        
        if(e->Value() == std::string("data"))
        {
            pDataNode = e;
        }
    }
    
    for(TiXmlNode* e = pDataNode->FirstChild(); e != NULL; e = e->NextSibling())
    {
        TiXmlText* text = e->ToText();
        std::string t = text->Value();
        decodedIDs = base64_decode(t);
    }
    
    // uncompress zlib compression
    uLongf sizeofids = m_width * m_height * sizeof(int);
    std::vector<int> ids(m_width * m_height);
    uncompress((Bytef*)&ids[0], &sizeofids,(const Bytef*)decodedIDs.c_str(), decodedIDs.size());
    
    std::vector<int> layerRow(m_width);
    
    for(int j = 0; j < m_height; j++)
    {
        data.push_back(layerRow);
    }
    
    for(int rows = 0; rows < m_height; rows++)
    {
        for(int cols = 0; cols < m_width; cols++)
        {
            data[rows][cols] = ids[rows * m_width + cols];
        }
    }
    
    pTileLayer->setTileIDs(data);
    pTileLayer->setMapWidth(m_width);
    
    if(collidable)
    {
        pCollisionLayers->push_back(pTileLayer);
    }
    
    pLayers->push_back(pTileLayer);
}


