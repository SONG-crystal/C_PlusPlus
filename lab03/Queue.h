#pragma once
#include "Dictionary.h"

namespace sdds
{
   template<typename T, size_t CAPACITY>
   class Queue 
   {
      T m_collection[CAPACITY]{};  //non-type template parameter
      size_t m_currentStoring{};
      static T m_dummy;            //"class member!" means STATIC!!!!

   public:

      virtual bool push(const T& item){
         bool ok = false;
         if (CAPACITY > m_currentStoring) {
            m_collection[m_currentStoring++] = item;
            ok = true;

         }
         return ok;
      }

      T pop()
      {
         T temp = m_collection[0];
         for (size_t i = 0; i < m_currentStoring-1; i++) {
            m_collection[i] = m_collection[i+1];
         }
         m_currentStoring--;
         return temp;
      }

      size_t size() const {
         return m_currentStoring;
      }

      std::ostream& display(std::ostream& os = std::cout) const {
         os << "----------------------" << std::endl;
         os << "| Dictionary Content |" << std::endl;
         os << "----------------------" << std::endl;
         for (size_t i = 0; i < m_currentStoring; i++) {
            os << m_collection[i] << std::endl;
         }

         os << "----------------------" << std::endl;
         return os;
      }

      T operator[](size_t index) const {
         return (index < m_currentStoring) ? m_collection[index] : m_dummy;
      }

      virtual ~Queue() {};
   };

   //helper function
   template <typename T>
   std::ostream& operator<<(std::ostream& os, const T& item) {
      return item.display(os);
   }

   //specialization
   template<>
   Dictionary Queue<Dictionary, 100u>::m_dummy = { "Empty Term", "Empty Substitute" };


   //initialize at once 
   template<typename T, size_t CAPACITY>
   T Queue<T, CAPACITY>::m_dummy{};
}
