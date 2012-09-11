// A cartograph is essentially a two-dimensional std::vector, with coordinate
// translation. Woo.
//
// It's 'cartograph' instead of some name akin to 'vector' because we already
// use 'vector' for things like Vector2f (a two-element (x,y) vector). Sigh.
//
// The coordinate system looks like the following:
//
//                             (-y, 0)
//      topLeft                   |
//            +-------------------|-------------------+
//            |                   |                   |
//            |                   |                   |
//            |                   |                   |
//            |                   |                   |
//            |                   |                   |
//  (0, -x) ----------------------0---------------------- (0,  x)
//            |                   |                   |
//            |                   |                   |
//            |                   |                   |
//            |                   |                   |
//            |                   |                   |
//            +-------------------|-------------------+
//                                |                  bottomRight
//                             ( y, 0)

#pragma once

#include "common/Vector2.h"
#include "common/Rectangle.h"
#include "common/PointIterator.h"
#include <boost/iterator/iterator_facade.hpp>

namespace squidge {

template<typename ElementType>
class Cartograph
{
public:

   template<typename ET>
   class CartographIterator : public boost::iterator_facade<
      CartographIterator<ET>, ET, std::bidirectional_iterator_tag >
   {
   public:
      CartographIterator(
         Cartograph<ElementType>* parent,
         Point pos) :
         _parent(parent),
         _pointItr(parent->_bounds, pos)
      { }

      const Point& position()
      {
         return *_pointItr;
      }

   private:
      friend class boost::iterator_core_access;

      Cartograph<ET>* _parent;
      PointIterator _pointItr;

      void increment()
      {
         _pointItr++;
      }

      void decrement()
      {
         _pointItr--;
      }

      bool equal(const CartographIterator& other) const
      {
         return _pointItr == other._pointItr;
      }

      ET& dereference() const
      {
         return (*_parent)(_pointItr->x, _pointItr->y);
      }
   };

   typedef const ElementType& const_reference;
   typedef ElementType& reference;
   typedef CartographIterator<ElementType> iterator;

   inline Cartograph();
   inline Cartograph(const Rectangle& bounds, ElementType value = ElementType());
   inline Cartograph(const Cartograph& other);

   inline Cartograph& operator=(const Cartograph& other);

   inline bool operator==(const Cartograph& other) const;

   inline void resize(const Rectangle& bounds, ElementType value = ElementType());
   inline void clear();

   inline iterator begin();
   inline iterator end();

   inline const Rectangle& bounds() const;
   inline int32_t height() const;
   inline int32_t width() const;

   inline bool inRange(int32_t x, int32_t y) const;
   inline bool inRange(const Point& xy) const;

   inline const_reference operator()(int32_t x, int32_t y) const;
   inline reference operator()(int32_t x, int32_t y);

   // Get (x,y), performing bounds-checking.
   // Note that unlike std::vector, we do not throw out_of_range: we return the element
   // that is at the nearest edge.
   inline const_reference at(int32_t x, int32_t y) const;
   inline reference at(int32_t x, int32_t y);

private:
   inline void _constrain(int32_t& x, int32_t& y) const;
   inline size_t _offset(int32_t x, int32_t y) const;

   std::vector<ElementType> _storage;
   Rectangle _bounds;
};

} // namespace squidge

#include "common/Cartograph.ipp"
