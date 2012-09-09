#pragma once

#include <boost/array.hpp>
#include <vector>
#include <stdint.h>
#include "client/SpriteBatch.h"
#include "client/Tile.h"

namespace squidge {
namespace client {

class Level
{
public:
   enum Layer
   {
      Background = 0,
      Foreground = 1,
      LayerCount = 2
   };

   Level();
   ~Level();

   void resize(uint32_t width, uint32_t height);

   void recomputeTerrainFrame(Layer layer, uint32_t x, uint32_t y);
   void recomputeBackgroundTerrainFrame(Layer layer, uint32_t x, uint32_t y);

   // get the tile at a particular x,y location. if you specify an x,y off the map,
   // bad things will happen.
   inline const Tile& tileAt(Layer layer, uint32_t x, uint32_t y) const;
   inline Tile& tileAt(Layer layer, uint32_t x, uint32_t y);

   // get the tile at a particular x,y location. if you specify an x,y off the map,
   // the coordinates will be clamped to give you the tile at that edge.
   const Tile& tileAtClamped(Layer layer, int32_t x, int32_t y) const;

   // set tile at a location
   void setTileAt(Layer layer, uint32_t x, uint32_t y, const Tile& tile);

   // Level generators should be using this...
   void setTileAtWithoutComputingFrame(Layer layer, uint32_t x, uint32_t y, const Tile& tile);
   void recomputeAllFrames();

   void draw(SpriteBatch& spriteBatch);

private:
   size_t _getOffset(uint32_t x, uint32_t y) const;

   uint32_t _width;
   uint32_t _height;
   boost::shared_ptr<Texture> _dirtTexture;
   boost::shared_ptr<Texture> _brickTexture;
   boost::shared_ptr<Texture> _dirtWallTexture;
   boost::shared_ptr<Texture> _brickWallTexture;

   boost::array< std::vector<Tile>, LayerCount > _tiles;
};

inline const Tile& Level::tileAt(Level::Layer layer, uint32_t x, uint32_t y) const
{
   return _tiles[layer][_getOffset(x,y)];
}

inline Tile& Level::tileAt(Level::Layer layer, uint32_t x, uint32_t y)
{
   return _tiles[layer][_getOffset(x,y)];
}

inline size_t Level::_getOffset(uint32_t x, uint32_t y) const
{
   return y*_width + x;
}


} // namespace client
} // namespace squidge
