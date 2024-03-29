#ifndef GRAPH_FUNCS
#define GRAPH_FUNCS
//-----------------------------------------------------------------------------
//
//  Name:   HandyGraphFunctions.h
//
//  Author: Shaun Hose
//
//  Desc:   As the name implies, some useful functions you can use with your
//          graphs. 

//          For the function templates, make sure your graph interface complies
//          with the SparseGraph class
//-----------------------------------------------------------------------------
#include <iosfwd>


#include "../misc/utils.h"
#include "../misc/Stream_Utility_Functions.h"
#include "GraphAlgorithms.h"
#include "AStarHeuristicPolicies.h"
#include "GraphNodeTypes.h"
#include "GraphEdgeTypes.h"
#include "SparseGraph.h"



//--------------------------- ValidNeighbour -----------------------------
//
//  returns true if x,y is a valid position in the map
//------------------------------------------------------------------------
bool ValidNeighbour(int x, int y, int NumCellsX, int NumCellsY)
{
  return !((x < 0) || (x >= NumCellsX) || (y < 0) || (y >= NumCellsY));
}
  
//------------ GraphHelper_AddAllNeighboursToGridNode ------------------
//
//  use to add he eight neighboring edges of a graph node that 
//  is positioned in a grid layout
//------------------------------------------------------------------------
template <class graph_type>
void GraphHelper_AddAllNeighboursToGridNode(graph_type& graph,
                                            int         row,
                                            int         col,
                                            int         NumCellsX,
                                            int         NumCellsY)
{   
  for (int i=-1; i<2; ++i)
  {
    for (int j=-1; j<2; ++j)
    {
      int nodeX = col+j;
      int nodeY = row+i;

      //skip if equal to this node
      if ( (i == 0) && (j==0) ) continue;

      //check to see if this is a valid neighbour
      if (ValidNeighbour(nodeX, nodeY, NumCellsX, NumCellsY))
      {
        //calculate the distance to this node
        Vector2D PosNode      = graph.GetNode(row*NumCellsX+col).Pos();
        Vector2D PosNeighbour = graph.GetNode(nodeY*NumCellsX+nodeX).Pos();

        double dist = PosNode.Distance(PosNeighbour);

        //this neighbour is okay so it can be added
        typename graph_type::EdgeType NewEdge(row*NumCellsX+col,
                                     nodeY*NumCellsX+nodeX,
                                     dist);
        graph.AddEdge(NewEdge);

        //if graph is not a diagraph then an edge needs to be added going
        //in the other direction
        if (!graph.isDigraph())
        {
          typename graph_type::EdgeType NewEdge(nodeY*NumCellsX+nodeX,
                                       row*NumCellsX+col,
                                       dist);
          graph.AddEdge(NewEdge);
        }
      }
    }
  }
}


//--------------------------- GraphHelper_CreateGrid --------------------------
//
//  creates a graph based on a grid layout. This function requires the 
//  dimensions of the environment and the number of cells required horizontally
//  and vertically 
//-----------------------------------------------------------------------------
template <class graph_type>
void GraphHelper_CreateGrid(graph_type& graph,
                             int cySize,
                             int cxSize,
                             int NumCellsY,
                             int NumCellsX)
{ 

  
  //need some temporaries to help calculate each node center
  double CellWidth  = (double)cySize / (double)NumCellsX;
  double CellHeight = (double)cxSize / (double)NumCellsY;

  double midX = CellWidth/2;
  double midY = CellHeight/2;

  
  //first create all the nodes
  for (int row=0; row<NumCellsY; ++row)
  {
    for (int col=0; col<NumCellsX; ++col)
    {
      graph.AddNode(NavGraphNode<>(graph.GetNextFreeNodeIndex(),
                                   Vector2D(midX + (col*CellWidth),
                                   midY + (row*CellHeight))));

    }
  }
  //now to calculate the edges. (A position in a 2d array [x][y] is the
  //same as [y*NumCellsX + x] in a 1d array). Each cell has up to eight
  //neighbours.
  for (int row=0; row<NumCellsY; ++row)
  {
    for (int col=0; col<NumCellsX; ++col)
    {
      GraphHelper_AddAllNeighboursToGridNode(graph, row, col, NumCellsX, NumCellsY);
    }
  }
}  




//--------------------------- WeightNavGraphNodeEdges -------------------------
//
//  Given a cost value and an index to a valid node this function examines 
//  all a node's edges, calculates their length, and multiplies
//  the value with the weight. Useful for setting terrain costs.
//------------------------------------------------------------------------
template <class graph_type>
void WeightNavGraphNodeEdges(graph_type& graph, int node, double weight)
{typedef typename graph_type::EdgeType Edge;
  typedef typename graph_type::NodeType Node;
  //make sure the node is present
  assert(node < graph.NumNodes());

  //set the cost for each edge
  typename graph_type::ConstEdgeIterator ConstEdgeItr(graph, node);
  for (Edge* pE=ConstEdgeItr.begin();
       !ConstEdgeItr.end();
       pE=ConstEdgeItr.next())
  {
    //calculate the distance between nodes
    double dist = Vec2DDistance(graph.GetNode(pE->From()).Pos(),
                               graph.GetNode(pE->To()).Pos());

    //set the cost of this edge
    graph.SetEdgeCost(pE->From(), pE->To(), dist * weight);

    //if not a digraph, set the cost of the parallel edge to be the same
    if (!graph.isDigraph())
    {      
      graph.SetEdgeCost(pE->To(), pE->From(), dist * weight);
    }
  }
}


//----------------------- CreateAllPairsTable ---------------------------------
//
// creates a lookup table encoding the shortest path info between each node
// in a graph to every other
//-----------------------------------------------------------------------------
template <class graph_type>
std::vector<std::vector<int> > CreateAllPairsTable(const graph_type& G)
{typedef typename graph_type::EdgeType Edge;
  typedef typename graph_type::NodeType Node;
  enum {no_path = -1};
  
  std::vector<int> row(G.NumNodes(), no_path);
  
  std::vector<std::vector<int> > ShortestPaths(G.NumNodes(), row);

  for (int source=0; source<G.NumNodes(); ++source)
  {
    //calculate the SPT for this node
    Graph_SearchDijkstra<graph_type> search(G, source);

    std::vector<const Edge*> spt = search.GetSPT();

    //now we have the SPT it's easy to work backwards through it to find
    //the shortest paths from each node to this source node
    for (int target = 0; target<G.NumNodes(); ++target)
    {
      //if the source node is the same as the target just set to target
      if (source == target)
      {
        ShortestPaths[source][target] = target;
      }

      else
      {
        int nd = target;

        while ((nd != source) && (spt[nd] != 0))
        {
          ShortestPaths[spt[nd]->From][target]= nd;

          nd = spt[nd]->From;
        }
      }
    }//next target node
  }//next source node

  return ShortestPaths;
}


//----------------------- CreateAllPairsCostsTable -------------------------------
//
//  creates a lookup table of the cost associated from traveling from one
//  node to every other
//-----------------------------------------------------------------------------
template <class graph_type>
std::vector<std::vector<double> > CreateAllPairsCostsTable(const graph_type& G)
{
  //create a two dimensional vector
  std::vector<double> row(G.NumNodes(), 0.0);
  std::vector<std::vector<double> > PathCosts(G.NumNodes(), row);

  for (int source=0; source<G.NumNodes(); ++source)
  {
    //do the search
    Graph_SearchDijkstra<graph_type> search(G, source);

    //iterate through every node in the graph and grab the cost to travel to
    //that node
    for (int target = 0; target<G.NumNodes(); ++target)
    {
      if (source != target)
      {
        PathCosts[source][target]= search.GetCostToNode(target);
      }
    }//next target node
    
  }//next source node

  return PathCosts;
}

//---------------------- CalculateAverageGraphEdgeLength ----------------------
//
//  determines the average length of the edges in a navgraph (using the 
//  distance between the source & target node positions (not the cost of the 
//  edge as represented in the graph, which may account for all sorts of 
//  other factors such as terrain type, gradients etc)
//------------------------------------------------------------------------------
template <class graph_type>
double CalculateAverageGraphEdgeLength(const graph_type& G)
{typedef typename graph_type::EdgeType Edge;
  typedef typename graph_type::NodeType Node;
  double TotalLength = 0;
  int NumEdgesCounted = 0;

 typename  graph_type::ConstNodeIterator NodeItr(G);
  Node* pN;
  for (pN = (Node*)NodeItr.begin(); !NodeItr.end(); pN=(Node*)NodeItr.next())
  {
    typename graph_type::ConstEdgeIterator EdgeItr(G, pN->Index());
    for (Edge* pE = (Edge*)EdgeItr.begin(); !EdgeItr.end(); pE=(Edge*)EdgeItr.next())
    {
      //increment edge counter
      ++NumEdgesCounted;

      //add length of edge to total length
      TotalLength += Vec2DDistance(G.GetNode(pE->From()).Pos(), G.GetNode(pE->To()).Pos());
    }
  }

  return TotalLength / (double)NumEdgesCounted;
}

//----------------------------- GetCostliestGraphEdge -------------------
//
//  returns the cost of the costliest edge in the graph
//-----------------------------------------------------------------------------
template <class graph_type>
double GetCostliestGraphEdge(const graph_type& G)
{typedef typename graph_type::EdgeType Edge;
  typedef typename graph_type::NodeType Node;
  double greatest = MinDouble;

  typename graph_type::ConstNodeIterator NodeItr(G);
  Node* pN;
  for (pN = NodeItr.begin(); !NodeItr.end(); pN=NodeItr.next())
  {
    typename graph_type::ConstEdgeIterator EdgeItr(G, pN->Index());
    for (Edge* pE = EdgeItr.begin(); !EdgeItr.end(); pE=EdgeItr.next())
    {
      if (pE->Cost() > greatest)greatest = pE->Cost();
    }
  }

  return greatest;
}

#endif
