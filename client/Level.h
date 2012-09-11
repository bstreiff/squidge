#pragma once

#include <boost/array.hpp>
#include <vector>
#include <stdint.h>
#include "client/SpriteBatch.h"
#include "client/Tile.h"
#include "common/Cartograph.h"
#include "common/Rectangle.h"

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

   void resize(const Rectangle& bounds);

   void recomputeTerrainFrame(Layer layer, int32_t x, int32_t y);
   void recomputeBackgroundTerrainFrame(Layer layer, int32_t x, int32_t y);

   // get the tile at a particular x,y location. if you specify an x,y off the map,
   // bad things will happen.
   inline const Tile& tileAt(Layer layer, int32_t x, int32_t y) const;
   inline Tile& tileAt(Layer layer, int32_t x, int32_t y);

   // set tile at a location
   void setTileAt(Layer layer, int32_t x, int32_t y, const Tile& tile);

   // Level generators should be using this...
   void setTileAtWithoutComputingFrame(Layer layer, int32_t x, int32_t y, const Tile& tile);
   void recomputeAllFrames();

   void draw(SpriteBatch& spriteBatch);

private:
   boost::shared_ptr<Texture> _dirtTexture;
   boost::shared_ptr<Texture> _brickTexture;
   boost::shared_ptr<Texture> _dirtWallTexture;
   boost::shared_ptr<Texture> _brickWallTexture;

   boost::array< Cartograph<Tile>, LayerCount > _tiles;
};

inline const Tile& Level::tileAt(Level::Layer layer, int32_t x, int32_t y) const
{
   return _tiles[layer](x,y);
}

inline Tile& Level::tileAt(Level::Layer layer, int32_t x, int32_t y)
{
   return _tiles[layer](x,y);
}

} // namespace client
} // namespace squidge
