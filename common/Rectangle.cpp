#include "common/Rectangle.h"

namespace squidge {

Rectangle::Rectangle() :
   x(),
   y(),
   width(),
   height()
{ }

Rectangle::Rectangle(int32_t xx, int32_t yy, int32_t ww, int32_t hh) :
   x(xx),
   y(yy),
   width(ww),
   height(hh)
{ }

Rectangle::Rectangle(const Point& topLeft, const Point& bottomRight) :
   x(topLeft.x),
   y(topLeft.y),
   width(bottomRight.x - topLeft.x),
   height(bottomRight.y - topLeft.y)
{ }

Rectangle::Rectangle(const Rectangle& other) :
   x(other.x),
   y(other.y),
   width(other.width),
   height(other.height)
{ }

Rectangle& Rectangle::operator=(const Rectangle& other)
{
   if (this == &other)
      return *this;

   x = other.x;
   y = other.y;
   width = other.width;
   height = other.height;

   return *this;
}

Point Rectangle::center() const
{
   return Point((x + width) / 2, (y + height) / 2);
}

int32_t Rectangle::top() const
{
   return y;
}

int32_t Rectangle::bottom() const
{
   return y + height;
}

int32_t Rectangle::left() const
{
   return x;
}

int32_t Rectangle::right() const
{
   return x + width;
}

bool Rectangle::contains(const Point& point) const
{
   return (point.x >= x && point.x < (x + width)) &&
          (point.y >= y && point.y < (y + height));
}

bool Rectangle::contains(int32_t pointx, int32_t pointy) const
{
   return (pointx >= x && pointx < (x + width)) &&
          (pointy >= y && pointy < (y + height));
}

bool operator==(const Rectangle& a, const Rectangle& b)
{
   return a.x == b.x && a.y == b.y &&
          a.width == b.width && a.height == b.height;
}

bool operator!=(const Rectangle& a, const Rectangle& b)
{
   return !(a == b);
}

std::ostream& operator<<(std::ostream& os, const Rectangle& b)
{
   return os << "[x=" << b.x << ", y=" << b.y << ", w=" << b.width << ", h=" << b.height << "]";
}


} // namespace squidge
