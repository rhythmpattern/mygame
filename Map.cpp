#include "Map.h"
#include "ObjectEnumerations.h"
#include "Graph/HandyGraphFunctions.h"
#include "Door.h"
#include "Game/EntityManager.h"
#include "constants.h"
#include "Triggers/Trigger_HealthGiver.h"
#include "Triggers/Trigger_WeaponGiver.h"
#include "Triggers/Trigger_OnButtonSendMsg.h"
#include "Triggers/Trigger_SoundNotify.h"
#include <sstream>
#include "UserOptions.h"
#include <stdio.h>
#include "Scriptor.h"

#define Debug

//----------------------------- ctor ------------------------------------------
//-----------------------------------------------------------------------------
Map::Map():m_pNavGraph(NULL),
                       m_pSpacePartition(NULL),
                       m_iSizeY(0),
                       m_iSizeX(0),
                       m_dCellSpaceNeighborhoodRange(0)
{
}


//------------------------------ dtor -----------------------------------------
//-----------------------------------------------------------------------------
Map::~Map()
{
  
  Clear();
}



//-----------------------------update-------------------------------------------
//-
//-
//------------------------------------------------------------------------------



void Map::update() {}


//--------------------------render--------------------------------
//

//
///
//---------------------------------------------------------------

void Map::render(){}










//---------------------------- Clear ------------------------------------------
//
//  deletes all the current objects ready for a map load
//-----------------------------------------------------------------------------
void Map::Clear()
{
  //delete the triggers
  m_TriggerSystem.Clear();

  //delete the doors
  std::vector<Door*>::iterator curDoor = m_Doors.begin();
  for (curDoor; curDoor != m_Doors.end(); ++curDoor)
  {
    delete *curDoor;
  }

  m_Doors.clear();

  std::vector<Wall2D*>::iterator curWall = m_Walls.begin();
  for (curWall; curWall != m_Walls.end(); ++curWall)
  {
    delete *curWall;
  }

  m_Walls.clear();
  m_SpawnPoints.clear();

  //delete the navgraph
  delete m_pNavGraph;

  //delete the partioning info
  delete m_pSpacePartition;
}


//----------------------------- AddWall ---------------------------------------
//-----------------------------------------------------------------------------
void Map::AddWall(std::ifstream& in)
{
  m_Walls.push_back(new Wall2D(in));
}

Wall2D* Map::AddWall(Vector2D from, Vector2D to)
{
  Wall2D* w = new Wall2D(from, to);

  m_Walls.push_back(w);

  return w;
}

//--------------------------- AddDoor -----------------------------------------
//-----------------------------------------------------------------------------
void Map::AddDoor(std::ifstream& in)
{
  Door* pDoor = new Door(this, in);

  m_Doors.push_back(pDoor);

  //register the entity
  EntityMgr->RegisterEntity(pDoor);
}


//--------------------------- AddDoorTrigger ----------------------------------
//-----------------------------------------------------------------------------
void Map::AddDoorTrigger(std::ifstream& in)
{
  Trigger_OnButtonSendMsg<Character>* tr = new Trigger_OnButtonSendMsg<Character>(in);

  m_TriggerSystem.Register(tr);

  //register the entity
  EntityMgr->RegisterEntity(tr);

}


//---------------------------- AddSpawnPoint ----------------------------------
//-----------------------------------------------------------------------------
void Map::AddSpawnPoint(std::ifstream& in)
{
  double x, y, dummy;

  in >> dummy >> x >> y >> dummy >> dummy;                   //dummy values are artifacts from the map editor

  
  m_SpawnPoints.push_back(Vector2D(x,y));
}


//----------------------- AddHealth__Giver ----------------------------------
//-----------------------------------------------------------------------------
void Map::AddHealth_Giver(std::ifstream& in)
{
  Trigger_HealthGiver* hg = new Trigger_HealthGiver(in);

  m_TriggerSystem.Register(hg);

  //let the corresponding navgraph node point to this object
  NavGraph::NodeType& node = m_pNavGraph->GetNode(hg->GraphNodeIndex());

  node.SetExtraInfo(hg);

  //register the entity
  EntityMgr->RegisterEntity(hg);
}

//----------------------- AddWeapon__Giver ----------------------------------
//-----------------------------------------------------------------------------
void Map::AddWeapon_Giver(int type_of_weapon, std::ifstream& in)
{
  Trigger_WeaponGiver* wg = new Trigger_WeaponGiver(in);

  wg->SetEntityType(type_of_weapon);

  //add it to the appropriate vectors
  m_TriggerSystem.Register(wg);

  //let the corresponding navgraph node point to this object
  NavGraph::NodeType& node = m_pNavGraph->GetNode(wg->GraphNodeIndex());

  node.SetExtraInfo(wg);

  //register the entity
  EntityMgr->RegisterEntity(wg);
}

//-------------------------LoadMap------------
bool Map::LoadMap(const std::string& filename)
{
#ifdef Debug
  std::cout << "LoadMap called"<<endl;
  #endif
std::ifstream in(filename.c_str());
if (!in)
  {
    throw std::runtime_error("Invalid Map filename");
    return false;
  }
Clear();

Entity::ResetNextValidID();

m_pNavGraph = new NavGraph(false);

m_pNavGraph->Load(in);

 m_dCellSpaceNeighborhoodRange = CalculateAverageGraphEdgeLength(*m_pNavGraph) + 1;
//load in the map size and adjust the client window accordingly
  in >> m_iSizeX >> m_iSizeY;
//partition the graph nodes
  PartitionNavGraph();

  //now create the environment entities
  while (!in.eof())
  {
    //get type of next map object
    int EntityType;

    in >> EntityType;

    //create the object
    switch(EntityType)
    {
    case type_wall:

        AddWall(in); break;

    case type_sliding_door:

        AddDoor(in); break;

    case type_door_trigger:

        AddDoorTrigger(in); break;

   case type_spawn_point:

       AddSpawnPoint(in); break;

   case type_health:

       AddHealth_Giver(in); break;

    default:

break;
      throw std::runtime_error("<Map::Load>: Attempting to load undefined object");



    }//end switch

}


   //calculate the cost lookup table
  m_PathCosts = CreateAllPairsCostsTable(*m_pNavGraph);
 //g_screenLog->log(LL_INFO, "AFTER COSTS TABLE");
return true;
}



//-------------------------------------------

//------------- CalculateCostToTravelBetweenNodes -----------------------------
//
//  Uses the pre-calculated lookup table to determine the cost of traveling
//  from nd1 to nd2
//-----------------------------------------------------------------------------
double
Map::CalculateCostToTravelBetweenNodes(int nd1, int nd2)const
{
  assert (nd1>=0 && nd1<m_pNavGraph->NumNodes() &&
          nd2>=0 && nd2<m_pNavGraph->NumNodes() &&
          "<Map::CostBetweenNodes>: invalid index");

  return m_PathCosts[nd1][nd2];
}



//-------------------------- PartitionEnvironment -----------------------------
//-----------------------------------------------------------------------------
void Map::PartitionNavGraph()
{
  if (m_pSpacePartition) delete m_pSpacePartition;

  m_pSpacePartition = new CellSpacePartition<NavGraph::NodeType*>(m_iSizeX,
                                                                  m_iSizeY,
                                                                  script->getInt("numcellsx"),
                                                                  script->getInt("numcellsy"),
                                                                  m_pNavGraph->NumNodes());

  //add the graph nodes to the space partition
  NavGraph::NodeIterator NodeItr(*m_pNavGraph);
  for (NavGraph::NodeType* pN=NodeItr.begin();!NodeItr.end();pN=NodeItr.next())
  {
    m_pSpacePartition->AddEntity(pN);
  }
}


//---------------------------- AddSoundTrigger --------------------------------
//
//  given the bot that has made a sound, this method adds a SoundMade trigger
//-----------------------------------------------------------------------------
void Map::AddSoundTrigger(Character* pSoundSource, double range)
{
  m_TriggerSystem.Register(new Trigger_SoundNotify(pSoundSource, range));
}


//----------------------- UpdateTriggerSystem ---------------------------------
//
//  givena container of entities in the world this method updates them against
//  all the triggers
//-----------------------------------------------------------------------------
void Map::UpdateTriggerSystem(std::vector<Character*>& bots)
{
  m_TriggerSystem.Update(bots);
}


//------------------------- GetRandomNodeLocation -----------------------------
//
//  returns the position of a graph node selected at random
//-----------------------------------------------------------------------------
Vector2D Map::GetRandomNodeLocation()const
{
  NavGraph::ConstNodeIterator NodeItr(*m_pNavGraph);
  int RandIndex = RandInt(0, m_pNavGraph->NumActiveNodes()-1);
  const NavGraph::NodeType* pN = NodeItr.begin();
  while (--RandIndex > 0)
  {
    pN = NodeItr.next();
  }

  return pN->Pos();
}









