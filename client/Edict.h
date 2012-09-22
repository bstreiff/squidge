#pragma once

#include "common/Vector2.h"
#include "client/graphics/SpriteBatch.h"
#include <boost/shared_ptr.hpp>
#include <string>

namespace squidge {
namespace client {

class Edict;

typedef boost::shared_ptr<Edict> EdictPtr;

class Edict
{
protected:
   Edict(const std::string& classname);
public:
   virtual ~Edict();

   typedef EdictPtr (*EdictConstruct)();

   virtual EdictPtr construct() = 0;
   const std::string& classname() const;

   virtual void draw(SpriteBatch& spriteBatch) const;

   virtual void think();
   virtual void blocked(EdictPtr other);
   virtual void touch(EdictPtr other);
   virtual void use(EdictPtr other, EdictPtr activator);
   virtual void pain(EdictPtr other, int32_t damage);
   virtual void die(EdictPtr inflictor, EdictPtr attacker, int32_t damage);

private:
   const std::string _classname;
};


} // namespace client
} // namespace squidge
