#include <iostream>
#include "Timer.h"

using namespace std;
using namespace chrono;

namespace sdds 
{
   void Timer::start()
   {
      startTime = steady_clock::now(); //current system time
   }
   long long Timer::stop()
   {
      steady_clock::time_point endTime = steady_clock::now(); 
      auto nanoSec = duration_cast<nanoseconds>(endTime - startTime).count();
      return nanoSec;
   }
}