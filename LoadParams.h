//
//  LoadParams.h

#ifndef LOAD_PARAMS_H
#define LOAD_PARAMS_H

#include <string>

class LoadParams
{
public:
    
  LoadParams(int a, int b) 
    {
      x = a;
      y = b;
    }
    
  int getX () { return x;}
  int getY () {return y;}
    
private:
  int x,y;
   
};

#endif
