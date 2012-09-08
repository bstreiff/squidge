#pragma once

#include <SDL.h>
#include <boost/utility.hpp>

namespace squidge {
namespace client {
namespace SDL {

class SurfaceAutoLock : boost::noncopyable
{
public:
   inline SurfaceAutoLock(SDL_Surface* surface) :
      _surface(surface),
      _surfaceWasLocked(false)
   {
      if (SDL_MUSTLOCK(_surface))
      {
         if (SDL_LockSurface(_surface) == 0)
         {
            _surfaceWasLocked = true;
         }
      }
   }

   inline ~SurfaceAutoLock()
   {
      if (_surfaceWasLocked)
      {
         SDL_UnlockSurface(_surface);
         _surfaceWasLocked = false;
      }
   }

private:
   SDL_Surface* _surface;
   bool _surfaceWasLocked;
};

} // namespace SDL
} // namespace client
} // namespace squidge
