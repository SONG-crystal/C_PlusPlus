
#ifndef SDDS_UTILS_H
#define SDDS_UTILS_H
#include "Item.h"

namespace sdds
{
   class Utils {
   public:
      void flushkeys();
      int getInt();
      int getInt(int min, int max, int value);
      void getSystemDate(int& year, int& mon, int& day, int& hour, int& min, bool dateOnly);
      int uniqueDateValue(int year, int mon, int day, int hour, int min);
      int daysOfMonth(int year, int month);
      void strCat(char* des, const char* src);


   };

   extern Utils U; //this prototype
   //extern make a filescope variable global
}
#endif
