#ifndef SDDS_TIMER_H
#define SDDS_TIMER_H

#include <chrono>

using namespace std::chrono;

namespace sdds 
{
   class Timer {
      steady_clock::time_point startTime;
   public:
      void start();
      long long stop();
   };
}
#endif