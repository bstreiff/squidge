#pragma once

#include <stdexcept>

namespace squidge {

template<typename ElementType>
inline Cartograph<ElementType>::Cartograph() :
   _storage(),
   _bounds()
{ }

template<typename ElementType>
inline Cartograph<ElementType>::Cartograph(
   const Rectangle& bounds,
   ElementType value) :
   _storage(),
   _bounds()
{
   resize(bounds, value);
}

template<typename ElementType>
inline Cartograph<ElementType>::Cartograph(
   const Cartograph& other) :
   _storage(other._storage),
   _bounds(other._bounds)
{ }

template<typename ElementType>
inline Cartograph<ElementType>& Cartograph<ElementType>::operator=(
   const Cartograph& other)
{
   if (this == &other)
      return true;

   _storage = other._storage;
   _bounds = other._bounds;
   return *this;
}

template<typename ElementType>
inline bool Cartograph<ElementType>::operator==(
   const Cartograph& other) const
{
   if (this == &other)
      return true;

   if (_bounds != other._bounds)
      return false;

   return _storage == other._storage;
}

template<typename ElementType>
inline void Cartograph<ElementType>::resize(
   const Rectangle& bounds,
   ElementType value)
{
   if (bounds.width < 0)
      throw std::invalid_argument("Cartograph ctor: bounds have zero/negative width!");
   if (bounds.height < 0)
      throw std::invalid_argument("Cartograph ctor: bounds have zero/negative height!");

   _storage.resize(bounds.width * bounds.height, value);
   _bounds = bounds;
}

template<typename ElementType>
inline void Cartograph<ElementType>::clear()
{
   _storage.clear();
   _bounds = Rectangle(0,0,0,0);
}

template<typename ElementType>
inline typename Cartograph<ElementType>::iterator Cartograph<ElementType>::begin()
{
   return Cartograph::iterator(this, Point(_bounds.x, _bounds.y));
}

template<typename ElementType>
inline typename Cartograph<ElementType>::iterator Cartograph<ElementType>::end()
{
   // You would /think/ this would be (_bounds.x+w, _bounds.y+h), but the
   // iterator will automatically move to the next row, so we have to also.
   Point adjustedEnd(_bounds.x, _bounds.y + _bounds.height);

   return Cartograph::iterator(this, adjustedEnd);
}

template<typename ElementType>
inline const Rectangle& Cartograph<ElementType>::bounds() const
{
   return _bounds;
}

template<typename ElementType>
inline int32_t Cartograph<ElementType>::height() const
{
   return _bounds.height;
}

template<typename ElementType>
inline int32_t Cartograph<ElementType>::width() const
{
   return _bounds.width;
}

template<typename ElementType>
inline bool Cartograph<ElementType>::inRange(int32_t x, int32_t y) const
{
   return _bounds.contains(x, y);
}

template<typename ElementType>
inline bool Cartograph<ElementType>::inRange(const Point& xy) const
{
   return _bounds.contains(xy);
}

template<typename ElementType>
inline typename Cartograph<ElementType>::const_reference Cartograph<ElementType>::operator()(
   int32_t x, int32_t y) const
{
   return _storage[_offset(x, y)];
}

template<typename ElementType>
inline typename Cartograph<ElementType>::reference Cartograph<ElementType>::operator()(
   int32_t x, int32_t y)
{
   return _storage[_offset(x, y)];
}

template<typename ElementType>
inline typename Cartograph<ElementType>::const_reference Cartograph<ElementType>::at(
   int32_t x, int32_t y) const
{
   _constrain(x, y);
   return _storage[_offset(x, y)];
}

template<typename ElementType>
inline typename Cartograph<ElementType>::reference Cartograph<ElementType>::at(
   int32_t x, int32_t y)
{
   _constrain(x, y);
   return _storage[_offset(x, y)];
}

template<typename ElementType>
inline void Cartograph<ElementType>::_constrain(
   int32_t& x, int32_t& y) const
{
   if (x < _bounds.x)
      x = _bounds.x;
   else if (x >= _bounds.x + _bounds.width)
      x = _bounds.x + _bounds.width - 1;

   if (y < _bounds.y)
      y = _bounds.y;
   else if (y >= _bounds.y + _bounds.height)
      y = _bounds.y + _bounds.height - 1;
}

template<typename ElementType>
inline size_t Cartograph<ElementType>::_offset(
   int32_t x, int32_t y) const
{
   if (!inRange(x,y))
   {
      throw std::logic_error("offset is not in range!");
   }

   const int32_t offset = (y - _bounds.y) * _bounds.width + (x - _bounds.x);

//#ifdef SQUIDGE_DEBUG_ASSERTIONS
   if (offset > _storage.size() || offset < 0)
   {
      std::cout << "got offset " << offset << " for " << Point(x,y) << " in " << _bounds << std::endl;
      throw std::logic_error("Cartograph::_offset computed something bogus!");
   }
//#endif

   return offset;
}

} // namespace squidge
