#pragma once

#include <vector>
#include <stdint.h>
#include "client/SpriteBatch.h"
#include "client/Tile.h"

namespace squidge {
namespace client {

class Level
{
public:
   Level();
   ~Level();

   void resize(uint32_t width, uint32_t height);

   uint32_t computeFrame(uint32_t x, uint32_t y);
   uint32_t computeDirtFrame(uint32_t x, uint32_t y);

   inline Tile tileAt(uint32_t x, uint32_t y) const { return _foreground[_getOffset(x,y)]; }
   void setTileAt(uint32_t x, uint32_t y, Tile tile);

   // Level generators should be using this...
   void setTileAtWithoutComputingFrame(uint32_t x, uint32_t y, Tile tile);
   void recomputeAllFrames();

   void draw(SpriteBatch& spriteBatch);

private:
   size_t _getOffset(uint32_t x, uint32_t y) const
   {
      return y*_width + x;
   }

   uint32_t _width;
   uint32_t _height;
   boost::shared_ptr<Texture> _dirtTexture;
   boost::shared_ptr<Texture> _brickTexture;

   std::vector<Tile> _foreground;
   std::vector<Tile> _background;

};

} // namespace client
} // namespace squidge
