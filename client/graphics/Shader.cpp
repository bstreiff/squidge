#include "client/graphics/Shader.h"
#include <iostream>
#include <fstream>
#include <stdexcept>

namespace squidge {
namespace client {

Shader::Shader(
   GLenum shaderType,
   boost::filesystem::path& filename) :
   _shader(0)
{
   // Load the shader file.
   std::string code;
   std::ifstream inputStream(filename.string().c_str(), std::ios::in);
   if (inputStream.is_open())
   {
      std::string line("");
      while (std::getline(inputStream, line))
      {
         code += "\n" + line;
      }
      inputStream.close();
   }
   else
   {
      throw std::logic_error("couldn't open shader");
   }

   // Now compile it.
   _shader = glCreateShader(shaderType);

   const char* codeCStr = code.c_str();
   glShaderSource(_shader, 1, &codeCStr, NULL);
   glCompileShader(_shader);

   // Did compilation succeed?
   GLint compilationResult = GL_FALSE;
   glGetShaderiv(_shader, GL_COMPILE_STATUS, &compilationResult);
   GLint infoLogLength = 0;
   glGetShaderiv(_shader, GL_INFO_LOG_LENGTH, &infoLogLength);
   std::vector<char> infoLog;
   glGetShaderInfoLog(_shader, infoLogLength, NULL, &infoLog[0]);

   // TODO: should probably do something aside from just print this...
   printf("%s\n", &infoLog[0]);
}

Shader::~Shader()
{
   if (_shader != 0)
   {
      glDeleteShader(_shader);
      _shader = 0;
   }
}

GLuint Shader::id() const
{
   return _shader;
}

} // namespace client
} // namespace squidge
