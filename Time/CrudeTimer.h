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




#define Clock CrudeTimer::Instance()

class CrudeTimer
{
private:
  
  std::time_t timev;
	
  //set to the time (in seconds) when class is instantiated
  double m_dStartTime;

  //set the start time
  CrudeTimer(){m_dStartTime = double(clock())/CLOCKS_PER_SEC ;}

  //copy ctor and assignment should be private
  CrudeTimer(const CrudeTimer&);
  CrudeTimer& operator=(const CrudeTimer&);
  
public:

  static CrudeTimer* Instance();

  //returns how much time has elapsed since the timer was started
  double GetCurrentTime(){return  (double(clock())/CLOCKS_PER_SEC)  - m_dStartTime;}

};







#endif
