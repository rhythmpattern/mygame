#ifndef DOOR_H
#define DOOR_H
#pragma warning (disable:4786)
//-----------------------------------------------------------------------------
//
//  Name:   Door.h
//
//  Author: Shaun Hose
//
//  Desc:   class to emulate a sliding door that can be opened by sending
//          it a msg_OpenSesame telegram. The door stays open for a user
//          specified amount of time before closing. 
//-----------------------------------------------------------------------------
#include <vector>
#include <iosfwd>
#include "2D/Vector2D.h"
#include "Game/Entity.h"



struct Telegram;
class Map;
class Wall2D;


class Door : public Entity
{
protected:
  
  enum door_status{open, opening, closed, closing};

protected:

  door_status                m_Status;

  //a sliding door is created from two walls, back to back.These walls must
  //be added to a map's geometry in order for an agent to detect them
  Wall2D*                    m_pWall1;
  Wall2D*                    m_pWall2;

  //a container of the id's of the triggers able to open this door
  std::vector<unsigned int>  m_Switches;

  //how long the door remains open before it starts to shut again
  int                        m_iNumTicksStayOpen;

  //how long the door has been open (0 if status is not open)
  int                        m_iNumTicksCurrentlyOpen;

  //the door's position and size when in the open position
  Vector2D  m_vP1;
  Vector2D  m_vP2;
  double     m_dSize;
  
  //a normalized vector facing along the door. This is used frequently
  //by the other methods so we might as well just calculate it once in the
  //ctor
  Vector2D  m_vtoP2Norm;

  //the door's current size
  double     m_dCurrentSize;

  void  Open();
  void  Close();
  
  void ChangePosition(Vector2D newP1, Vector2D newP2);
 
public:
  
  Door(Map* pMap, std::istringstream& is);
  ~Door();

  void load(const LoadParams* pParams){}
  
  //the usual suspects
  void Update();
  bool HandleMessage(const Telegram& msg);
  void Read(std::istringstream&  is);
  void Write(std::ostream& os);

  //adds the ID of a switch
  void AddSwitch(unsigned int id);

  std::vector<unsigned int> GetSwitchIDs()const{return m_Switches;}
};


#endif
