#ifndef OBJECTS_H
#define OBJECTS_H

#include <string>


enum 
{
  type_wall,
  type_bot,
  type_unused,
  type_waypoint,
  type_health,
  type_spawn_point,
  type_shooter,
  type_obstacle,
  type_sliding_door,
  type_door_trigger,
  type_zomb,
  type_player,
  type_melee
};



inline std::string GetNameOfType(int w)
{
  std::string s;
  
  switch (w)
  {
  case type_wall:
    
    s = "Wall"; break; 
    
  case type_waypoint:
    
    s = "Waypoint"; break;

  case type_obstacle:
    
    s = "Obstacle"; break;

  case type_health:
    
    s = "Health"; break;

  case type_spawn_point:
    
    s = "Spawn Point"; break;

  case type_shooter:
    
    s = "Shooter"; break;

 

  case type_unused:
    
    s =  "knife"; break;

  case type_bot:
    
    s =  "bot"; break;

  case type_sliding_door:
    
    s =  "sliding_door"; break;
    
  case type_door_trigger:
    
    s =  "door_trigger"; break;

  default:

    s = "UNKNOWN OBJECT TYPE"; break;

  }

  return s;
}


#endif
