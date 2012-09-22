#include "client/graphics/ShaderProgram.h"
#include "client/graphics/Shader.h"

namespace squidge {
namespace client {

class ShaderProgram
{
public:
ShaderProgram::ShaderProgram() :
   _vertexShader(),
   _fragmentShader(),
   _shaderProgram(0)
{ }

ShaderProgram::ShaderProgram(
   boost::shared_ptr<Shader> vertexShader,
   boost::shared_ptr<Shader> fragmentShader) :
   _vertexShader(vertexShader),
   _fragmentShader(fragmentShader),
   _shaderProgram(0)
{
   _shaderProgram = glCreateProgram();
   glAttachShader(_shaderProgram, vertexShader->id());
   glAttachShader(_shaderProgram, fragmentShader->id());
}

ShaderProgram::~ShaderProgram()
{
   if (_shaderProgram)
   {
      // TODO: Do I need to detach manually?
      glDetachShader(_shaderProgram, vertexShader->id());
      glDetachShader(_shaderProgram, fragmentShader->id());
      glDeleteProgram(_shaderProgram);
   }
}

GLuint ShaderProgram::id() const
{
   return _shaderProgram;
}

} // namespace client
} // namespace squidge
