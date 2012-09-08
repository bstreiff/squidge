#include <stdio.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include "client/sdl/Initializer.h"
#include "client/sdl/Window.h"
#include "client/Stopwatch.h"
#include "common/Vector2.h"
#include "common/Rectangle.h"
#include "client/SpriteBatch.h"
#include "client/Texture.h"
#include "client/Level.h"
#include "client/LevelGenerator.h"

namespace squidge {
namespace client {

int main(int argc, char* argv[])
{
   SDL::Initializer sdlInit(SDL_INIT_VIDEO);
   SDL::Window window(640, 480);
   Stopwatch stopwatch;

   Level level;
   LevelGenerator levelGenerator;
   // TODO: temporary level size matches the window size. :)
   levelGenerator.generate(40, 30, level);

   glClearColor(0.0f, 0.0f, 0.3f, 0.0f);

   glEnable(GL_BLEND);
   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

   SDL_Event event;
   stopwatch.reset();
   while (1)
   {
      // process input
      while(SDL_PollEvent(&event))
      {
         switch(event.type)
         {
            case SDL_QUIT:
            case SDL_KEYDOWN:
               return 1;
            default:
               break;
         }
      }

      TimeDuration delta = stopwatch.getDelta();
      if (delta > 0)
      {
         // TODO: update NPCs, physics, world, etc.
      }

      // draw
      SpriteBatch sb;
      sb.drawBegin();

      level.draw(sb);
      
      sb.drawEnd();
   }

   return 0;
}

} // namespace client
} // namespace squidge


int main(int argc, char* argv[])
{
   return squidge::client::main(argc, argv);
}
