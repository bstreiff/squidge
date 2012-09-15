#pragma once

#include <iostream>

namespace squidge {

class Vector2;

class Vector3
{
public:
   Vector3();
   Vector3(float x, float y, float z);
   Vector3(const Vector2& xy, float z);
   Vector3(const Vector3& other);
   Vector3& operator=(const Vector3& other);

   float length() const;
   float lengthSquared() const;
   Vector3 unit() const;

   static void add(const Vector3& a, const Vector3& b, Vector3& result);
   static void divide(const Vector3& a, float b, Vector3& result);
   static void divide(const Vector3& a, const Vector3& b, Vector3& result);
   static void max(const Vector3& a, const Vector3& b, Vector3& result);
   static void min(const Vector3& a, const Vector3& b, Vector3& result);
   static void multiply(const Vector3& a, float b, Vector3& result);
   static void multiply(const Vector3& a, const Vector3& b, Vector3& result);
   static void negate(const Vector3& a, Vector3& result);
   static void subtract(const Vector3& a, const Vector3& b, Vector3& result);

   static float dot(const Vector3& a, const Vector3& b);

public:
   float x;
   float y;
   float z;
};

bool operator==(const Vector3& a, const Vector3& b);
bool operator!=(const Vector3& a, const Vector3& b);
Vector3 operator+(const Vector3& a, const Vector3& b);
Vector3 operator-(const Vector3& a, const Vector3& b);
Vector3 operator*(const Vector3& a, const Vector3& b);
Vector3 operator/(const Vector3& a, const Vector3& b);

Vector3 operator*(const Vector3& a, float b);
Vector3 operator/(const Vector3& a, float b);

std::ostream& operator<<(std::ostream& os, const Vector3& b);

} // namespace squidge
