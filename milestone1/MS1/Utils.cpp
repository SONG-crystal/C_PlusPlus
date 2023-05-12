#include <iostream>
#include "Utils.h"

using namespace std;
namespace sdds
{
   Utils U; // file scope instance called U of Utils in Utils.cpp



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

}