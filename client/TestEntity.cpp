#include "client/TestEntity.h"
#include "client/ResourceManager.h"

namespace squidge {
namespace client {

TestEntity::TestEntity() :
   BaseEntity(
      "TestEntity",
      Vector2( 0,  0),
      Vector2(-6, -6),
      Vector2( 6,  6))
{
   _potionTexture = ResourceManager::get().getTexture("potions.png");
}

TestEntity::TestEntity(const Vector2 origin, int color) :
   BaseEntity(
      "TestEntity",
      origin,
      Vector2(-6, -6),
      Vector2( 6,  6)),
   _color(color)
{
   _potionTexture = ResourceManager::get().getTexture("potions.png");
}

EdictPtr TestEntity::construct()
{
   // this entry point is intended to be called from a dynamic broker
   // that only knows the classname... the idea is to use it for creating
   // an entity given some data... maybe we need to pass in a reference
   // to that data somehow (some sort of deserialization engine?)
   //
   // If that's the case, then:
   //   do we want to use the no-arg ctor for this? I don't think so.
   return EdictPtr(new TestEntity);
}

void TestEntity::draw(SpriteBatch& sb) const
{
   sb.draw(
      _potionTexture,
      Rectangle(_color*12, 0, 12, 12),
      Rectangle(origin.x*24 - 6, origin.y*24 - 6, 24, 24));
}

} // namespace client
} // namespace squidge
