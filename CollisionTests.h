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


// //----------------------- doRectsObstructCylinderSides -------------------------
// //
// //  similar to above except this version checks to see if the sides described
// //  by the cylinder of length |AB| with the given radius intersect any rects.
// //  (this enables the trace to take into account any the bounding radii of
// //  entity objects)
// //-----------------------------------------------------------------------------
// template <class ContRect>
// inline bool doRectsObstructCylinderSides(Vector2D        A,
//                                          Vector2D        B,
//                                          double           BoundingRadius,
//                                          const ContRect& rects)
// {
//   //the line segments that make up the sides of the cylinder must be created
//   Vector2D toB = Vec2DNormalize(B-A);

//   //A1B1 will be one side of the cylinder, A2B2 the other.
//   Vector2D A1, B1, A2, B2;

//   Vector2D radialEdge = toB.Perp() * BoundingRadius;

//   //create the two sides of the cylinder
//   A1 = A + radialEdge;
//   B1 = B + radialEdge;

//   A2 = A - radialEdge;
//   B2 = B - radialEdge;

//   //now test against them
//   if (!doRectsObstructLineSegment(A1, B1, rects))
//   {
//     return doRectsObstructLineSegment(A2, B2, rects);
//   }
  
//   return true;
// }

// //------------------ FindClosestPointOfIntersectionWithRects ------------------
// //
// //  tests a line segment against the container of rects  to calculate
// //  the closest intersection point, which is stored in the reference 'ip'. The
// //  distance to the point is assigned to the reference 'distance'
// //
// //  returns false if no intersection point found
// //-----------------------------------------------------------------------------

// template <class ContRect>
// inline bool FindClosestPointOfIntersectionWithRects(Vector2D        A,
//                                                     Vector2D        B,
//                                                     double&          distance,
//                                                     Vector2D&       ip,
//                                                     const ContRect& rects)
// {
//   distance = MaxDouble;

//   typename ContRect::const_iterator curRect = rects.begin();
//   for (curRect; curRect != rects.end(); ++curRect)
//   {
//     double dist = 0.0;
//     Vector2D point;

//     if (LineIntersection2D(A, B, (*curRect)->From(), (*curRect)->To(), dist, point))
//     {
//       if (dist < distance)
//       {
//         distance = dist;
//         ip = point;
//       }
//     }
//   }

//   if (distance < MaxDouble) return true;

//   return false;
// }

// //------------------------ doRectsIntersectCircle -----------------------------
// //
// //  returns true if any rects intersect the circle of radius at point p
// //-----------------------------------------------------------------------------
// template <class ContRect>
// inline bool doRectsIntersectCircle(const ContRect& rects, Vector2D p, double r)
// {
//   //test against the rects
//   typename ContRect::const_iterator curRect = rects.begin();

//   for (curRect; curRect != rects.end(); ++curRect)
//   {
//     //do a line segment intersection test
//     if (LineSegmentCircleIntersection((*curRect)->From(), (*curRect)->To(), p, r))
//     {
//       return true;
//     }
//   }
                                                                           
//   return false;
// }



#endif
