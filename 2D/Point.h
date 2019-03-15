#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <math.h>

using namespace std;

// Class to represent points.
class POINT {

public:

        double x, y;
        // Constructor uses default arguments to allow calling with zero, one,
        // or two values.
        POINT(double a = 0.0, double b = 0.0) {
                x = a;
                y = b;
        }
        
        // Extractors.

        // Distance to another point.  Pythagorean thm.
        double dist(POINT other) {
                double xd = x - other.x;
                double yd = y - other.y;
                return sqrt(xd*xd + yd*yd);
        }

        // Add or subtract two points.
        POINT add(POINT b)
        {
                return POINT(x + b.x, y + b.y);
        }
        POINT sub(POINT b)
        {
                return POINT(x - b.x, y - b.y);
        }

        // Move the existing point.
        void move(double a, double b)
        {
                x += a;
                y += b;
        }

        // Print the point on the stream.  The class ostream is a base class
        // for output streams of various types.
        void print(ostream &strm)
        {
                strm << "(" << x << "," << y << ")";
        }
};


#endif
