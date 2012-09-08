#pragma once

namespace squidge {

template<typename T>
inline Vector2Base<T>::Vector2Base(const T& xx, const T& yy) :
   x(xx),
   y(yy)
{ }

template<typename T>
inline Vector2Base<T>::Vector2Base(const Vector2Base<T>& other) :
   x(other.x),
   y(other.y)
{ }

template<typename T>
inline T Vector2Base<T>::length() const
{
   return sqrt(squaredLength());
}

template<typename T>
inline T Vector2Base<T>::squaredLength() const
{
   return x*x + y*y;
}

template<typename T>
inline Vector2Base<T> Vector2Base<T>::unit() const
{
   return (*this / this->length());
}

template<typename T>
inline Vector2Base<T> operator==(const Vector2Base<T>& a, const Vector2Base<T>& b)
{
   return a.x == b.x && a.y == b.y;
}

template<typename T>
inline Vector2Base<T> operator!=(const Vector2Base<T>& a, const Vector2Base<T>& b)
{
   return !(a == b);
}

template<typename T>
inline Vector2Base<T> operator+(const Vector2Base<T>& a, const Vector2Base<T>& b)
{
   return Vector2Base<T>(a.x+b.x, a.y+b.y);
}

template<typename T>
inline Vector2Base<T> operator-(const Vector2Base<T>& a, const Vector2Base<T>& b)
{
   return Vector2Base<T>(a.x-b.x, a.y-b.y);
}

template<typename T>
inline Vector2Base<T> operator*(const Vector2Base<T>& a, const Vector2Base<T>& b)
{
   return Vector2Base<T>(a.x*b.x, a.y*b.y);
}

template<typename T>
inline Vector2Base<T> operator/(const Vector2Base<T>& a, const Vector2Base<T>& b)
{
   return Vector2Base<T>(a.x/b.x, a.y/b.y);
}

template<typename T, typename S>
inline Vector2Base<T> operator*(const Vector2Base<T>& a, S b)
{
   return Vector2Base<T>(a.x*b, a.y*b);
}

template<typename T, typename S>
inline Vector2Base<T> operator/(const Vector2Base<T>& a, S b)
{
   return Vector2Base<T>(a.x/b, a.y/b);
}

template<typename T>
inline T dot(const Vector2Base<T>& a, const Vector2Base<T>& b)
{
   return a.x*b.x + a.y*b.y;
}

template<typename T>
inline T cross(const Vector2Base<T>& a, const Vector2Base<T>& b)
{
   return a.x * b.y - a.y * b.x;
}

} // namespace squidge
