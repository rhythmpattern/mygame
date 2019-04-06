#include "BLayer.h"

BLayer::BLayer(){}

void BLayer::render()
{
   TextureManager::Instance()->drawFrame("background",  0, 0, 1455, 796,0,0, Game::Instance()->getRenderer(),0,100);
}


void BLayer::update(Level* pLevel){}
