#include "client/Stopwatch.h"

namespace squidge {
namespace client {

Stopwatch::Stopwatch() : _previousTime( boost::chrono::high_resolution_clock::now() )
{
    /* does nothing. */
}

/* XXX: possibly add pragma to remove warning C4244, possible loss of data
        converting from double to TimeDuration (which is currently float). we
        knowingly do this to prevent catostrophic cancellation from occurring
        when we compute the time delta. */
TimeDuration Stopwatch::getDelta()
{
    boost::chrono::high_resolution_clock::time_point currentTime = boost::chrono::high_resolution_clock::now();
    boost::chrono::high_resolution_clock::duration   elapsedTime = currentTime - _previousTime;

    _previousTime = currentTime;
    return static_cast<TimeDuration>(elapsedTime.count() *
        (static_cast<double>(boost::chrono::high_resolution_clock::period::num) /
                             boost::chrono::high_resolution_clock::period::den) );
}

void Stopwatch::reset()
{
    _previousTime = boost::chrono::high_resolution_clock::now();
}

} // namespace client
} // namespace squidge
                                                                                     