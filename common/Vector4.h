#pragma once

#include <iostream>

namespace squidge {

class Vector2;
class Vector3;

class Vector4
{
public:
   Vector4();
   Vector4(float x, float y, float z, float w);
   Vector4(const Vector2& xy, float z, float w);
   Vector4(const Vector3& xyz, float w);
   Vector4(const Vector4& other);
   Vector4& operator=(const Vector4& other);

   float length() const;
   float lengthSquared() const;
   Vector4 unit() const;

   static void add(const Vector4& a, const Vector4& b, Vector4& result);
   static void divide(const Vector4& a, float b, Vector4& result);
   static void divide(const Vector4& a, const Vector4& b, Vector4& result);
   static void max(const Vector4& a, const Vector4& b, Vector4& result);
   static void min(const Vector4& a, const Vector4& b, Vector4& result);
   static void multiply(const Vector4& a, float b, Vector4& result);
   static void multiply(const Vector4& a, const Vector4& b, Vector4& result);
   static void negate(const Vector4& a, Vector4& result);
   static void subtract(const Vector4& a, const Vector4& b, Vector4& result);

   static float dot(const Vector4& a, const Vector4& b);

public:
   float x;
   float y;
   float z;
   float w;
};

bool operator==(const Vector4& a, const Vector4& b);
bool operator!=(const Vector4& a, const Vector4& b);
Vector4 operator+(const Vector4& a, const Vector4& b);
Vector4 operator-(const Vector4& a, const Vector4& b);
Vector4 operator*(const Vector4& a, const Vector4& b);
Vector4 operator/(const Vector4& a, const Vector4& b);

Vector4 operator*(const Vector4& a, float b);
Vector4 operator/(const Vector4& a, float b);

std::ostream& operator<<(std::ostream& os, const Vector4& b);

} // namespace squidge
