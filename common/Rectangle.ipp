#pragma once

namespace squidge {

template<typename T>
RectangleBase<T>::RectangleBase() :
   x(),
   y(),
   width(),
   height()
{ }

template<typename T>
RectangleBase<T>::RectangleBase(const T& xx, const T& yy, const T& ww, const T& hh) :
   x(xx),
   y(yy),
   width(ww),
   height(hh)
{ }

template<typename T>
RectangleBase<T>::RectangleBase(const Vector2Base<T>& topLeft, const Vector2Base<T>& bottomRight) :
   x(topLeft.x),
   y(topLeft.y),
   width(bottomRight.x - topLeft.x),
   height(bottomRight.y - topLeft.y)
{ }

template<typename T>
RectangleBase<T>::RectangleBase(const RectangleBase<T>& other) :
   x(other.x),
   y(other.y),
   width(other.width),
   height(other.height)
{ }

template<typename T>
RectangleBase<T>& RectangleBase<T>::operator=(const RectangleBase<T>& other)
{
   x = other.x;
   y = other.y;
   width = other.width;
   height = other.height;

   return *this;
}

template<typename T>
Vector2Base<T> RectangleBase<T>::center() const
{
   return Vector2Base<T>((x + width) / 2, (y + height) / 2);
}

template<typename T>
T RectangleBase<T>::top() const
{
   return y;
}

template<typename T>
T RectangleBase<T>::bottom() const
{
   return y + height;
}

template<typename T>
T RectangleBase<T>::left() const
{
   return x;
}

template<typename T>
T RectangleBase<T>::right() const
{
   return x + width;
}

template<typename T>
bool operator==(const RectangleBase<T>& a, const RectangleBase<T>& b)
{
   return a.x == b.x && a.y == b.y &&
          a.width == b.width && a.height == b.height;
}

template<typename T>
bool operator!=(const RectangleBase<T>& a, const RectangleBase<T>& b)
{
   return !(a == b);
}


} // namespace squidge
