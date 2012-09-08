#include "client/Level.h"
#include <boost/random/random_device.hpp>

namespace squidge {
namespace client {

Level::Level() :
   _width(0),
   _height(0),
   _foreground(),
   _background()
{
   // TODO: There should be some texture manager that gives us shared pointers to texture objects.
   // TODO: this should also not load stuff out of an absolute path!
   _brickTexture = boost::shared_ptr<Texture>(new Texture("/Users/brandon/Desktop/squidge/resources/bricks.png"));
   _dirtTexture = boost::shared_ptr<Texture>(new Texture("/Users/brandon/Desktop/squidge/resources/dirt.png"));
}

Level::~Level()
{
}

void Level::resize(uint32_t width, uint32_t height)
{
   _foreground.resize(width*height);
   _background.resize(width*height);
   _width = width;
   _height = height;
}

void Level::setTileAt(uint32_t x, uint32_t y, Tile tile)
{
   // tile will be coming in without subtype... we need to compute the correct frame.
   
   //_getOffset(x,y);
}

void Level::setTileAtWithoutComputingFrame(uint32_t x, uint32_t y, Tile tile)
{
   // tile will be coming in without subtype... we need to compute the correct frame.
   
   _foreground[_getOffset(x,y)] = tile;
}

void Level::recomputeAllFrames()
{
   boost::random::random_device rng;

   for (uint32_t y = 0; y < _height; ++y)
   {
      for (uint32_t x = 0; x < _width; ++x)
      {
         Tile& tile = _foreground[_getOffset(x,y)];
         uint32_t frame;

         if (tile.type == TileType::Air)
         {
            // do nothing.
            continue;
         }
         else if (tile.type == TileType::Dirt)
         {
            frame = computeDirtFrame(x, y);
         }
         else if (tile.type == TileType::Brick)
         {
            frame = computeDirtFrame(x, y);
         }

         // generate a random instance of this frame so
         // that the level looks a little more interesting.
         uint32_t randomInstance = rand()%4;
         tile.framex = static_cast<uint8_t>(frame);
         tile.framey = static_cast<uint8_t>(randomInstance);
      }
   }

}

uint32_t Level::computeFrame(uint32_t x, uint32_t y)
{
   if (_foreground[y*_width + x].type == TileType::Dirt)
   {
      return computeDirtFrame(x, y);
   }
   return static_cast<uint32_t>(~0UL);
}

// then here we only deal with brick either adjacent to brick or adjacent to nothing.
// there are only sixteen possibilities in that case...
//
// ...  .b.  ...  ...  ...  .b.  ...  bbb  ...  bb. .bb  ...  ...  .bb  bb.  bbb
// .b.  .b.  .b.  bb.  .bb  .b.  bbb  bbb  bbb  bb. .bb  .bb  bb.  .bb  bb.  bbb
// ...  ...  .b.  ...  ...  .b.  ...  ...  bbb  bb. .bb  .bb  bb.  ...  ...  bbb
//
// for overlaid dirt, there are nineteen (inverse of everything above except last, plus 4 corners)
// ddd  d.d  ddd  ddd  ddd  d.d  ddd  ...  ddd  ..d d..  ddd  ddd  d..  ..d  ...  ...  ..d  d..
// d.d  d.d  d.d  ..d  d..  d.d  ...  ...  ...  ..d d..  d..  ..d  d..  ..d  ...  ...  ...  ...
// ddd  ddd  d.d  ddd  ddd  d.d  ddd  ddd  ...  ..d d..  d..  ..d  ddd  ddd  ..d  d..  ...  ...
//
// TODO: I actually forgot a couple cases above (T intersections and inside corners... need
// to fix the textures up for those.)

uint32_t Level::computeDirtFrame(uint32_t x, uint32_t y)
{
   Tile::Type utype, dtype, ltype, rtype;
   const Tile& thisTile = tileAt(x, y);

   // Get the tiles that are u/d/l/r of us, taking care about edges of map
   utype = (y == 0           ? thisTile.type : tileAt(x, y-1).type);
   dtype = (y == (_height-1) ? thisTile.type : tileAt(x, y+1).type);
   ltype = (x == 0           ? thisTile.type : tileAt(x-1, y).type);
   rtype = (x == (_width-1)  ? thisTile.type : tileAt(x+1, y).type);

   // Now pack all of the information into a single byte.
   uint8_t compareMask = (((utype == thisTile.type) ? 0x8 : 0x0) |
                          ((dtype == thisTile.type) ? 0x4 : 0x0) |
                          ((ltype == thisTile.type) ? 0x2 : 0x0) |
                          ((rtype == thisTile.type) ? 0x1 : 0x0));

   // Now translate the adjacency mask into a frame for the texture.
   // (should I rearrange the texture to make this better?)
   //
   // ...  .b.  ...  ...  ...  .b.  ...  bbb  ...  bb.  .bb  ...  ...  .bb  bb.  bbb
   // .b.  .b.  .b.  bb.  .bb  .b.  bbb  bbb  bbb  bb.  .bb  .bb  bb.  .bb  bb.  bbb
   // ...  ...  .b.  ...  ...  .b.  ...  ...  bbb  bb.  .bb  .bb  bb.  ...  ...  bbb
   //  0    1    2    3    4    5    6    7    8    9    10   11  12   13   14   15
   // 
   // ____ u___ _d__ __l_ ___r ud__ __lr u_lr _dlr udl_ ud_r _d_r _dl_ u__r u_l_ udlr
   // 0000 1000 0100 0010 0001 1100 0011 1011 0111 1110 1101 0101 0110 1001 1010 1111
   //  0    8    4    2    1    C    3    B    7    E    D    5    6    9    A    F
   //
   static const uint32_t textureMap[] = { 0, 4, 3, 6, 2, 11, 12, 8, 1, 13, 14, 7, 5, 10, 9, 15 };
   return textureMap[compareMask];
}

void Level::draw(SpriteBatch& spriteBatch)
{
   for (uint32_t y = 0; y < _height; ++y)
   {
      for (uint32_t x = 0; x < _width; ++x)
      {
         const Tile& tile = tileAt(x, y);
         if (tile.type == TileType::Air)
         {
            // do nothing.
         }
         else if (tile.type == TileType::Dirt)
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

} // namespace client
} // namespace squidge
