 #ifndef ENTITY_H
#define ENTITY_H
#pragma warning (disable:4786)
//------------------------------------------------------------------------
//
//  Name: Entity.h
//
//  Desc: Base class to define a common interface for all game
//        entities
//
//  Author: Shaun Hose
//
//------------------------------------------------------------------------
#include <vector>
#include <string>
#include <iosfwd>
#include "../2D/Vector2D.h"
#include "../2D/Geometry.h"
#include "../misc/utils.h"
#include "../LoadParams.h"



struct Telegram;


class Entity
{
public:
  
  enum {default_entity_type = -1};

private:
 
  
  //each entity has a unique ID
  int         m_ID;

  //every entity has a type associated with it (health, troll, ammo etc)
  int         m_iType;

  
  //this is the next valid ID. Each time a Entity is instantiated
  //this value is updated
  static int  m_iNextValidID;

 

protected:
   //Texture variables.
  int m_width;
  int m_height;
  std::string m_textureID;
  int m_numFrames;
  int m_currentFrame;
  double m_angle;
  int m_alpha;
  int m_currentRow;
   //this must be called within each constructor to make sure the ID is set
  //correctly. It verifies that the value passed to the method is greater
  //or equal to the next valid ID, before setting the ID and incrementing
  //the next valid ID
  void SetID(int val);
//this is a generic flag. 
  bool        m_bTag;

  //its location in the environment
  Vector2D m_vPosition;

  Vector2D m_vScale;
 

  //the magnitude of this object's bounding radius
  double    m_dBoundingRadius;

  
  Entity(int ID);

public:

  virtual ~Entity(){}

  virtual void Update(){};
  virtual void draw(){};

  void load(std::unique_ptr<LoadParams> const &pParams);
  
  virtual bool HandleMessage(const Telegram& msg){return false;}
  
  //entities should be able to read/write their data to a stream
  virtual void Write(std::ostream&  os)const{}
  virtual void Read (std::istringstream& is)const{}

  //use this to grab the next valid ID
  static int   GetNextValidID(){return m_iNextValidID;}
  
  //this can be used to reset the next ID
  static void  ResetNextValidID(){m_iNextValidID = 0;}
  
  void         Render();

  Vector2D     Pos()const{return m_vPosition;}
  void         SetPos(Vector2D new_pos){m_vPosition = new_pos;}

  double       BRadius()const{return m_dBoundingRadius;}
  void         SetBRadius(double r){m_dBoundingRadius = r;}
  int          ID()const{return m_ID;}

  bool         IsTagged()const{return m_bTag;}
  void         Tag(){m_bTag = true;}
  void         UnTag(){m_bTag = false;}

  Vector2D     Scale()const{return m_vScale;}
  void         SetScale(Vector2D val){m_dBoundingRadius *= MaxOf(val.x, val.y)/MaxOf(m_vScale.x, m_vScale.y); m_vScale = val;}
  void         SetScale(double val){m_dBoundingRadius *= (val/MaxOf(m_vScale.x, m_vScale.y)); m_vScale = Vector2D(val, val);} 

  int          EntityType()const{return m_iType;}
  void         SetEntityType(int new_type){m_iType = new_type;}

};



      
#endif


