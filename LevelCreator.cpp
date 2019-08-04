#include "LevelCreator.h"

LevelCreator* LevelCreator::pInstance = 0;

LevelCreator::LevelCreator(){}

LevelCreator::~LevelCreator(){}

Level* LevelCreator::Create()
{
   LevelParser* levelParser = new LevelParser();
   Level* pLevel = levelParser->parseLevel(Game::Instance()->getLevelFiles()[Game::Instance()->getCurrentLevel() - 1].c_str());
   return pLevel;
}
