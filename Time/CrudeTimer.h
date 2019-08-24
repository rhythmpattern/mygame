#ifndef CRUDETIMER_H
#define CRUDETIMER_H
//------------------------------------------------------------------------
//
//  Name:   CrudeTimer.h
//
//  Desc:   timer to measure time in seconds
//
//  Author: Shaun Hose
//
//------------------------------------------------------------------------

//this library must be included
#pragma comment(lib, "winmm.lib")
#include <ctime>
#include <SDL2/SDL.h>



#define Clock CrudeTimer::Instance()

class CrudeTimer
{
private:
  
  std::time_t timev;
	
  //set to the time (in seconds) when class is instantiated
  double m_dStartTime;

  //set the start time
  CrudeTimer(){m_dStartTime = SDL_GetTicks()/1000.f ;}

  //copy ctor and assignment should be private
  CrudeTimer(const CrudeTimer&);
  CrudeTimer& operator=(const CrudeTimer&);
  
public:

  static CrudeTimer* Instance();

  //returns how much time has elapsed since the timer was started
  double GetCurrentTime(){return  (SDL_GetTicks()/1000.f);}

};







#endif
