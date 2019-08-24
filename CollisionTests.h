#ifndef COLLISION_TESTS_H
#define COLLISION_TESTS_H

#include <SDL2/SDL.h>
#include "2D/Vector2D.h"
#include "2D/Wall2D.h"
//-----------------------------------------------------------------------------
//
//  Name:   CollisionTests.h
//
//  Author: Shaun Hose
//
//  Desc:   a few functions for testing line segments against rectangles
//-----------------------------------------------------------------------------

//A rectangle is defined by having positions: x and y. And dimensions:  w and h.
// x and y denote the upper left corner position of the Rectangle.

//----------------------- doRectsObstructLineSegment --------------------------
//
//  given a line segment defined by the points from and to, iterate through all
//  the Rectangles and test for any intersection. This method
//  returns true if an intersection occurs.
//-----------------------------------------------------------------------------
template <class ContRect>
inline bool doRectsObstructLineSegment(Vector2D from,
                                       Vector2D to,
                                       const ContRect& rects)
{
  //test against the rects
  typename ContRect::const_iterator curRect = rects.begin();

  for (curRect; curRect != rects.end(); ++curRect)
  {
    int x = (*curRect)->x;
    int y = (*curRect)->y;
    int w = (*curRect)->w;
    int h = (*curRect)->h;
    Vector2D A = Vector2D(x,y);
    Vector2D B = Vector2D(x+w,y);
    Vector2D C = Vector2D(x+w,y+h);
    Vector2D D = Vector2D(x,y+h);
    //do line segment intersection tests
    if (LineIntersection2D(from, to, A,B) ||
	LineIntersection2D(from, to , B,C) ||
	LineIntersection2D(from, to, C,D) ||
	LineIntersection2D(from, to, D,A))
    {
      return true;
    }
  }
                                                                           
  return false;
}

//------------------------ doRectsIntersectCircle -----------------------------
//
//  returns true if any rects intersect the circle of radius at point p
//-----------------------------------------------------------------------------
template <class ContRect>
inline bool doRectsIntersectCircle(const ContRect& rects, Vector2D p, double r)
{
  //test against the rects
  typename ContRect::const_iterator curRect = rects.begin();

  for (curRect; curRect != rects.end(); ++curRect)
  {
    int x = (*curRect)->x;
    int y = (*curRect)->y;
  int w = (*curRect)->w;
int h = (*curRect)->h;
    Vector2D A = Vector2D(x,y);
    Vector2D B = Vector2D(x+w , y);
    Vector2D C = Vector2D(x+w , y+h);
    Vector2D D = Vector2D(x , y+h);
    //do a line segment intersection test
    if (LineSegmentCircleIntersection(A,B, p, r) ||
	LineSegmentCircleIntersection(B,C, p, r)||
	LineSegmentCircleIntersection(C,D, p, r)||
	LineSegmentCircleIntersection(D,A, p, r))
    {
      return true;
    }
  }
                                                                           
  return false;
}
template <class ContRect>
inline bool checkRectCollision( SDL_Rect* a, SDL_Rect* b )
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = a->x;
    rightA = a->x + a->w;
    topA = a->y;
    bottomA = a->y + a->h;

    //Calculate the sides of rect B
    leftB = b->x;
    rightB = b->x + b->w;
    topB = b->y;
    bottomB = b->y + b->h;

    //If any of the sides from A are outside of B
    if( bottomA <= topB )
    {
        return false;
    }

    if( topA >= bottomB )
    {
        return false;
    }

    if( rightA <= leftB )
    {
        return false;
    }

    if( leftA >= rightB )
    {
        return false;
    }

    //If none of the sides from A are outside B
    return true;
}


#endif
