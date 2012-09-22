#pragma once

#include <stdint.h>
#include <iostream>

namespace squidge {

class Vector2
{
public:
   Vector2();
   Vector2(float x, float y);
   Vector2(const Vector2& other);
   Vector2& operator=(const Vector2& other);

   float length() const;
   float lengthSquared() const;
   Vector2 unit() const;

   static void add(const Vector2& a, const Vector2& b, Vector2& result);
   static void divide(const Vector2& a, float b, Vector2& result);
   static void divide(const Vector2& a, const Vector2& b, Vector2& result);
   static void max(const Vector2& a, const Vector2& b, Vector2& result);
   static void min(const Vector2& a, const Vector2& b, Vector2& result);
   static void multiply(const Vector2& a, float b, Vector2& result);
   static void multiply(const Vector2& a, const Vector2& b, Vector2& result);
   static void negate(const Vector2& a, Vector2& result);
   static void subtract(const Vector2& a, const Vector2& b, Vector2& result);

   static void lerp(const Vector2& start, const Vector2& end, float amount, Vector2& result);

   static float dot(const Vector2& a, const Vector2& b);

public:
   float x;
   float y;
};

bool operator==(const Vector2& a, const Vector2& b);
bool operator!=(const Vector2& a, const Vector2& b);
Vector2 operator+(const Vector2& a, const Vector2& b);
Vector2 operator-(const Vector2& a, const Vector2& b);
Vector2 operator*(const Vector2& a, const Vector2& b);
Vector2 operator/(const Vector2& a, const Vector2& b);

Vector2 operator*(const Vector2& a, float b);
Vector2 operator/(const Vector2& a, float b);

std::ostream& operator<<(std::ostream& os, const Vector2& b);

} // namespace squidge
