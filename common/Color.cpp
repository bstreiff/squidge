#include "common/Color.h"
#include "common/Vector3.h"
#include "common/Vector4.h"

namespace squidge {

namespace {

inline uint8_t convertColorFloatToByte(float x)
{
   if (x <= 0.0f) return 0;
   else if (x >= 1.0f) return 255;
   else return static_cast<uint8_t>(x * 255.0f);
}

} // namespace

Color::Color() :
   r(0), g(0), b(0), a(0)
{ }

Color::Color(uint8_t rr, uint8_t gg, uint8_t bb) :
   r(rr), g(gg), b(bb), a(255)
{ }

Color::Color(uint8_t rr, uint8_t gg, uint8_t bb, uint8_t aa) :
   r(rr), g(gg), b(bb), a(aa)
{ }

Color::Color(float rr, float gg, float bb) :
   r(convertColorFloatToByte(rr)),
   g(convertColorFloatToByte(gg)),
   b(convertColorFloatToByte(bb)),
   a(255)
{ }

Color::Color(float rr, float gg, float bb, float aa) :
   r(convertColorFloatToByte(rr)),
   g(convertColorFloatToByte(gg)),
   b(convertColorFloatToByte(bb)),
   a(convertColorFloatToByte(aa))
{ }

Color::Color(const Vector3& rgb) :
   r(convertColorFloatToByte(rgb.x)),
   g(convertColorFloatToByte(rgb.y)),
   b(convertColorFloatToByte(rgb.z)),
   a(255)
{ }

Color::Color(const Vector4& rgba) :
   r(convertColorFloatToByte(rgb.x)),
   g(convertColorFloatToByte(rgb.y)),
   b(convertColorFloatToByte(rgb.z)),
   a(convertColorFloatToByte(rgb.w)),
{ }

Color::Color(const Color& other) :
   r(other.r),
   g(other.g),
   b(other.b),
   a(other.a)
{ }

Color& Color::operator=(const Color& other)
{
   r = other.r;
   g = other.g;
   b = other.b;
   a = other.a;

   return *this;
}

} // namespace squidge