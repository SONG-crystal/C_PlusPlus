//*****************************************************************************
// Workshop - #4
// Full Name  : SuJung Song
// Student ID : 172745218
// Email      : ssong49@myseneca.ca
// Section    : OOP345NEE
//
// Authenticity Declaration 
// I declare this submission is the result of my own work and has not been
// shared with any other student or 3rd party content provider.This submitted
// piece of work is entirely of my own creation.
//*****************************************************************************

#include "Restaurant.h"
#include "ConfirmationSender.h"

namespace sdds
{
   ConfirmationSender::ConfirmationSender() {};

   ConfirmationSender::ConfirmationSender(const ConfirmationSender& res) {
      *this = res;
   }

   ConfirmationSender::ConfirmationSender(ConfirmationSender&& res) {
      *this = std::move(res);
   }

   ConfirmationSender& ConfirmationSender::operator=(const ConfirmationSender& res)
   {
      if (this != &res) {
         delete[] m_restPtr;

         m_size = res.m_size;   //shallow copy

         m_restPtr = new const Reservation * [m_size];

         for (size_t i = 0; i < m_size; i++) {
            m_restPtr[i] = res.m_restPtr[i];
         }
      }
      return *this;
   }

   ConfirmationSender& ConfirmationSender::operator=(ConfirmationSender&& res)
   {
      if (this != &res) {
         delete[] m_restPtr;

         m_size = res.m_size; //shallow copy
         res.m_size = 0;

         m_restPtr = res.m_restPtr; //move pointer
         res.m_restPtr = nullptr;
      }
      return *this;
   }

   ConfirmationSender::~ConfirmationSender() {
      delete[] m_restPtr;
   }

   // adds the reservation res to the array by adding its address
   ConfirmationSender& ConfirmationSender::operator+=(const Reservation& res) {
      int found = -1;
      bool ok = false;
      for (size_t i = 0; i < m_size && !ok; i++) {
         if (m_restPtr[i] == &res) {
            ok = true;
            found = i;
         }
      }

      if (found < 0) { //if there is not matching res in array        

         const Reservation** temp = new const Reservation * [m_size + 1];   //resizes the array in temp

         for (size_t i = 0; i < m_size; i++) // copy
            temp[i] = m_restPtr[i]; 
         
         temp[m_size] = &res;  //stores the address of res in last index of array

         delete[] m_restPtr; //delete pointer
         m_restPtr = temp;   //now pointer m_restPtr pointing to temp

         m_size++;
      }
      return *this;
   }

   //removes the reservation res from the array by removing its address
   ConfirmationSender& ConfirmationSender::operator-=(const Reservation& res) {

      bool found = false;
      size_t i = 0;

      if (m_restPtr != nullptr) {
         for (; i < m_size && !found; ++i) {
            if (m_restPtr[i] == &res) {
               found = true;
            }
         }

         if (found) {
            for (; i < m_size; ++i) {
               m_restPtr[i - 1] = m_restPtr[i];
            }
            if (m_size > 0) {
               m_restPtr[m_size - 1] = nullptr;
               m_size--;
            }

            //const Reservation** temp = new const Reservation * [m_size];
            //for (size_t i = 0; i < m_size; i++) {
            //   if (m_restPtr[i] != nullptr) {
            //      temp[i] = m_restPtr[i];
            //   }
            //}
            //delete[] m_restPtr;

            //m_restPtr = new const Reservation * [m_size];
            //for (size_t i = 0; i < m_size; i++) {
            //   m_restPtr[i] = temp[i];
            //}
            //delete[] temp;
         }

      }
      return *this;
   }

    std::ostream& operator<<(std::ostream& os, const ConfirmationSender& con) {

      os << "--------------------------" << std::endl;
      os << "Confirmations to Send" << std::endl;
      os << "--------------------------" << std::endl;

      if (con.m_size == 0)  
         os << "There are no confirmations to send!" << std::endl;
      else {
         for (size_t i = 0; i < con.m_size; i++) 
            os << *con.m_restPtr[i];
      }
      os << "--------------------------" << std::endl;
      return os;
   };
}
