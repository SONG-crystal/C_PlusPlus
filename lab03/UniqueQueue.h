//
// SuJung Song
// 172745218
// OOP345NEE
// 
// I have done all the coding by myself and only copied the code that my professor 
// provided to complete my workshops and assignments.
//
#pragma once
#include <math.h> 
#include "Queue.h"

namespace sdds
{ 
   template<typename T>
   class UniqueQueue : public Queue<T, 100> {

   public: 
      bool push(const T& item) { //override
         bool ok = true;
         for (size_t i = 0; i < 100; i++) {
            if (Queue<T,100>::operator[](i) == item) {
               ok = false; 
            }
         } 

         if (ok == true) {
            return Queue<T, 100>::push(item);
         }
         else {
            return false;
         }
      }
   };
    
   template<>
   bool UniqueQueue<double>::push(const double& item) {
      bool ok = true ;

      for (size_t i = 0; i < 100; i++) {
         if (std::fabs(item) - std::fabs(operator[](i)) >= -0.005 &&
             std::fabs(item) - std::fabs(operator[](i)) <= 0.005) {
            ok = false;
         }
      }

      if (ok == true) {
         return Queue<double, 100>::push(item);
      }
      else {
         return false;
      }
   };

}