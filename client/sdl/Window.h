#pragma once

#include <stdint.h>
#include <SDL.h>
#include <boost/utility.hpp>

namespace squidge {
namespace client {
namespace SDL {

class Window : boost::noncopyable
{
public:
   Window(uint32_t width, uint32_t height);
   ~Window();

   void resize(uint32_t width, uint32_t height);

   SDL_Surface* getSurface();
   uint32_t getWidth();
   uint32_t getHeight();

private:
   SDL_Surface* _windowSurface;
   uint32_t _width;
   uint32_t _height;
};


} // namespace SDL
} // namespace client
} // namespace squidge
