#include "PlayerSteering.h"
#include "Character.h"
#include "2D/Wall2D.h"
#include "2D/Transformations.h"
#include "misc/utils.h"
#include "Game.h"
#include "2D/Geometry.h"
#include "Map.h"
#include "Scriptor.h"
#include <cassert>
#include "InputHandler.h"


using std::string;
using std::vector;



//------------------------- ctor -----------------------------------------
//
//------------------------------------------------------------------------
PlayerSteering::PlayerSteering(Room* room, Player* agent):
                                  
             m_pRoom(room),
             m_pCharacter(agent),
             m_iFlags(0),
             m_dWeightSeparation(script->getNum("separationweight")),
             m_dWeightWander(script->getNum("wanderweight")),
             m_dWeightWallAvoidance(script->getNum("wallavoidanceweight")),
             m_dViewDistance(script->getNum("viewdistance")),
             m_dWallDetectionFeelerLength(script->getNum("walldetectionfeelerlength")),
             m_Feelers(3),
             m_Deceleration(normal),
             m_pTargetAgent1(NULL),
             m_pTargetAgent2(NULL),
             m_dWanderDistance(WanderDist),
             m_dWanderJitter(WanderJitterPerSec),
             m_dWanderRadius(WanderRad),
             m_dWeightSeek(script->getNum("seekweight")),
             m_dWeightArrive(script->getNum("arriveweight")),
             m_bCellSpaceOn(false),
             m_SummingMethod(prioritized)
             


{
  //stuff for the wander behavior
  double theta = RandFloat() * TwoPi;

  //create a vector to a target position on the wander circle
  m_vWanderTarget = Vector2D(m_dWanderRadius * cos(theta),
                              m_dWanderRadius * sin(theta));

}


//----------------------------------HandleInput----------------------
//
//
//
void PlayerSteering::handleinput()
{
 
  if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_UP) && m_pCharacter->Pos().y > 0)
        {
	  m_pCharacter->Velocity().setY(-m_pCharacter->MaxSpeed());
        }
    
}




//---------------------------------dtor ----------------------------------
PlayerSteering::~PlayerSteering(){}


/////////////////////////////////////////////////////////////////////////////// CALCULATE METHODS 


//----------------------- Calculate --------------------------------------
//
//  calculates the accumulated steering force according to the method set
//  in m_SummingMethod
//------------------------------------------------------------------------
Vector2D PlayerSteering::Calculate()
{ 
  //reset the steering force
  m_vSteeringForce.Zero();

 
  m_vSteeringForce = CalculatePrioritized();

  return m_vSteeringForce;
}

//------------------------- ForwardComponent -----------------------------
//
//  returns the forward oomponent of the steering force
//------------------------------------------------------------------------
double PlayerSteering::ForwardComponent()
{
  return m_pCharacter->Heading().Dot(m_vSteeringForce);
}

//--------------------------- SideComponent ------------------------------
//  returns the side component of the steering force
//------------------------------------------------------------------------
double PlayerSteering::SideComponent()
{
  return m_pCharacter->Side().Dot(m_vSteeringForce);
}


//--------------------- AccumulateForce ----------------------------------
//
//  This function calculates how much of its max steering force the 
//  vehicle has left to apply and then applies that amount of the
//  force to add.
//------------------------------------------------------------------------
bool PlayerSteering::AccumulateForce(Vector2D &RunningTot,
                                       Vector2D ForceToAdd)
{  
  //calculate how much steering force the vehicle has used so far
  double MagnitudeSoFar = RunningTot.Length();

  //calculate how much steering force remains to be used by this vehicle
  double MagnitudeRemaining = m_pCharacter->MaxForce() - MagnitudeSoFar;

  //return false if there is no more force left to use
  if (MagnitudeRemaining <= 0.0) return false;

  //calculate the magnitude of the force we want to add
  double MagnitudeToAdd = ForceToAdd.Length();
  
  //if the magnitude of the sum of ForceToAdd and the running total
  //does not exceed the maximum force available to this vehicle, just
  //add together. Otherwise add as much of the ForceToAdd vector is
  //possible without going over the max.
  if (MagnitudeToAdd < MagnitudeRemaining)
  {
    RunningTot += ForceToAdd;
  }

  else
  {
    MagnitudeToAdd = MagnitudeRemaining;

    //add it to the steering force
    RunningTot += (Vec2DNormalize(ForceToAdd) * MagnitudeToAdd); 
  }

  return true;
}



//---------------------- CalculatePrioritized ----------------------------
//
//  this method calls each active steering behavior in order of priority
//  and acumulates their forces until the max steering force magnitude
//  is reached, at which time the function returns the steering force 
//  accumulated to that  point
//------------------------------------------------------------------------
Vector2D PlayerSteering::CalculatePrioritized()
{       
  Vector2D force;

  if (On(wall_avoidance))
  {
    force = WallAvoidance(m_pRoom->GetMap()->GetWalls()) *
            m_dWeightWallAvoidance;

    if (!AccumulateForce(m_vSteeringForce, force)) return m_vSteeringForce;
  }

 


  return m_vSteeringForce;
}


/////////////////////////////////////////////////////////////////////////////// START OF BEHAVIORS

//------------------------------- Seek -----------------------------------
//
//  Given a target, this behavior returns a steering force which will
//  direct the agent towards the target
//------------------------------------------------------------------------
Vector2D PlayerSteering::Seek(const Vector2D &target)
{
 
  Vector2D DesiredVelocity = Vec2DNormalize(target - m_pCharacter->Pos())
                            * m_pCharacter->MaxSpeed();

  return (DesiredVelocity - m_pCharacter->Velocity());
}





//--------------------------- WallAvoidance --------------------------------
//
//  This returns a steering force that will keep the agent away from any
//  walls it may encounter
//------------------------------------------------------------------------
Vector2D PlayerSteering::WallAvoidance(const vector<Wall2D*> &walls)
{
  //the feelers are contained in a std::vector, m_Feelers
  CreateFeelers();
  
  double DistToThisIP    = 0.0;
  double DistToClosestIP = MaxDouble;

  //this will hold an index into the vector of walls
  int ClosestWall = -1;

  Vector2D SteeringForce,
            point,         //used for storing temporary info
            ClosestPoint;  //holds the closest intersection point

  //examine each feeler in turn
  for (unsigned int flr=0; flr<m_Feelers.size(); ++flr)
  {
    //run through each wall checking for any intersection points
    for (unsigned int w=0; w<walls.size(); ++w)
    {
      if (LineIntersection2D(m_pCharacter->Pos(),
                             m_Feelers[flr],
                             walls[w]->From(),
                             walls[w]->To(),
                             DistToThisIP,
                             point))
      {
        //is this the closest found so far? If so keep a record
        if (DistToThisIP < DistToClosestIP)
        {
          DistToClosestIP = DistToThisIP;

          ClosestWall = w;

          ClosestPoint = point;
        }
      }
    }//next wall

  
    //if an intersection point has been detected, calculate a force  
    //that will direct the agent away
    if (ClosestWall >=0)
    {
      //calculate by what distance the projected position of the agent
      //will overshoot the wall
      Vector2D OverShoot = m_Feelers[flr] - ClosestPoint;

      //create a force in the direction of the wall normal, with a 
      //magnitude of the overshoot
      SteeringForce = walls[ClosestWall]->Normal() * OverShoot.Length();
    }

  }//next feeler

  return SteeringForce;
}

//------------------------------- CreateFeelers --------------------------
//
//  Creates the antenna utilized by WallAvoidance
//------------------------------------------------------------------------
void PlayerSteering::CreateFeelers()
{
  //feeler pointing straight in front
  m_Feelers[0] = m_pCharacter->Pos() + m_dWallDetectionFeelerLength *
                 m_pCharacter->Heading() * m_pCharacter->Speed();

  //feeler to left
  Vector2D temp = m_pCharacter->Heading();
  Vec2DRotateAroundOrigin(temp, HalfPi * 3.5);
  m_Feelers[1] = m_pCharacter->Pos() + m_dWallDetectionFeelerLength/2.0 * temp;

  //feeler to right
  temp = m_pCharacter->Heading();
  Vec2DRotateAroundOrigin(temp, HalfPi * 0.5);
  m_Feelers[2] = m_pCharacter->Pos() + m_dWallDetectionFeelerLength/2.0 * temp;
}























