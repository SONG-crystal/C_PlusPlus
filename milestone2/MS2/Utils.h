#ifndef SDDS_UTILS_H
#define SDDS_UTILS_H

namespace sdds 
{
   class Utils {
   public:
      void getSystemDate(int& year, int& mon, int& day, int& hour, int& min, bool dateOnly);
      int uniqueDateValue(int year, int mon, int day, int hour, int min);
      int daysOfMonth(int year, int month);
   };

   extern Utils U;
}
#endif