#ifndef COLLISION_H
#define COLLISION_H

#include <SDL2/SDL.h>

class Collision
{
 public:
  Collision();
  ~Collision();
   bool RectRect(SDL_Rect* A, SDL_Rect* );
};

#endif
