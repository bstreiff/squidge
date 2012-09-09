#include "client/Level.h"
#include "client/ResourceManager.h"
#include <boost/random/random_device.hpp>

namespace squidge {
namespace client {

Level::Level() :
   _width(0),
   _height(0)
{
   _brickTexture = ResourceManager::get().getTexture("bricks.png");
   _dirtTexture = ResourceManager::get().getTexture("dirt.png");
   _brickWallTexture = ResourceManager::get().getTexture("brick_wall.png");
   _dirtWallTexture = ResourceManager::get().getTexture("dirt_wall.png");
}

Level::~Level()
{
}

void Level::resize(uint32_t width, uint32_t height)
{
   for (size_t i = 0; i < LayerCount; ++i)
   {
      _tiles[i].resize(width*height);
   }

   _width = width;
   _height = height;
}

void Level::setTileAt(Level::Layer layer, uint32_t x, uint32_t y, const Tile& tile)
{
   // tile will be coming in without subtype... we need to compute the correct frame.
   setTileAtWithoutComputingFrame(layer, x, y, tile);
   recomputeTerrainFrame(layer, x, y);
}

void Level::setTileAtWithoutComputingFrame(Level::Layer layer, uint32_t x, uint32_t y, const Tile& tile)
{   
   _tiles[layer][_getOffset(x,y)] = tile;
}

void Level::recomputeAllFrames()
{
   boost::random::random_device rng;

   for (uint32_t y = 0; y < _height; ++y)
   {
      for (uint32_t x = 0; x < _width; ++x)
      {
         for (size_t layer = 0; layer < LayerCount; ++layer)
         {
            const Tile& tile = tileAt(static_cast<Layer>(layer), x, y);

            if (tile.type == TileType::Air)
            {
               // do nothing.
               continue;
            }
            else if (tile.type == TileType::Dirt ||
                     tile.type == TileType::Brick)
            {
               if (layer == Background)
               {
                  recomputeBackgroundTerrainFrame(static_cast<Layer>(layer), x, y);
               }
               else if (layer == Foreground)
               {
                  recomputeTerrainFrame(static_cast<Layer>(layer), x, y);
               }
            }
         }
      }
   }

}

void Level::recomputeTerrainFrame(Level::Layer layer, uint32_t x, uint32_t y)
{
   Tile& tile = tileAt(layer, x, y);
   const Tile::Type thisType = tile.type;

   // Get the tiles that are u/d/l/r of us, taking care about edges of map
   const Tile::Type uType = tileAtClamped(layer, x, y-1).type;
   const Tile::Type dType = tileAtClamped(layer, x, y+1).type;
   const Tile::Type lType = tileAtClamped(layer, x-1, y).type;
   const Tile::Type rType = tileAtClamped(layer, x+1, y).type;

   uint8_t frame;

   // Now pack all of the information into a single byte.
   uint8_t sideCompareMask = (((uType == thisType) ? 0x8 : 0x0) |
                              ((dType == thisType) ? 0x4 : 0x0) |
                              ((lType == thisType) ? 0x2 : 0x0) |
                              ((rType == thisType) ? 0x1 : 0x0));

   // Conveniently, for all but 1111 the mask above is the same as the frame number.
   //
   // ( 0) ( 1) ( 2) ( 3) ( 4) ( 5) ( 6) ( 7) ( 8) ( 9) (10) (11) (12) (13) (14) (30)
   //  .    .    .    .    .    .    .    .    b    b    b    b    b    b    b    b
   // .b.  .bb  bb.  bbb  .b.  .bb  bb.  bbb  .b.  .bb  bb.  bbb  .b.  .bb  bb.  bbb
   //  .    .    .    .    b    b    b    b    .    .    .    .    b    b    b    b
   //
   // ____ ___r __l_ __lr _d__ _d_r _dl_ _dlr u___ u__r u_l_ u_lr ud__ ud_r udl_ udlr 
   // 0000 0001 0010 0011 0100 0101 0110 0111 1000 1001 1010 1011 1100 1101 1110 1111

   if (sideCompareMask < 0xF)
   {
      frame = sideCompareMask;
   }
   else
   {
      // We treat the case where we have the same type u/d/l/r of us specially. When
      // we do this we start looking at what's ul/dl/dr/ur of us, so that we can have
      // better textures for the corners.

      const Tile::Type ulType = tileAtClamped(layer, x-1, y-1).type;
      const Tile::Type dlType = tileAtClamped(layer, x-1, y+1).type;
      const Tile::Type drType = tileAtClamped(layer, x+1, y+1).type;
      const Tile::Type urType = tileAtClamped(layer, x+1, y-1).type;

      uint8_t cornerCompareMask = (((ulType == thisType) ? 0x8 : 0x0) |
                                   ((dlType == thisType) ? 0x4 : 0x0) |
                                   ((drType == thisType) ? 0x2 : 0x0) |
                                   ((urType == thisType) ? 0x1 : 0x0));

      // Now translate this into a frame number. Basically, we just add fifteen.
      //
      // (15) (16) (17) (18) (19) (20) (21) (22) (23) (24) (25) (26) (27) (28) (29) (30)
      // .b.  .bb  .b.  .bb  .b.  .bb  .b.  .bb  bb.  bbb  bb.  bbb  bb.  bbb  bb.  bbb
      // bbb  bbb  bbb  bbb  bbb  bbb  bbb  bbb  bbb  bbb  bbb  bbb  bbb  bbb  bbb  bbb
      // .b.  .b.  .bb  .bb  bb.  bb.  bbb  bbb  .b.  .b.  .bb  .bb  bb.  bb.  bbb  bbb
      //
      //         u   d    du  d    d u  dd   ddu u    u  u u d  u du ud   ud u udd  uddu
      // ____ ___r __r_ __rr _l__ _l_r _lr_ _lrr l___ l__r l_r_ l_rr ll__ ll_r llr_ llrr
      // 0000 0001 0010 0011 0100 0101 0110 0111 1000 1001 1010 1011 1100 1101 1110 1111

      frame = 15 + cornerCompareMask;
   }

   // generate a random instance of this frame so
   // that the level looks a little more interesting.
   boost::random::random_device rng;
   const uint32_t randomInstance = rng()%4;
   tile.framex = static_cast<uint8_t>(frame);
   tile.framey = static_cast<uint8_t>(randomInstance);
}

void Level::recomputeBackgroundTerrainFrame(Level::Layer layer, uint32_t x, uint32_t y)
{
   Tile& tile = tileAt(layer, x, y);
   const Tile::Type thisType = tile.type;

   // Get the tiles that are u/d/l/r of us, taking care about edges of map
   const Tile::Type uType = tileAtClamped(layer, x, y-1).type;
   const Tile::Type dType = tileAtClamped(layer, x, y+1).type;
   const Tile::Type lType = tileAtClamped(layer, x-1, y).type;
   const Tile::Type rType = tileAtClamped(layer, x+1, y).type;

   uint8_t frame;

   // Now pack all of the information into a single byte.
   uint8_t sideCompareMask = (((uType == thisType) ? 0x8 : 0x0) |
                              ((dType == thisType) ? 0x4 : 0x0) |
                              ((lType == thisType) ? 0x2 : 0x0) |
                              ((rType == thisType) ? 0x1 : 0x0));

   // ( 0) ( 1) ( 2) ( 3) ( 4) ( 5) ( 6) ( 7) ( 8) ( 9) (10) (11) (12) (13) (14) (15)
   //  .    .    .    .    .    .    .    .    b    b    b    b    b    b    b    b
   // .b.  .bb  bb.  bbb  .b.  .bb  bb.  bbb  .b.  .bb  bb.  bbb  .b.  .bb  bb.  bbb
   //  .    .    .    .    b    b    b    b    .    .    .    .    b    b    b    b
   //
   // ____ ___r __l_ __lr _d__ _d_r _dl_ _dlr u___ u__r u_l_ u_lr ud__ ud_r udl_ udlr 
   // 0000 0001 0010 0011 0100 0101 0110 0111 1000 1001 1010 1011 1100 1101 1110 1111

   frame = sideCompareMask;

   // generate a random instance of this frame so
   // that the level looks a little more interesting.
   boost::random::random_device rng;
   const uint32_t randomInstance = rng()%4;
   tile.framex = static_cast<uint8_t>(frame);
   tile.framey = static_cast<uint8_t>(randomInstance);
}


void Level::draw(SpriteBatch& spriteBatch)
{
   // draw the background layer (walls)
   for (uint32_t y = 0; y < _height; ++y)
   {
      for (uint32_t x = 0; x < _width; ++x)
      {
         const Tile& tile = tileAt(Background, x, y);
         if (tile.type == TileType::Dirt)
         {
            spriteBatch.draw(
               _dirtWallTexture,
               Rectangle(tile.framex*16, tile.framey*16, 16, 16),
               Rectangle(x*16 - 8, y*16 - 8, 32, 32));
         }
         else if (tile.type == TileType::Brick)
         {
            spriteBatch.draw(
               _brickWallTexture,
               Rectangle(tile.framex*16, tile.framey*16, 16, 16),
               Rectangle(x*16 - 8, y*16 - 8, 32, 32));
         }
      }
   }

   // draw the foreground layer
   for (uint32_t y = 0; y < _height; ++y)
   {
      for (uint32_t x = 0; x < _width; ++x)
      {
         const Tile& tile = tileAt(Foreground, x, y);
         if (tile.type == TileType::Dirt)
         {
            spriteBatch.draw(
               _dirtTexture,
               Rectangle(tile.framex*8, tile.framey*8, 8, 8),
               Rectangle(x*16, y*16, 16, 16));
         }
         else if (tile.type == TileType::Brick)
         {
            spriteBatch.draw(
               _brickTexture,
               Rectangle(tile.framex*8, tile.framey*8, 8, 8),
               Rectangle(x*16, y*16, 16, 16));
         }
      }
   }
}

const Tile& Level::tileAtClamped(Level::Layer layer, int32_t x, int32_t y) const
{
   if (x < 0)
      x = 0;
   else if (x > static_cast<int32_t>(_width-1))
      x = static_cast<int32_t>(_width-1);

   if (y < 0)
      y = 0;
   else if (y > static_cast<int32_t>(_height-1))
      y = static_cast<int32_t>(_height-1);

   return tileAt(layer, static_cast<uint32_t>(x), static_cast<uint32_t>(y));
}

} // namespace client
} // namespace squidge
