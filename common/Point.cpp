#include "common/Point.h"
#include <math.h>

namespace squidge {

Point::Point() :
   x(),
   y()
{ }

Point::Point(int32_t xx, int32_t yy) :
   x(xx),
   y(yy)
{ }

Point::Point(const Point& other) :
   x(other.x),
   y(other.y)
{ }

Point& Point::operator=(const Point& other)
{
   x = other.x;
   y = other.y;
   return *this;
}

bool operator==(const Point& a, const Point& b)
{
   return a.x == b.x && a.y == b.y;
}

bool operator!=(const Point& a, const Point& b)
{
   return !(a == b);
}

Point operator+(const Point& a, const Point& b)
{
   return Point(a.x+b.x, a.y+b.y);
}


Point operator-(const Point& a, const Point& b)
{
   return Point(a.x-b.x, a.y-b.y);
}


Point operator*(const Point& a, const Point& b)
{
   return Point(a.x*b.x, a.y*b.y);
}


Point operator/(const Point& a, const Point& b)
{
   return Point(a.x/b.x, a.y/b.y);
}

Point operator*(const Point& a, int32_t b)
{
   return Point(a.x*b, a.y*b);
}

Point operator/(const Point& a, int32_t b)
{
   return Point(a.x/b, a.y/b);
}

std::ostream& operator<<(std::ostream& os, const Point& b)
{
   return os << '(' << b.x << ',' << b.y << ')';
}

} // namespace squidge
