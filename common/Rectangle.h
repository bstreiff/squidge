#pragma once

#include "common/Vector2.h"

namespace squidge {

template<typename T>
class RectangleBase
{
public:
   inline RectangleBase();
   inline RectangleBase(const T& x, const T& y, const T& w, const T& h);
   inline RectangleBase(const Vector2Base<T>& topLeft, const Vector2Base<T>& bottomRight);
   inline RectangleBase(const RectangleBase<T>& other);

   inline RectangleBase<T>& operator=(const RectangleBase<T>& other);

   inline Vector2Base<T> center() const;
   inline T top() const;
   inline T bottom() const;
   inline T left() const;
   inline T right() const;

public:
   T x;
   T y;
   T width;
   T height;
};

template<typename T>
bool operator==(const RectangleBase<T>& a, const RectangleBase<T>& b);

template<typename T>
bool operator!=(const RectangleBase<T>& a, const RectangleBase<T>& b);


typedef RectangleBase<int32_t> Rectangle;

}

#include "common/Rectangle.ipp"