#include "common/Vector3.h"
#include "common/Vector2.h"
#include <math.h>

namespace squidge {

Vector3::Vector3() :
   x(),
   y(),
   z()
{ }

Vector3::Vector3(float xx, float yy, float zz) :
   x(xx),
   y(yy),
   z(zz)
{ }

Vector3::Vector3(const Vector2& xy, float zz) :
   x(xy.x),
   y(xy.y),
   z(zz)
{ }

Vector3::Vector3(const Vector3& other) :
   x(other.x),
   y(other.y),
   z(other.z)
{ }

Vector3& Vector3::operator=(const Vector3& other)
{
   x = other.x;
   y = other.y;
   z = other.z;
   return *this;
}

float Vector3::length() const
{
   return sqrt(lengthSquared());
}

float Vector3::lengthSquared() const
{
   return x*x + y*y + z*z;
}

Vector3 Vector3::unit() const
{
   return (*this / this->length());
}

void Vector3::add(const Vector3& a, const Vector3& b, Vector3& result)
{
   result.x = a.x + b.x;
   result.y = a.y + b.y;
   result.z = a.z + b.z;
}

void Vector3::divide(const Vector3& a, float b, Vector3& result)
{
   result.x = a.x / b;
   result.y = a.y / b;
   result.y = a.z / b;
}

void Vector3::divide(const Vector3& a, const Vector3& b, Vector3& result)
{
   result.x = a.x / b.x;
   result.y = a.y / b.y;
   result.z = a.z / b.z;
}

void Vector3::max(const Vector3& a, const Vector3& b, Vector3& result)
{
   result.x = std::max(a.x, b.x);
   result.y = std::max(a.y, b.y);
   result.z = std::max(a.z, b.z);
}

void Vector3::min(const Vector3& a, const Vector3& b, Vector3& result)
{
   result.x = std::min(a.x, b.x);
   result.y = std::min(a.y, b.y);
   result.z = std::min(a.z, b.z);
}

void Vector3::multiply(const Vector3& a, float b, Vector3& result)
{
   result.x = a.x * b;
   result.y = a.y * b;
   result.z = a.z * b;
}

void Vector3::multiply(const Vector3& a, const Vector3& b, Vector3& result)
{
   result.x = a.x * b.x;
   result.y = a.y * b.y;
   result.z = a.z * b.z;
}

void Vector3::negate(const Vector3& a, Vector3& result)
{
   result.x = -a.x;
   result.y = -a.y;
   result.z = -a.z;
}

void Vector3::subtract(const Vector3& a, const Vector3& b, Vector3& result)
{
   result.x = a.x - b.x;
   result.y = a.y - b.y;
   result.z = a.z - b.z;
}

void Vector3::lerp(const Vector3& start, const Vector3& end, float amount, Vector3& result)
{
   result.x = start.x + (end.x - start.x) * amount;
   result.y = start.y + (end.y - start.y) * amount;
   result.z = start.z + (end.z - start.z) * amount;
}

float Vector3::dot(const Vector3& a, const Vector3& b)
{
   return a.x*b.x + a.y*b.y + a.z*b.z;
}

bool operator==(const Vector3& a, const Vector3& b)
{
   return a.x == b.x && a.y == b.y && a.z == b.z;
}

bool operator!=(const Vector3& a, const Vector3& b)
{
   return !(a == b);
}

Vector3 operator+(const Vector3& a, const Vector3& b)
{
   Vector3 result;
   Vector3::add(a, b, result);
   return result;
}

Vector3 operator-(const Vector3& a, const Vector3& b)
{
   Vector3 result;
   Vector3::subtract(a, b, result);
   return result;
}

Vector3 operator*(const Vector3& a, const Vector3& b)
{
   Vector3 result;
   Vector3::multiply(a, b, result);
   return result;
}

Vector3 operator/(const Vector3& a, const Vector3& b)
{
   Vector3 result;
   Vector3::divide(a, b, result);
   return result;
}

Vector3 operator*(const Vector3& a, float b)
{
   Vector3 result;
   Vector3::multiply(a, b, result);
   return result;
}

Vector3 operator/(const Vector3& a, float b)
{
   Vector3 result;
   Vector3::divide(a, b, result);
   return result;
}

std::ostream& operator<<(std::ostream& os, const Vector3& b)
{
   return os << '{' << b.x << ',' << b.y << ',' << b.z << '}';
}

} // namespace squidge
