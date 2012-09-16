#include "client/graphics/SpriteBatch.h"
#include <SDL.h>
#include <SDL_opengl.h>
#include <stdexcept>

namespace squidge {
namespace client {

SpriteBatch::SpriteBatch() :
   _drawQueue(),
   _hasBegun(false)
{ }

void SpriteBatch::drawBegin()
{
   if (_hasBegun)
      throw std::logic_error("SpriteBatch::drawBegin() called multiple times.\n");
   _hasBegun = true;
}

void SpriteBatch::draw(
   boost::shared_ptr<Texture> texture,
   Rectangle sourceRect,
   Point position)
{
   draw(
      texture,
      sourceRect,
      Rectangle(position.x, position.y, sourceRect.width, sourceRect.height));
}

void SpriteBatch::draw(
   boost::shared_ptr<Texture> texture,
   Rectangle sourceRect,
   Rectangle destRect)
{
   if (!_hasBegun)
      throw std::logic_error("SpriteBatch::draw() without drawBegin\n");

   SpriteWorkItem swi =
   {
      texture,
      sourceRect,
      destRect
   };

   _drawQueue.push_back(swi);   
}

void SpriteBatch::drawEnd()
{
   if (!_hasBegun)
      throw std::logic_error("SpriteBatch::drawEnd() without correponding drawBegin\n");

   glClear(GL_COLOR_BUFFER_BIT);

   // TODO: Combine all the SpriteWorkItems into one giant blob of
   // vertices and texcoords per texture id.

   glEnableClientState(GL_VERTEX_ARRAY);
   glEnableClientState(GL_TEXTURE_COORD_ARRAY);

   for (std::list<SpriteWorkItem>::const_iterator itr = _drawQueue.begin();
        itr != _drawQueue.end(); ++itr)
   {
      const SpriteWorkItem& sprite = *itr;

      glBindTexture(GL_TEXTURE_2D, sprite.texture->getTextureID());

      float vertices[] =
      {
         sprite.destRect.left(), sprite.destRect.top(),
         sprite.destRect.left(), sprite.destRect.bottom(),
         sprite.destRect.right(), sprite.destRect.bottom(),
         sprite.destRect.right(), sprite.destRect.top(),
      };
      float texcoords[] =
      {
         static_cast<float>(sprite.sourceRect.left()) / sprite.texture->getWidth(),
            static_cast<float>(sprite.sourceRect.top()) / sprite.texture->getHeight(),
         static_cast<float>(sprite.sourceRect.left()) / sprite.texture->getWidth(),
            static_cast<float>(sprite.sourceRect.bottom()) / sprite.texture->getHeight(),
         static_cast<float>(sprite.sourceRect.right()) / sprite.texture->getWidth(),
            static_cast<float>(sprite.sourceRect.bottom()) / sprite.texture->getHeight(),
         static_cast<float>(sprite.sourceRect.right()) / sprite.texture->getWidth(),
            static_cast<float>(sprite.sourceRect.top()) / sprite.texture->getHeight()
      };

      glVertexPointer(2, GL_FLOAT, 0, vertices);
      glTexCoordPointer(2, GL_FLOAT, 0, texcoords);
      glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
   }

   glDisableClientState(GL_VERTEX_ARRAY);
   glDisableClientState(GL_TEXTURE_COORD_ARRAY);


   _drawQueue.clear();

   SDL_GL_SwapBuffers();
}

} // namespace client
} // namespace squidge
