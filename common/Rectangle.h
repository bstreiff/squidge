#pragma once

#include "common/Point.h"
#include <iostream>

namespace squidge {

class Rectangle
{
public:
   Rectangle();
   Rectangle(int32_t x, int32_t y, int32_t w, int32_t h);
   Rectangle(const Point& topLeft, const Point& bottomRight);
   Rectangle(const Rectangle& other);

   Rectangle& operator=(const Rectangle& other);

   Point center() const;
   int32_t top() const;
   int32_t bottom() const;
   int32_t left() const;
   int32_t right() const;

   bool contains(const Point& point) const;
   bool contains(int32_t pointx, int32_t pointy) const;

public:
   int32_t x;
   int32_t y;
   int32_t width;
   int32_t height;
};

bool operator==(const Rectangle& a, const Rectangle& b);
bool operator!=(const Rectangle& a, const Rectangle& b);

std::ostream& operator<<(std::ostream& os, const Rectangle& b);

} // namespace squidge
