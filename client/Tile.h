// Tiles have a type and an associated frame (which maps to a specific 8x8 spot on
// the texture).

#include <stdint.h>

namespace squidge {
namespace client {

class Tile
{
public:
   typedef uint16_t Type;

   inline Tile();
   inline Tile(Tile::Type type);
   inline Tile(Tile::Type type, uint8_t framex, uint8_t framey);

   inline Tile(const Tile& other);
   inline Tile& operator=(const Tile& other);

   Type type;
   uint8_t  framex;
   uint8_t  framey;
};

namespace TileType
{
const Tile::Type Air   = 0;
const Tile::Type Dirt  = 1;
const Tile::Type Brick = 2;
} // namespace TileType

inline Tile::Tile() :
   type(TileType::Air),
   framex(0),
   framey(0)
{ }

inline Tile::Tile(Tile::Type tt) :
   type(tt),
   framex(0),
   framey(0)
{ }

inline Tile::Tile(Tile::Type tt, uint8_t fx, uint8_t fy) :
   type(tt),
   framex(fx),
   framey(fy)
{ }

inline Tile::Tile(const Tile& other) :
   type(other.type),
   framex(other.framex),
   framey(other.framey)
{ }

inline Tile& Tile::operator=(const Tile& other)
{
   type = other.type;
   framex = other.framex;
   framey = other.framey;
   return *this;
}


} // namespace client
} // namespace squidge
