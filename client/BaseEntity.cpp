#include "client/BaseEntity.h"

namespace squidge {
namespace client {

BaseEntity::BaseEntity(
   const std::string& classname,
   const Vector2& originx,
   const Vector2& minsx,
   const Vector2& maxsx) :
   Edict(classname),
   origin(originx),
   mins(minsx),
   maxs(maxsx)
{ }

} // namespace client
} // namespace squidge
