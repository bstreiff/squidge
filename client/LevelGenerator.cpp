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
   level.resize(width, height);

   boost::random::random_device rng;

   // For now, let's use a simple algorithm for map generation...
   // create a height map, then average it out...
   std::vector<double> heightMap;
   // Make this a bit larger to make the smoothing logic easier later.
   heightMap.resize(width + 4);
   for (uint32_t i = 0; i < width + 4; ++i)
   {
      heightMap[i] = (static_cast<double>(rng())/rng.max()) * (static_cast<double>(height)/2);
   }

   std::vector<double> smoothedHeightMap;
   smoothedHeightMap.resize(width);
   // now smooth it out
   for (uint32_t i = 0; i < width; ++i)
   {
      smoothedHeightMap[i] = (
         heightMap[i] +
         heightMap[i+1] +
         heightMap[i+2] +
         heightMap[i+3] +
         heightMap[i+4]) / 5.0f;
   }


   // now fill in.
   for (uint32_t y = 0; y < height; ++y)
   {
      for (uint32_t x = 0; x < width; ++x)
      {
         if (smoothedHeightMap[x] < y)
         {
            level.setTileAtWithoutComputingFrame(Level::Foreground, x, y, Tile(TileType::Dirt));
         }
         else
         {
            level.setTileAtWithoutComputingFrame(Level::Foreground, x, y, Tile(TileType::Air));
         }
      }
   }

   // Add a box made out of bricks!
   uint32_t boxWidth     = rng()%(width/2);
   if (boxWidth < 3) boxWidth = 3;
   uint32_t boxHeight    = rng()%(height/2);
   if (boxHeight < 3) boxHeight = 3;
   uint32_t boxPositionX = rng()%(width/2);
   uint32_t boxPositionY = rng()%(height/2);

   // top and bottom
   for (uint32_t i = boxPositionX; i <= boxPositionX + boxWidth; ++i)
   {
      level.setTileAtWithoutComputingFrame(Level::Foreground, i, boxPositionY, TileType::Brick);
      level.setTileAtWithoutComputingFrame(Level::Foreground, i, boxPositionY+boxHeight, TileType::Brick);
   }
   // left and right
   for (uint32_t i = boxPositionY; i <= boxPositionY + boxHeight; ++i)
   {
      level.setTileAtWithoutComputingFrame(Level::Foreground, boxPositionX, i, TileType::Brick);
      level.setTileAtWithoutComputingFrame(Level::Foreground, boxPositionX+boxWidth, i, TileType::Brick);
   }
   // background
   for (uint32_t y = boxPositionY + 1; y <= boxPositionY + boxHeight - 1; ++y)
   {
      for (uint32_t x = boxPositionX + 1; x <= boxPositionX + boxWidth - 1; ++x)
      {
         level.setTileAtWithoutComputingFrame(Level::Background, x, y, TileType::Brick);
      }
   }

   // We're done setting stuff, so prettify it all up.
   level.recomputeAllFrames();
}

} // namespace client
} // namespace squidge
