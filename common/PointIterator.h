// Iterators for traversing a two-dimensional region of points, bounded
// by a Rectangle.
//
// Direction of forward traversal is across x then down y (row-major).

#pragma once

#include <boost/iterator/iterator_facade.hpp>
#include "common/Point.h"
#include "common/Rectangle.h"

namespace squidge {

class PointIterator : public boost::iterator_facade<
   PointIterator, const Point, std::bidirectional_iterator_tag >
{
public:
   PointIterator() :
      rect(),
      pos()
   { }

   explicit PointIterator(
      const Rectangle& rectangle) :
      rect(rectangle),
      pos(Point(rectangle.x, rectangle.y))
   { }

   PointIterator(
      const Rectangle& rectangle,
      const Point& initialPosition) :
      rect(rectangle),
      pos(initialPosition)
   { }

   PointIterator(
      const PointIterator& other) :
      rect(other.rect),
      pos(other.pos)
   { }

   PointIterator& operator=(
      const PointIterator& other)
   {
      rect = other.rect;
      pos = other.pos;
      return *this;
   }

private:
   friend class boost::iterator_core_access;

   void increment()
   {
      pos.x++;

      if (pos.x >= rect.x + rect.width)
      {
         pos.x = rect.x;
         pos.y++;
      }
   }

   void decrement()
   {
      pos.x--;

      if (pos.x < rect.x)
      {
         pos.x = rect.x + rect.width - 1;
         pos.y--;
      }
   }

   bool equal(const PointIterator& other) const
   {
      return pos == other.pos;
   }

   const Point& dereference() const
   {
      return pos;
   }

   Rectangle rect;
   Point pos;
};

} // namespace squidge
