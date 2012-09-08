#include "client/sdl/Initializer.h"
#include <SDL.h>
#include <SDL_image.h>

namespace squidge {
namespace client {
namespace SDL {

Initializer::Initializer(uint32_t flags) :
   _sdlWasInited(false),
   _sdlImageWasInited(false)
{
   if (SDL_Init(flags) == 0)
   {
      _sdlWasInited = true;
   }

   if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) == IMG_INIT_PNG)
   {
      _sdlImageWasInited = true;
   }
}

Initializer::~Initializer()
{
   if (_sdlImageWasInited)
   {
      IMG_Quit();
   }

   if (_sdlWasInited)
   {
      SDL_Quit();
   }
}

} // namespace SDL
} // namespace client
} // namespace squidge
