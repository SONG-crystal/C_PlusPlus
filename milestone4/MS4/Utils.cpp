#define _CRT_SECURE_NO_WARNINGS
#include <ctime>
#include "Utils.h"
#include <iostream>

using namespace std;

namespace sdds
{
   Utils U;

   void Utils::flushkeys()
   {
      while (cin.get() != '\n');
   }



   int Utils::getInt()
   {
      int value{};
      bool done{};
      do
      {
         cin >> value;
         done = false;


         if (cin) //if(!cin.fail())
         {
            if (cin.get() != '\n')  //if the next char after int is not newline
            {
               cout << "Invalid Integer, try again: ";
               flushkeys();

            }
            else
            {
               done = getInt(0, 5, value);
            }
         }
         else
         {
            cin.clear(); //clear the fail state
            cout << "Invalid Integer, try again: ";
            if (!done) cin.ignore(10000, '\n');
         }

      } while (!done);

      return value;
   }


   int Utils::getInt(int min, int max, int value)
   {
      //if value is not 0-5, it will return 0(flase),
      //else value is 0-5, it will return 1(true)
      if (value <min || value > max)
      {
         cout << "[0<=value<=5], retry: > ";
         value = 0;
      }
      else
      {
         value = 1;
      }

      return value;
   }
   //system date and time
   void Utils::getSystemDate(int& year, int& mon, int& day, int& hour, int& min, bool dateOnly)
   {
      time_t t = time(NULL);
      tm lt = *localtime(&t);
      day = lt.tm_mday;
      mon = lt.tm_mon + 1;
      year = lt.tm_year + 1900;
      if (dateOnly) {
         hour = min = 0;
      }
      else {
         hour = lt.tm_hour;
         min = lt.tm_min;
      }
   }

   //Unique Date and Time integer value retrieval
   int Utils::uniqueDateValue(int year, int mon, int day, int hour, int min)
   {
      return year * 535680 + mon * 44640 + day * 1440 + hour * 60 + min;
   }

   //Number of days in the month based on leap year calculation
   int Utils::daysOfMonth(int year, int month)
   {
      int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
      int mon = month >= 1 && month <= 12 ? month : 13;
      mon--;
      return days[mon] + int((mon == 1) * ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
   }

   void strCat(char* des, const char* src) {
      while (*des) des++;
      while (*src) *des++ = *src++;
      *des = *src;
   }
}
