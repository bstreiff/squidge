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

   // get the tile at a particular x,y location. if you specify an x,y off the map,
   // bad things will happen.
   inline const Tile& tileAt(uint32_t x, uint32_t y) const;
   inline Tile& tileAt(uint32_t x, uint32_t y);

   // get the tile at a particular x,y location. if you specify an x,y off the map,
   // the coordinates will be clamped to give you the tile at that edge.
   const Tile& tileAtClamped(int32_t x, int32_t y) const;

   // set tile at a location
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

inline const Tile& Level::tileAt(uint32_t x, uint32_t y) const
{
   return _foreground[_getOffset(x,y)];
}

inline Tile& Level::tileAt(uint32_t x, uint32_t y)
{
   return _foreground[_getOffset(x,y)];
}


} // namespace client
} // namespace squidge
