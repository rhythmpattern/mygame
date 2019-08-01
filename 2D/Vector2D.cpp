#include "Vector2D.h"
#include <fstream>

std::ostream& operator<<(std::ostream& os, const Vector2D& rhs)
{
  os << " " << rhs.x << " " << rhs.y;

  return os;
}

  
std::istringstream& operator>>(std::istringstream& is, Vector2D& lhs)
{
  is >> lhs.x >> lhs.y;

  return is;
}

