#include "client/sdl/Window.h"

#include <stdint.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include "common/Matrix.h"

namespace squidge {
namespace client {
namespace SDL {

Window::Window(uint32_t width, uint32_t height) :
   _windowSurface(NULL),
   _width(width),
   _height(height)
{
   resize(width, height);
}

Window::~Window()
{
   // The returned surface will be freed by SDL_Quit and must
   // not be freed by us.
}

void Window::resize(uint32_t width, uint32_t height)
{
   SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

   _windowSurface = SDL_SetVideoMode(width, height, 0, SDL_OPENGL);
   if (!_windowSurface)
   {
      // that didn't work...
      // throw?
   }

   _width = width;
   _height = height;

   // reset the OpenGL context.
   glEnable(GL_TEXTURE_2D);
   glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
   glViewport(0, 0, width, height);
   glClear(GL_COLOR_BUFFER_BIT);

   Matrix projection;
   Matrix::createOrthographic(0.0f, width, height, 0.0f, -1.0f, 1.0, projection);
   glMatrixMode(GL_PROJECTION);
   glLoadMatrixf(projection.data());

   glMatrixMode(GL_MODELVIEW);
   glLoadMatrixf(Matrix::identity().data());
}

SDL_Surface* Window::getSurface()
{
   return _windowSurface;
}

uint32_t Window::getWidth()
{
   return _width;
}

uint32_t Window::getHeight()
{
   return _height;
}

} // namespace SDL
} // namespace client
} // namespace squidge
