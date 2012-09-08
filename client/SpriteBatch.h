#pragma once

#include <boost/utility.hpp>
#include <boost/shared_ptr.hpp>
#include "client/Texture.h"
#include "common/Vector2.h"
#include "common/Rectangle.h"
#include <list>

namespace squidge {
namespace client {

class SpriteBatch : boost::noncopyable
{
public:
   // Create a new sprite batch.
   // (Should this take in some sort of context object?)
   SpriteBatch();

   // Begin the drawing operation.
   void drawBegin();

   // Add a sprite to the drawing queue.
   void draw(
      boost::shared_ptr<Texture> texture,
      Rectangle sourceRect,
      Point destPoint);
   void draw(
      boost::shared_ptr<Texture> texture,
      Rectangle sourceRect,
      Rectangle destRect);

   // Flush the drawing queue, rendering all sprites.
   // The draw queue is cleared after this operation.
   void drawEnd();

private:

   struct SpriteWorkItem
   {
      boost::shared_ptr<Texture> texture;
      Rectangle sourceRect;
      Rectangle destRect;
   };

   std::list<SpriteWorkItem> _drawQueue;
   bool _hasBegun;
};

} // namespace client
} // namespace squidge
