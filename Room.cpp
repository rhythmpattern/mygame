#include "Room.h"
#include "CharManager.h"


bool Room::init(const std::string mapName)
{
  LoadMap(mapName);
  AddChar(Game::Instance()->GetPlayer());
  /*
  LoadMap(mapName);
   
      m_pPlayer = new Player(this, Vector2D(0,0));
    
   
    m_CharManager->AddChar(m_pPlayer);
    EntityMgr->AddEntity(m_pPlayer);
  */
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


void Room::Update()
{
   //update any doors
  std::vector<Door*>::iterator curDoor =m_pMap->GetDoors().begin();
  for (curDoor; curDoor != m_pMap->GetDoors().end(); ++curDoor)
  {
    (*curDoor)->Update();
  }
  
  m_pMap->UpdateTriggerSystem(m_Chars);
}

void Room::Clear()
{
  #ifdef LOG
    std::cout << "\n------------------------------ Clearup -------------------------------" << endl;
#endif

   
 
 
  
}




