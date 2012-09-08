#pragma once

#include <stdint.h>
#include <boost/utility.hpp>
#include "client/Level.h"

namespace squidge {
namespace client {

class LevelGenerator : boost::noncopyable
{
public:
   LevelGenerator();
   ~LevelGenerator();
   
   void generate(uint32_t width, uint32_t height, Level& level);
private:
};

} // namespace client
} // namespace squidge
