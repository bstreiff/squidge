#pragma once

#include <SDL_opengl.h>
#include <boost/shared_ptr.hpp>

namespace squidge {
namespace client {

class Shader;

class ShaderProgram
{
public:
   ShaderProgram();
   ShaderProgram(
      boost::shared_ptr<Shader> vertexShader,
      boost::shared_ptr<Shader> fragmentShader);
   ~ShaderProgram();

   GLuint id() const;

private:
   boost::shared_ptr<Shader> _vertexShader;
   boost::shared_ptr<Shader> _fragmentShader;
   GLuint _shaderProgram;

};

} // namespace client
} // namespace squidge
