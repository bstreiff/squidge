#pragma once

#include <stdint.h>
#include <iostream>

namespace squidge {

class Point
{
public:
   Point();
   Point(int32_t x, int32_t y);
   Point(const Point& other);
   Point& operator=(const Point& other);

public:
   int32_t x;
   int32_t y;
};

bool operator==(const Point& a, const Point& b);
bool operator!=(const Point& a, const Point& b);
Point operator+(const Point& a, const Point& b);
Point operator-(const Point& a, const Point& b);
Point operator*(const Point& a, const Point& b);
Point operator/(const Point& a, const Point& b);

Point operator*(const Point& a, int32_t b);
Point operator/(const Point& a, int32_t b);

std::ostream& operator<<(std::ostream& os, const Point& b);

} // namespace squidge
