#ifndef MAP_H
#define MAP_H
#pragma warning (disable:4786)

#include <vector>
#include <string>
#include <list>
#include "Graph/SparseGraph.h"
#include "Triggers/TriggerSystem.h"
#include "Character.h"
#include "Triggers/Trigger.h"
#include "2D/Wall2D.h"
#include "misc/CellSpacePartition.h"
#include "Graph/GraphNodeTypes.h"
#include "Graph/GraphEdgeTypes.h"
#include "Player.h"

class Entity;
class Door;
class TileLayer;


class Map {
 public:
     typedef NavGraphNode<Trigger<Character>*>         GraphNode;
  typedef SparseGraph<GraphNode, NavGraphEdge>      NavGraph;
  typedef CellSpacePartition<NavGraph::NodeType*>   CellSpace;

  typedef Trigger<Character>                        TriggerType;
  typedef TriggerSystem<TriggerType>                TrigSystem;
  

  private:


 //the walls that comprise the current map's architecture. 
  std::vector<Wall2D*>                m_Walls;

 //trigger are objects that define a region of space. When a  bot
  //enters that area, it 'triggers' an event. That event may be anything
  //from increasing a bot's health to opening a door or requesting a lift.
   TrigSystem                     m_TriggerSystem;   


  //this holds a number of spawn positions. When a bot is instantiated
  //it will appear at a randomly selected point chosen from this vector
  std::vector<Vector2D>              m_SpawnPoints;


  //a map may contain a number of sliding doors.
  std::vector<Door*>           m_Doors;

  //this map's accompanying navigation graph
  NavGraph*                          m_pNavGraph; 

  //the graph nodes will be partitioned enabling fast lookup
  CellSpace*                        m_pSpacePartition;

 //the size of the search radius the cellspace partition uses when looking for 
  //neighbors 
  double                             m_dCellSpaceNeighborhoodRange;

  int m_iSizeX;
  int m_iSizeY;
  
  void  PartitionNavGraph();

  //this will hold a pre-calculated lookup table of the cost to travel from
  //one node to any other.
  std::vector<std::vector<double> >  m_PathCosts;

  
    //stream constructors for loading from a file
  void AddWall(std::istringstream& in);
  void AddSpawnPoint(std::istringstream& in);
void AddWeapon_Giver(int type_of_weapon, std::istringstream& in);
  void AddHealth_Giver(std::istringstream& in);
  void AddDoor(std::istringstream& in);
  void AddDoorTrigger(std::istringstream& in);

  void Clear();

 public:

 Map();
 ~Map();

 void render();
void update();
 bool LoadMap(const std::string& FileName);
  bool LoadMap(TileLayer* tLayer);


    //adds a wall and returns a pointer to that wall. (this method can be
  //used by objects such as doors to add walls to the environment)
  Wall2D* AddWall(Vector2D from, Vector2D to);

   void    AddSoundTrigger(Character* pSoundSource, double range);

  double   CalculateCostToTravelBetweenNodes(int nd1, int nd2)const;
 
  
  Vector2D GetRandomNodeLocation()const;


  void  UpdateTriggerSystem(std::vector<Character*>& bots);

  const Map::TrigSystem::TriggerList&  GetTriggers() const{
	return m_TriggerSystem.GetTriggers(); }


  const std::vector<Wall2D*>&        GetWalls()const{return m_Walls;}
  NavGraph&                          GetNavGraph()const{return *m_pNavGraph;}
  std::vector<Door*>&          GetDoors(){return m_Doors;}
  const std::vector<Vector2D>&       GetSpawnPoints()const{return m_SpawnPoints;}
  CellSpace* const                   GetCellSpace()const{return m_pSpacePartition;}
  Vector2D                           GetRandomSpawnPoint(){return m_SpawnPoints[RandInt(0,m_SpawnPoints.size()-1)];}
int                                GetSizeX()const{return m_iSizeX;}
  int                                GetSizeY()const{return m_iSizeY;}
  int                                GetMaxDimension()const{return Maximum(m_iSizeX, m_iSizeY);}
  double                             GetCellSpaceNeighborhoodRange()const{return m_dCellSpaceNeighborhoodRange;}
 
};


#endif
