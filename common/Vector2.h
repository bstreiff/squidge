#pragma once

#include <stdint.h>
#include <iostream>

namespace squidge {

template<typename T>
class Vector2Base
{
public:
   inline Vector2Base();
   inline Vector2Base(const T& x, const T& y);
   inline Vector2Base(const Vector2Base& other);
   inline Vector2Base& operator=(const Vector2Base& other);

   inline T length() const;
   inline T squaredLength() const;
   inline Vector2Base unit() const;

public:
   T x;
   T y;
};

template<typename T>
inline bool operator==(const Vector2Base<T>& a, const Vector2Base<T>& b);

template<typename T>
inline bool operator!=(const Vector2Base<T>& a, const Vector2Base<T>& b);

template<typename T>
inline Vector2Base<T> operator+(const Vector2Base<T>& a, const Vector2Base<T>& b);

template<typename T>
inline Vector2Base<T> operator-(const Vector2Base<T>& a, const Vector2Base<T>& b);

template<typename T>
inline Vector2Base<T> operator*(const Vector2Base<T>& a, const Vector2Base<T>& b);

template<typename T>
inline Vector2Base<T> operator/(const Vector2Base<T>& a, const Vector2Base<T>& b);

template<typename T, typename S>
inline Vector2Base<T> operator*(const Vector2Base<T>& a, S b);

template<typename T, typename S>
inline Vector2Base<T> operator/(const Vector2Base<T>& a, S b);

template<typename T>
inline T dot(const Vector2Base<T>& a, const Vector2Base<T>& b);

template<typename T>
inline T cross(const Vector2Base<T>& a, const Vector2Base<T>& b);

template<typename T>
inline std::ostream& operator<<(std::ostream& os, const Vector2Base<T>& b);

typedef Vector2Base<float>   Vector2f;
typedef Vector2Base<int32_t> Point;

} // namespace squidge

#include "common/Vector2.ipp"
