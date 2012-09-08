#pragma once

#include <boost/utility.hpp>
#include <boost/shared_ptr.hpp>
#include <SDL.h>
#include <SDL_opengl.h>
#include <string>

namespace squidge {
namespace client {

class Texture : boost::noncopyable
{
public:
   Texture(const std::string& filename);
   ~Texture();

   inline GLuint getTextureID() const
   {
      return _textureID;
   }

   inline size_t getWidth() const
   {
      return _width;
   }

   inline size_t getHeight() const
   {
      return _height;
   }

private:
   GLuint _textureID;
   size_t _width;
   size_t _height;
   SDL_Surface* _surface;
};

} // namespace client
} // namespace squidge
