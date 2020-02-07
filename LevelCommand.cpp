#include "LevelCommand.h"
#include "Room.h"
#include "Level.h"

LevelCommand::LevelCommand(Level* pLevel , Room* m_pRoom)
{
  
    //m_pRoom->LoadMap("DM1.map", numChars); 
       m_pRoom->LoadMap(pLevel->getCollisionLayers()->front());
   m_pRoom->SetLevel(pLevel);
      pLevel->getRooms()->push_back(m_pRoom);
}
