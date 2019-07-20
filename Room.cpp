#include "Room.h"
#include "CharManager.h"


bool Room::init(const std::string mapName)
{
  LoadMap(mapName);
  GraveManager::Instance()->load();
  
  /*
 
      m_pPlayer = new Player(this, Vector2D(0,0));
    
   
    m_CharManager->AddChar(m_pPlayer);
    EntityMgr->RegisterEntity(m_pPlayer);
  */
}

Room::Room() {m_pCharManager = new CharManager(); m_pMap = NULL; m_pPathManager = NULL;}

//Destructor

Room::~Room()
{
  delete m_pMap;
  delete m_pPathManager;
  GraveManager::Instance()->Clear();
  ProjectileManager::Instance()->Clear();
}


bool Room::LoadMap(const std::string& filename)
{
 
   //clear any current chars and projectiles
   Clear();
  
  //out with the old
  delete m_pMap;
  delete m_pPathManager;

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
  
  /*
  //clear any current bots and projectiles
   Clear();
  
  //out with the old
  delete m_pMap;
  delete m_pPathManager;

  //in with the new
  m_pPathManager = new PathManager<PathPlanner>(script->getInt("maxsearchcyclesperupdatestep"));
  m_pMap = new Map();
  
  //make sure the entity manager is reset
  //EntityMgr->Reset();

 
  //load the new map data
  if (m_pMap->LoadMap(filename))
  {
    #ifdef LOG
    std::cout << "LoadMap called succesfully" <<endl;
    #endif
    m_pCharManager->AddChars(1);
  
    return true;
  }
  
  return false;
  */
  
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
  
  /*
  
  //update all the queued searches in the path manager
  m_pPathManager->UpdateSearches();
 
    m_pCharManager->Update();
 
  

  //update any doors
  std::vector<Door*>::iterator curDoor =m_pMap->GetDoors().begin();
  for (curDoor; curDoor != m_pMap->GetDoors().end(); ++curDoor)
  {
    (*curDoor)->Update();
  }


  //update the triggers
  std::vector<Character*> a;
  a =  m_pCharManager->GetAllChars();
  m_pMap->UpdateTriggerSystem(a);


  */
  
}

void Room::Clear()
{
  #ifdef LOG
    std::cout << "\n------------------------------ Clearup -------------------------------" << endl;
#endif

    m_pCharManager->Clear();
   
 
 
  
}




