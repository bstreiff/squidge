#pragma once

#include <boost/chrono.hpp>

namespace squidge {
namespace client {

typedef double TimeDuration;

class Stopwatch
{
public:
   Stopwatch();

   TimeDuration getDelta();
   void reset();

private:
   boost::chrono::high_resolution_clock::time_point _previousTime;
};

} // namespace client
} // namespace squidge
                