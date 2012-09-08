#pragma once

#include <stdint.h>

namespace squidge {
namespace client {

typedef uint16_t TileType;

namespace TileType
{

const TileType Air   = 0;
const TileType Dirt  = 1;
const TileType Brick = 2;

} // namespace TileType

} // namespace squidge
} // namespace client
