#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"
#include "Messaging/Telegram.h"
#include "Messages.h"
#include "SensoryMemory.h"
#include "Messaging/MessageDispatcher.h"
#include "Goals/Goal_Think.h"

class Player : public Character{
 public:
  Player(Room* room, Vector2D pos);
  bool HandleMessage(const Telegram& msg);
  void test(){std::cout << "WORKING";}

};





#endif
