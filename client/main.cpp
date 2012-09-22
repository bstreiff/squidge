#include <stdio.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include "client/sdl/Initializer.h"
#include "client/sdl/Window.h"
#include "client/Stopwatch.h"
#include "common/Vector2.h"
#include "common/Rectangle.h"
#include "common/Matrix.h"
#include "client/graphics/SpriteBatch.h"
#include "client/Level.h"
#include "client/LevelGenerator.h"
#include "client/TestEntity.h"

namespace squidge {
namespace client {

int main(int argc, char* argv[])
{
   SDL::Initializer sdlInit(SDL_INIT_VIDEO);
   SDL::Window window(800, 600);
   Stopwatch stopwatch;

   Level level;
   LevelGenerator levelGenerator;
   // TODO: temporary level size
   levelGenerator.generate(80, 60, level);

   // TODO: create some temporary entities
   std::vector<EdictPtr> edicts;
   edicts.push_back(EdictPtr(new TestEntity(Vector2(0, -10), 1)));
   edicts.push_back(EdictPtr(new TestEntity(Vector2(10, -5), 2)));
   edicts.push_back(EdictPtr(new TestEntity(Vector2(11, -5), 3)));

   // Camera position.
   Vector2 camera(0.0f, 0.0f);

   bool upHeld = false;
   bool downHeld = false;
   bool leftHeld = false;
   bool rightHeld = false;

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
               return 1;
            case SDL_KEYDOWN:
               switch(event.key.keysym.sym)
               {
                  case SDLK_UP:
                     upHeld = true;
                     break;
                  case SDLK_DOWN:
                     downHeld = true;
                     break;
                  case SDLK_LEFT:
                     leftHeld = true;
                     break;
                  case SDLK_RIGHT:
                     rightHeld = true;
                     break;
                  default:
                     break;
               }
               break;
            case SDL_KEYUP:
               switch(event.key.keysym.sym)
               {
                  case SDLK_UP:
                     upHeld = false;
                     break;
                  case SDLK_DOWN:
                     downHeld = false;
                     break;
                  case SDLK_LEFT:
                     leftHeld = false;
                     break;
                  case SDLK_RIGHT:
                     rightHeld = false;
                     break;
                  default:
                     break;
               }
            default:
               break;
         }
      }

      TimeDuration delta = stopwatch.getDelta();
      if (delta > 0)
      {
         // TODO: update NPCs, physics, world, etc.

         // update the camera
         if (upHeld)
            camera.y -= delta * 500;
         if (downHeld)
            camera.y += delta * 500;
         if (leftHeld)
            camera.x -= delta * 500;
         if (rightHeld)
            camera.x += delta * 500;
      }

      // draw
      Matrix modelview;
      // TODO: Camera translation should be on the projection matrix,
      // not the modelview one.
      Matrix::createTranslation(
         -camera.x + (window.getWidth() / 2),
         -camera.y + (window.getHeight() / 2),
         0.0f,
         modelview);
      glMatrixMode(GL_MODELVIEW);
      glLoadMatrixf(modelview.data());

      SpriteBatch sb;
      sb.drawBegin();

      level.draw(sb);
      for (std::vector<EdictPtr>::const_iterator edictItr = edicts.begin();
           edictItr != edicts.end(); ++edictItr)
      {
         (*edictItr)->draw(sb);
      }
      
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
