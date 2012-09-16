#pragma once

#include <stdint.h>

namespace squidge {

class Vector3;
class Vector4;

class Color
{
public:
   Color();
   Color(uint8_t r, uint8_t g, uint8_t b);
   Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
   Color(float r, float g, float b);
   Color(float r, float g, float b, float a);
   explicit Color(const Vector3& rgb);
   explicit Color(const Vector4& rgba);
   Color(const Color& other);
   Color& operator=(const Color& other);

public:
   uint8_t r;
   uint8_t g;
   uint8_t b;
   uint8_t a;
};

bool operator==(const Color& a, const Color& b);
bool operator!=(const Color& a, const Color& b);

} // namespace
