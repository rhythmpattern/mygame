#include "Room.h"
#include "CharManager.h"
#include "Scriptor.h"
#include "2D/WallIntersectionTests.h"

bool Room::init(const std::string mapName)
{
  LoadMap(mapName);
 
  
  /*
 
      m_pPlayer = new Player(this, Vector2D(0,0));
    
   
    m_CharManager->AddChar(m_pPlayer);
    EntityMgr->RegisterEntity(m_pPlayer);
  */
}

Room::Room() {m_pCharManager = new CharManager(this); m_pMap = NULL; m_pPathManager = NULL;}

//Destructor

Room::~Room()
{
  Clear();
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
   m_pPathManager = new PathManager<PathPlanner>(script->getInt("maxsearchcyclesperupdatestep"));
   GraveManager::Instance()->load();
   
 
  //load the new map data
  if (m_pMap->LoadMap(filename))
  {
    #ifdef LOG
    std::cout << "LoadMap called succesfully" <<endl;
    #endif
    m_pCharManager->AddChars(6);
    return true;
  }
  
  
  return false;
  

}


void Room::Render()
{
              
  GraveManager::Instance()->Render();
  m_pCharManager->Render();
  ProjectileManager::Instance()->Render();  
}

void Room::Update()
{
  
  GraveManager::Instance()->Update();
  ProjectileManager::Instance()->Update();
  m_pCharManager->Update();
  m_pPathManager->UpdateSearches();
  m_pMap->UpdateTriggerSystem(m_Chars);
   //update any doors
  std::vector<Door*>::iterator curDoor =m_pMap->GetDoors().begin();
  for (curDoor; curDoor != m_pMap->GetDoors().end(); ++curDoor)
  {
    (*curDoor)->Update();
  }
 
  
}

void Room::Clear()
{
  #ifdef LOG
    std::cout << "\n------------------------------ Clearup -------------------------------" << endl;
#endif

    m_pCharManager->Clear();
   
 
 
  
}



//---------------------------- isSecondVisibleToFirst -------------------------

bool
Room::isSecondVisibleToFirst(const Character* pFirst,
                                   const Character* pSecond)const
{
  //if the two bots are equal or if one of them is not alive return false
  if ( !(pFirst == pSecond) && pSecond->isAlive())
  {
    //first of all test to see if this bot is within the FOV
    if (isSecondInFOVOfFirst(pFirst->Pos(),
                             pFirst->Facing(),
                             pSecond->Pos(),
                             pFirst->FieldOfView()))
    {
      //test the line segment connecting the bot's positions against the walls.
      //If the bot is visible add it to the vector
      if (!doWallsObstructLineSegment(pFirst->Pos(),
                                      pSecond->Pos(),
                                      m_pMap->GetWalls()))
      {
        return true;
      }
    }
  }

  return false;
}

//---------------------------- isLOSOkay --------------------------------------
//
//  returns true if the ray between A and B is unobstructed.
//------------------------------------------------------------------------------
bool Room::isLOSOkay(Vector2D A, Vector2D B)const
{
  return !doWallsObstructLineSegment(A, B, m_pMap->GetWalls());
}

//------------------------- isPathObstructed ----------------------------------
//
//  returns true if a bot cannot move from A to B without bumping into 
//  world geometry. It achieves this by stepping from A to B in steps of
//  size BoundingRadius and testing for intersection with world geometry at
//  each point.
//-----------------------------------------------------------------------------
bool Room::isPathObstructed(Vector2D A,
                                  Vector2D B,
                                  double    BoundingRadius)const
{
  Vector2D ToB = Vec2DNormalize(B-A);

  Vector2D curPos = A;

  while (Vec2DDistanceSq(curPos, B) > BoundingRadius*BoundingRadius)
  {   
    //advance curPos one step
    curPos += ToB * 0.5 * BoundingRadius;
    
    //test all walls against the new position
    if (doWallsIntersectCircle(m_pMap->GetWalls(), curPos, BoundingRadius))
    {
      return true;
    }
  }

  return false;
}


//--------------------- GetPosOfClosestSwitch -----------------------------
//
//  returns the position of the closest visible switch that triggers the
//  door of the specified ID
//-----------------------------------------------------------------------------
Vector2D 
Room::GetPosOfClosestSwitch(Vector2D botPos, unsigned int doorID)const
{
  std::vector<unsigned int> SwitchIDs;
  
  //first we need to get the ids of the switches attached to this door
  std::vector<Door*>::const_iterator curDoor;
  for (curDoor = m_pMap->GetDoors().begin();
       curDoor != m_pMap->GetDoors().end();
       ++curDoor)
  {
    if ((*curDoor)->ID() == doorID)
    {
       SwitchIDs = (*curDoor)->GetSwitchIDs(); break;
    }
  }

  Vector2D closest;
  double ClosestDist = MaxDouble;
  
  //now test to see which one is closest and visible
  std::vector<unsigned int>::iterator it;
  for (it = SwitchIDs.begin(); it != SwitchIDs.end(); ++it)
  {
    Entity* trig = EntityMgr->GetEntityFromID(*it);

    if (isLOSOkay(botPos, trig->Pos()))
    {
      double dist = Vec2DDistanceSq(botPos, trig->Pos());

      if ( dist < ClosestDist)
      {
        ClosestDist = dist;
        closest = trig->Pos();
      }
    }
  }

  return closest;
}


void Room::TagCharactersWithinViewRange(Entity* pChar, double range)
   {
     std::vector<Character*> allChars = m_pCharManager->GetAllChars();
     TagNeighbors(pChar, allChars , range);}
  

