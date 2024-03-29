#ifndef ZOMBIE_H
#define ZOMBIE_H

#include "Character.h"
#include "ObjectEnumerations.h"
#include "misc/utils.h"
#include "2D/Transformations.h"
#include "Game.h"
#include "Navigation/PathPlanner.h"
#include "SteeringBehaviors.h"
#include "UserOptions.h"
#include "Time/Regulator.h"
#include "WeaponSystem.h"
#include "SensoryMemory.h"
#include "Messaging/Telegram.h"
#include "Messages.h"
#include "Messaging/MessageDispatcher.h"
#include "Goals/Goal_Think_Zombie.h"
#include "2D/Vector2D.h"

class Room;

class Zombie : public Character
{
 private:
  bool speedUp;
  Room* m_pRoom;
 public:
  Zombie(Room* room, Vector2D pos);
  virtual bool HandleMessage(const Telegram& msg);
  virtual void Update();

};

#endif
