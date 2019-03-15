#ifndef TERMINATION_POLICIES_H
#define TERMINATION_POLICIES_H

#include <cstddef>

//-----------------------------------------------------------------------------
//
//  Name:   SearchTerminationPolicies.h
//
//  Author: Shaun Hose
//
//  Desc:   class templates to define termination policies for Dijkstra's
//          algorithm
//-----------------------------------------------------------------------------



//--------------------------- FindNodeIndex -----------------------------------

//the search will terminate when the currently examined graph node
//is the same as the target node.
class FindNodeIndex
{
public:

  template <class graph_type>
  static bool isSatisfied(const graph_type& G, int target, int CurrentNodeIdx)
  {
    return CurrentNodeIdx == target;
  }
};

//--------------------------- FindActiveTrigger ------------------------------

//the search will terminate when the currently examined graph node
//is the same as the target node.
template <class trigger_type>
class FindActiveTrigger
{


public:

  template <class graph_type>
  static bool isSatisfied(const graph_type& G, int target, int CurrentNodeIdx)
  { typedef typename graph_type::NodeType Node;
    bool bSatisfied = false;

    //get a reference to the node at the given node index
   const Node& node = G.GetNode(CurrentNodeIdx);

    //if the extrainfo field is pointing to a giver-trigger, test to make sure 
    //it is active and that it is of the correct type.
    if ((node.ExtraInfo() != NULL) && 
         node.ExtraInfo()->isActive() && 
        (node.ExtraInfo()->EntityType() == target) )
    {    
      bSatisfied = true;
    }

    return bSatisfied;
  }
};


  
#endif
