#include "Room.h"
#include "CharManager.h"


bool Room::init(const std::string mapName)
{
  LoadMap(mapName);
  AddChar(Game::Instance()->GetPlayer());
}

//Destructor

Room::~Room()
{
  delete m_pMap;
}


bool Room::LoadMap(const std::string& filename)
{
   //clear any current chars and projectiles
   Clear();
  
  //out with the old
  delete m_pMap;

  //in with the new
  m_pMap = new Map();
  
 

 
  //load the new map data
  if (m_pMap->LoadMap(filename))
  {
    #ifdef LOG
    std::cout << "LoadMap called succesfully" <<endl;
    #endif
   
    return true;
  }
  
  
  return false;
}

void Room::Clear()
{
  #ifdef LOG
    std::cout << "\n------------------------------ Clearup -------------------------------" << endl;
#endif

    m_pCharManager->Clear();
 
 
  
}


void Room::AddChar(Character* pChar)
{
  m_Chars.push_back(pChar); 
}
