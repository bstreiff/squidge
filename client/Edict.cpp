#include "client/Edict.h"

namespace squidge {
namespace client {

Edict::Edict(const std::string& classname) :
   _classname(classname)
{ }

Edict::~Edict()
{ }

const std::string& Edict::classname() const
{
   return _classname;
}

void Edict::draw(SpriteBatch& sb) const
{ }

void Edict::think()
{ }

void Edict::blocked(EdictPtr other)
{ }

void Edict::touch(EdictPtr other)
{ }

void Edict::use(EdictPtr other, EdictPtr activator)
{ }

void Edict::pain(EdictPtr other, int32_t damage)
{ }

void Edict::die(EdictPtr inflictor, EdictPtr attacker, int32_t damage)
{ }

} // namespace client
} // namespace squidge
