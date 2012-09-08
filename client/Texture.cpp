#include "client/Texture.h"
#include <stdio.h>
#include <SDL_image.h>
#include <SDL_opengl.h>
#include "client/sdl/SurfaceAutoLock.h"

namespace squidge {
namespace client {

Texture::Texture(const std::string& filename) :
   _textureID(0),
   _width(0),
   _height(0),
   _surface(NULL)
{
   _surface = IMG_Load(filename.c_str());
   if (!_surface)
   {
      printf("faaaaaail\n");
      // throw?
      return;
   }

   GLuint newTexture = 0;
   glGenTextures(1, &newTexture);
   if (newTexture == 0)
   {
      printf("faaaaaaaaaaaaail\n");
      return;
   }

   glBindTexture(GL_TEXTURE_2D, newTexture);

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

   {
      SDL::SurfaceAutoLock autoLock(_surface);
      glTexImage2D(
         GL_TEXTURE_2D,
         0, // level-of-detail number
         GL_RGBA, // internal format
         _surface->w,
         _surface->h,
         0, // border width
         GL_BGRA, // pixel data format
         GL_UNSIGNED_BYTE,
         _surface->pixels);
      _width = _surface->w;
      _height = _surface->h;
   }

   _textureID = newTexture;

   // I think it may actually be safe to get rid of the SDL_Surface
   // at this point...
}

Texture::~Texture()
{
   if (_textureID > 0)
   {
      glDeleteTextures(1, &_textureID);
      SDL_FreeSurface(_surface);
      _surface = NULL;
      _textureID = 0;
      _width = 0;
      _height = 0;
   }
}

} // namespace client
} // namespace squidge
