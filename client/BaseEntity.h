#pragma once

#include "common/Vector2.h"
#include "client/Edict.h"
#include <boost/shared_ptr.hpp>

namespace squidge {
namespace client {

class BaseEntity;

typedef boost::shared_ptr<BaseEntity> BaseEntityPtr;

class BaseEntity : public Edict
{
protected:
   BaseEntity(
      const std::string& classname,
      const Vector2& origin,
      const Vector2& mins,
      const Vector2& maxs);

public:
   Vector2 origin;

   // These form the bounding box, without rotation.
   Vector2 mins;
   Vector2 maxs;
};


} // namespace client
} // namespace squidge
