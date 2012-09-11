#include "client/LevelGenerator.h"
#include <boost/random/random_device.hpp>

namespace squidge {
namespace client {

LevelGenerator::LevelGenerator()
{
}

LevelGenerator::~LevelGenerator()
{
}

void LevelGenerator::generate(
   uint32_t width,
   uint32_t height,
   Level& level)
{
   Rectangle bounds(-(width / 2), -(height / 2), width, height);
   level.resize(bounds);

   boost::random::random_device rng;

   for (int32_t y = bounds.y; y < bounds.y + bounds.height; ++y)
   {
      for (int32_t x = bounds.x; x < bounds.x + bounds.width; ++x)
      {
         if (y > 0)
         {
            level.setTileAtWithoutComputingFrame(Level::Foreground, x, y, Tile(TileType::Dirt));
         }
         else
         {
            level.setTileAtWithoutComputingFrame(Level::Foreground, x, y, Tile(TileType::Air));
         }
      }
   }

   level.setTileAtWithoutComputingFrame(Level::Foreground, 0, -2, Tile(TileType::Brick));
   level.setTileAtWithoutComputingFrame(Level::Foreground, 0, -1, Tile(TileType::Brick));
   level.setTileAtWithoutComputingFrame(Level::Foreground, 0,  0, Tile(TileType::Brick));
   level.setTileAtWithoutComputingFrame(Level::Foreground, 0,  1, Tile(TileType::Brick));
   level.setTileAtWithoutComputingFrame(Level::Foreground, 0,  2, Tile(TileType::Brick));
   level.setTileAtWithoutComputingFrame(Level::Foreground,-2,  0, Tile(TileType::Brick));
   level.setTileAtWithoutComputingFrame(Level::Foreground,-1,  0, Tile(TileType::Brick));
   level.setTileAtWithoutComputingFrame(Level::Foreground, 1,  0, Tile(TileType::Brick));
   level.setTileAtWithoutComputingFrame(Level::Foreground, 2,  0, Tile(TileType::Brick));

   // We're done setting stuff, so prettify it all up.
   level.recomputeAllFrames();
}

} // namespace client
} // namespace squidge
