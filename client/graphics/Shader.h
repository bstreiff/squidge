#pragma once

#include <SDL_opengl.h>
#include <boost/filesystem.hpp>

namespace squidge {
namespace client {

class Shader
{
public:
   Shader(GLenum shaderType, boost::filesystem::path& filename);
   ~Shader();

   GLuint id() const;

private:
   GLuint _shader;

};

} // namespace client
} // namespace squidge
