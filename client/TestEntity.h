#pragma once

#include "client/BaseEntity.h"

namespace squidge {
namespace client {

class TestEntity : public BaseEntity
{
protected:
   TestEntity();

public:
   TestEntity(const Vector2 origin, int color);

   void draw(SpriteBatch& sb) const;

   EdictPtr construct();

private:
   boost::shared_ptr<Texture> _potionTexture;
   int _color;

};

} // namespace client
} // namespace squidge
