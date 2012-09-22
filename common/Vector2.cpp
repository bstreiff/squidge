#include "common/Vector2.h"
#include <math.h>

namespace squidge {

Vector2::Vector2() :
   x(),
   y()
{ }

Vector2::Vector2(float xx, float yy) :
   x(xx),
   y(yy)
{ }

Vector2::Vector2(const Vector2& other) :
   x(other.x),
   y(other.y)
{ }

Vector2& Vector2::operator=(const Vector2& other)
{
   x = other.x;
   y = other.y;
   return *this;
}

float Vector2::length() const
{
   return sqrt(lengthSquared());
}

float Vector2::lengthSquared() const
{
   return x*x + y*y;
}

Vector2 Vector2::unit() const
{
   return (*this / this->length());
}

void Vector2::add(const Vector2& a, const Vector2& b, Vector2& result)
{
   result.x = a.x + b.x;
   result.y = a.y + b.y;
}

void Vector2::divide(const Vector2& a, float b, Vector2& result)
{
   result.x = a.x / b;
   result.y = a.y / b;
}

void Vector2::divide(const Vector2& a, const Vector2& b, Vector2& result)
{
   result.x = a.x / b.x;
   result.y = a.y / b.y;
}

void Vector2::max(const Vector2& a, const Vector2& b, Vector2& result)
{
   result.x = std::max(a.x, b.x);
   result.y = std::max(a.y, b.y);
}

void Vector2::min(const Vector2& a, const Vector2& b, Vector2& result)
{
   result.x = std::min(a.x, b.x);
   result.y = std::min(a.y, b.y);
}

void Vector2::multiply(const Vector2& a, float b, Vector2& result)
{
   result.x = a.x * b;
   result.y = a.y * b;
}

void Vector2::multiply(const Vector2& a, const Vector2& b, Vector2& result)
{
   result.x = a.x * b.x;
   result.y = a.y * b.y;
}

void Vector2::negate(const Vector2& a, Vector2& result)
{
   result.x = -a.x;
   result.y = -a.y;
}

void Vector2::subtract(const Vector2& a, const Vector2& b, Vector2& result)
{
   result.x = a.x - b.x;
   result.y = a.y - b.y;
}

void Vector2::lerp(const Vector2& start, const Vector2& end, float amount, Vector2& result)
{
   result.x = start.x + (end.x - start.x) * amount;
   result.y = start.y + (end.y - start.y) * amount;
}

float Vector2::dot(const Vector2& a, const Vector2& b)
{
   return a.x*b.x + a.y*b.y;
}

bool operator==(const Vector2& a, const Vector2& b)
{
   return a.x == b.x && a.y == b.y;
}

bool operator!=(const Vector2& a, const Vector2& b)
{
   return !(a == b);
}

Vector2 operator+(const Vector2& a, const Vector2& b)
{
   Vector2 result;
   Vector2::add(a, b, result);
   return result;
}

Vector2 operator-(const Vector2& a, const Vector2& b)
{
   Vector2 result;
   Vector2::subtract(a, b, result);
   return result;
}

Vector2 operator*(const Vector2& a, const Vector2& b)
{
   Vector2 result;
   Vector2::multiply(a, b, result);
   return result;
}

Vector2 operator/(const Vector2& a, const Vector2& b)
{
   Vector2 result;
   Vector2::divide(a, b, result);
   return result;
}

Vector2 operator*(const Vector2& a, float b)
{
   Vector2 result;
   Vector2::multiply(a, b, result);
   return result;
}

Vector2 operator/(const Vector2& a, float b)
{
   Vector2 result;
   Vector2::divide(a, b, result);
   return result;
}

std::ostream& operator<<(std::ostream& os, const Vector2& b)
{
   return os << '{' << b.x << ',' << b.y << '}';
}

} // namespace squidge
