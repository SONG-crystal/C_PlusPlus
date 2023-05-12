#define _CRT_SECURE_NO_WARNINGS
#include "Error.h"

namespace sdds {


   Error::Error()
   {
      m_emPointer = nullptr;
   }

   Error::Error(const char* errorMsg)
   {
      //delete[] m_emPointer;
      m_emPointer = nullptr;

      if (errorMsg != nullptr && errorMsg[0] != '\0')
      {
         m_emPointer = new char[strlen(errorMsg) + 1]; //memory leak
         strcpy(m_emPointer, errorMsg);
      }
   }

   Error::Error(const Error& E)
   {
      //delete[] m_emPointer;
      m_emPointer = nullptr;
      *this = E;
   }

   Error& Error::operator=(const Error& E)
   {
      if (this != &E)
      {
         delete[] m_emPointer;
         m_emPointer = nullptr;

         if (E)
         {
            m_emPointer = new char[strlen(E.m_emPointer) + 1];
            strcpy(m_emPointer, E.m_emPointer);
            //unsigned int i;
            //for (i = 0; i < strlen(E.m_emPointer); i++) {
            //   *(m_emPointer + i) = *(E.m_emPointer + i);
            //}
         }
      }
      return *this;
   }

   Error::~Error()
   {
      delete[] m_emPointer;
      m_emPointer = nullptr;
   }

   Error::operator bool() const
   {
      return m_emPointer != nullptr; //null means the object is no error
   }

   std::ostream& Error::getPointer(std::ostream& os)
   {
      if (*this)
         os << m_emPointer;
      return os;
   }



   Error& Error::setPointer(const char* warning)
   {


      if (warning && warning[0] != '\0')
      {

         delete[] m_emPointer;
         //m_emPointer = nullptr;

         m_emPointer = new char[strlen(warning) + 1];
         strcpy(m_emPointer, warning);
      }
      return *this;
   }

   Error& Error::clear() //when an object is creating, using this methods
   {
      delete[] m_emPointer; //memory leak!!!!!!!!!!!!!!!!
      m_emPointer = nullptr;
      return *this;
   }


   std::ostream& Error::display(std::ostream& os) const
   {
      if (m_emPointer != nullptr) {
         os << m_emPointer;
      }

      return os;
   }


   std::ostream& operator<<(std::ostream& os, const Error& E)
   {
      E.display(os);
      return os;
   }

}
