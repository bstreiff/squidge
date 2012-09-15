#include "common/Vector4.h"
#include "common/Vector2.h"
#include "common/Vector3.h"
#include <math.h>

namespace squidge {

Vector4::Vector4() :
   x(),
   y(),
   z(),
   w()
{ }

Vector4::Vector4(float xx, float yy, float zz, float ww) :
   x(xx),
   y(yy),
   z(zz),
   w(ww)
{ }

Vector4::Vector4(const Vector4& other) :
   x(other.x),
   y(other.y),
   z(other.z),
   w(other.w)
{ }

Vector4& Vector4::operator=(const Vector4& other)
{
   x = other.x;
   y = other.y;
   z = other.z;
   w = other.w;
   return *this;
}

float Vector4::length() const
{
   return sqrt(lengthSquared());
}

float Vector4::lengthSquared() const
{
   return x*x + y*y + z*z + w*w;
}

Vector4 Vector4::unit() const
{
   return (*this / this->length());
}

void Vector4::add(const Vector4& a, const Vector4& b, Vector4& result)
{
   result.x = a.x + b.x;
   result.y = a.y + b.y;
   result.z = a.z + b.z;
   result.w = a.w + b.w;
}

void Vector4::divide(const Vector4& a, float b, Vector4& result)
{
   result.x = a.x / b;
   result.y = a.y / b;
   result.z = a.z / b;
   result.w = a.w / b;
}

void Vector4::divide(const Vector4& a, const Vector4& b, Vector4& result)
{
   result.x = a.x / b.x;
   result.y = a.y / b.y;
   result.z = a.z / b.z;
   result.w = a.w / b.w;
}

void Vector4::max(const Vector4& a, const Vector4& b, Vector4& result)
{
   result.x = std::max(a.x, b.x);
   result.y = std::max(a.y, b.y);
   result.z = std::max(a.z, b.z);
   result.w = std::max(a.w, b.w);
}

void Vector4::min(const Vector4& a, const Vector4& b, Vector4& result)
{
   result.x = std::min(a.x, b.x);
   result.y = std::min(a.y, b.y);
   result.z = std::min(a.z, b.z);
   result.w = std::min(a.w, b.w);
}

void Vector4::multiply(const Vector4& a, float b, Vector4& result)
{
   result.x = a.x * b;
   result.y = a.y * b;
   result.z = a.z * b;
   result.w = a.w * b;
}

void Vector4::multiply(const Vector4& a, const Vector4& b, Vector4& result)
{
   result.x = a.x * b.x;
   result.y = a.y * b.y;
   result.z = a.z * b.z;
   result.w = a.w * b.w;
}

void Vector4::negate(const Vector4& a, Vector4& result)
{
   result.x = -a.x;
   result.y = -a.y;
   result.z = -a.z;
   result.w = -a.w;
}

void Vector4::subtract(const Vector4& a, const Vector4& b, Vector4& result)
{
   result.x = a.x - b.x;
   result.y = a.y - b.y;
   result.z = a.z - b.z;
   result.w = a.w - b.w;
}

float Vector4::dot(const Vector4& a, const Vector4& b)
{
   return a.x*b.x + a.y*b.y + a.z*b.z + a.w*b.w;
}

bool operator==(const Vector4& a, const Vector4& b)
{
   return a.x == b.x && a.y == b.y && a.z == b.z && a.w == b.w;
}

bool operator!=(const Vector4& a, const Vector4& b)
{
   return !(a == b);
}

Vector4 operator+(const Vector4& a, const Vector4& b)
{
   Vector4 result;
   Vector4::add(a, b, result);
   return result;
}

Vector4 operator-(const Vector4& a, const Vector4& b)
{
   Vector4 result;
   Vector4::subtract(a, b, result);
   return result;
}

Vector4 operator*(const Vector4& a, const Vector4& b)
{
   Vector4 result;
   Vector4::multiply(a, b, result);
   return result;
}

Vector4 operator/(const Vector4& a, const Vector4& b)
{
   Vector4 result;
   Vector4::divide(a, b, result);
   return result;
}

Vector4 operator*(const Vector4& a, float b)
{
   Vector4 result;
   Vector4::multiply(a, b, result);
   return result;
}

Vector4 operator/(const Vector4& a, float b)
{
   Vector4 result;
   Vector4::divide(a, b, result);
   return result;
}

std::ostream& operator<<(std::ostream& os, const Vector4& b)
{
   return os << '{' << b.x << ',' << b.y << ',' << b.z << ',' << b.w << '}';
}

} // namespace squidge
