#include "Feature.h"
#include "../Character.h"
#include "../Navigation/PathPlanner.h"
#include "../ObjectEnumerations.h"

//-----------------------------------------------------------------------------
double Feature::DistanceToItem(Character* pBot, int ItemType)
{
  //determine the distance to the closest instance of the item type
  double DistanceToItem = pBot->GetPathPlanner()->GetCostToClosestItem(ItemType);

  //if the previous method returns a negative value then there is no item of
  //the specified type present in the game world at this time.
  if (DistanceToItem < 0 ) return 1;

  //these values represent cutoffs. Any distance over MaxDistance results in
  //a value of 0, and value below MinDistance results in a value of 1
  const double MaxDistance = 500.0;
  const double MinDistance = 50.0;

  Clamp(DistanceToItem, MinDistance, MaxDistance);

  return DistanceToItem / MaxDistance;
}



//------------------------------- HealthScore ---------------------------------
//
//-----------------------------------------------------------------------------
double Feature::Health(Character* pBot)
{
  return (double)pBot->Health() / (double)pBot->MaxHealth();

}
