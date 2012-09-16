#include "client/graphics/Texture.h"
#include <stdio.h>
#include <SDL_image.h>
#include <SDL_opengl.h>
#include "client/sdl/SurfaceAutoLock.h"

namespace squidge {
namespace client {

Texture::Texture(const boost::filesystem::path& filename) :
   _textureID(0),
   _width(0),
   _height(0)
{
   SDL_Surface *surface = IMG_Load(filename.string().c_str());
   if (!surface)
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
      SDL::SurfaceAutoLock autoLock(surface);
      glTexImage2D(
         GL_TEXTURE_2D,
         0, // level-of-detail number
         GL_RGBA, // internal format
         surface->w,
         surface->h,
         0, // border width
         GL_BGRA, // pixel data format
         GL_UNSIGNED_BYTE,
         surface->pixels);
      _width = surface->w;
      _height = surface->h;
   }

   _textureID = newTexture;

   // I think it may actually be safe to get rid of the SDL_Surface
   // at this point...
   SDL_FreeSurface(surface);
}

Texture::~Texture()
{
   if (_textureID > 0)
   {
      glDeleteTextures(1, &_textureID);
      _textureID = 0;
      _width = 0;
      _height = 0;
   }
}

} // namespace client
} // namespace squidge
