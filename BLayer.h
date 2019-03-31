#ifndef BLAYER_H
#define BLAYER_H

#include "Level.h"
#include "Game.h"
#include "TextureManager.h"
#include "Layer.h"

class Level;

class BLayer : public Layer
{
public:
  BLayer();
  virtual ~BLayer(){}
    
    virtual void render();
    virtual void update(Level* pLevel);
};


#endif
