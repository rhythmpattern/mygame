#ifndef TRIGGER_SEND_MESSAGE_H
#define TRIGGER_SEND_MESSAGE_H
///-----------------------------------------------------------------------------
//
//  Name:   Trigger_OnButtonSendMsg.h
//
//  Author: Shaun Hose
//
//  Desc:   trigger class to define a button that sends a msg to a 
//          specific entity when activated.
//-----------------------------------------------------------------------------
#include "Trigger.h"
#include "../Messaging/MessageDispatcher.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "../misc/Stream_Utility_Functions.h"
#include "../Messages.h"

template <class entity_type>
class Trigger_OnButtonSendMsg : public Trigger<entity_type>
{
private:

  //when triggered a message is sent to the entity with the following ID
  unsigned int    m_iReceiver;

  //the message that is sent
  int             m_iMessageToSend;

public:

  Trigger_OnButtonSendMsg(std::istringstream& datafile):
      
      Trigger<entity_type>(GetValueFromStream<int>(datafile))
  {
   
     Read(datafile);
   }

  void Try(entity_type* pEnt);

  void Update();
  
  void Render();

  void Write(std::ostream&  os)const{}
  void Read (std::istringstream& is);

  bool HandleMessage(const Telegram& msg);
};


///////////////////////////////////////////////////////////////////////////////



template <class entity_type>
void  Trigger_OnButtonSendMsg<entity_type>::Try(entity_type* pEnt)
{
  
  if (this->isTouchingTrigger(pEnt->Pos(), pEnt->BRadius()))
  {
    
      Dispatcher->DispatchMsg(SEND_MSG_IMMEDIATELY,
                              this->ID(),
                              m_iReceiver,
                              m_iMessageToSend,
                              NULL);

  }
}

template <class entity_type>
void Trigger_OnButtonSendMsg<entity_type>::Update()
{

 
}


template <class entity_type>
void Trigger_OnButtonSendMsg<entity_type>::Read(std::istringstream& is)
{
  //grab the id of the entity it messages
  is >> m_iReceiver;

  //grab the message type
  is >> m_iMessageToSend;
  //grab the position and radius
  double x,y,r;
  is >> x >> y >> r;

  this->SetPos(Vector2D(x,y));
  this->SetBRadius(r);
  is>>r;
  //create and set this trigger's region of fluence
  this->AddRectangularTriggerRegion(this->Pos()-Vector2D(this->BRadius(), this->BRadius()),   //top left corner
                              this->Pos()+Vector2D(this->BRadius(), this->BRadius()));  //bottom right corner
}

template <class entity_type>
bool Trigger_OnButtonSendMsg<entity_type>::HandleMessage(const Telegram& msg)
{
  return false;
}

#endif
