#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"
#include "InputHandler.h"

class Player : public Character{
 public:
  Player(Game* world, Vector2D pos);

 private:
 void handleinput();

};





#endif
