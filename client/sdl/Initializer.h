#pragma once

#include <stdint.h>
#include <boost/utility.hpp>

namespace squidge {
namespace client {
namespace SDL {

class Initializer : boost::noncopyable
{
public:
   Initializer(uint32_t flags);
   ~Initializer();
private:
   bool _sdlWasInited;
   bool _sdlImageWasInited;
};

} // namespace SDL
} // namespace client
} // namespace squidge
