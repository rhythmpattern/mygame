#ifndef FEATURE_H
#define FEATURE_H
//-----------------------------------------------------------------------------
//
//  Name:   Feature.h
//
//  Author: Shaun Hose
//
//  Desc:   class that implements methods to extract feature specific
//          information from the Raven game world and present it as 
//          a value in the range 0 to 1
//
//-----------------------------------------------------------------------------
class Character;

class Feature
{
public:

  //returns a value between 0 and 1 based on the bot's health. The better
  //the health, the higher the rating
  static double Health(Character* pBot);
  
  //returns a value between 0 and 1 based on the bot's closeness to the 
  //given item. the further the item, the higher the rating. If there is no
  //item of the given type present in the game world at the time this method
  //is called the value returned is 1
  static double DistanceToItem(Character* pBot, int ItemType);
  

};



#endif
