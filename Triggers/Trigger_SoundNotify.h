#ifndef TRIGGER_SOUNDNOTIFY_H
#define TRIGGER_SOUNDNOTIFY_H
#pragma warning (disable:4786)
//-----------------------------------------------------------------------------
//
//  Name:     Trigger_SoundNotify.h
//
//  Author:   Shaun Hose
//
//  Desc:     whenever an agent makes a sound -- such as when a weapon fires --
//            this trigger can be used to notify other bots of the event.
//
//            This type of trigger has a circular trigger region and a lifetime
//            of 1 update-step
//
//-----------------------------------------------------------------------------
#include "Trigger_LimitedLifeTime.h"
#include "../Character.h"



class Trigger_SoundNotify : public Trigger_LimitedLifetime<Character>
{
private:

  //a pointer to the bot that has made the sound
  Character*  m_pSoundSource;

public:

  Trigger_SoundNotify(Character* source, double range);
   
  void load(LoadParams* pParams){}
  void  Try(Character*);

  void  Render(){}

};




#endif
