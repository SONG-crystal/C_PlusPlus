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

#include "Reservation.h"
#include "Restaurant.h"

namespace sdds
{
   Restaurant::Restaurant() {};

   Restaurant::Restaurant(const Reservation* reservations[], size_t cnt) : m_CNT(cnt) {
      if (m_CNT > 0) {
         m_reserPtr = new Reservation* [m_CNT];  //allocate memory, array of pointer 

         for (size_t i = 0; i < m_CNT; i++) {      
            m_reserPtr[i] = new Reservation;
            *m_reserPtr[i] = *reservations[i];    //should copies of all reservations
         }
      }
   }

   size_t Restaurant::size() const {
      return m_number;
   }

   //in cpp, do not need to put "std::ostream& os = std::cout"
   std::ostream& Restaurant::display(std::ostream& os) const {
      for (size_t i = 0; i < m_CNT; i++) {
         os << *m_reserPtr[i];
      }
      return os;
   }

   Restaurant::Restaurant(const Restaurant& res) {
      *this = res;
   }

   Restaurant::Restaurant(Restaurant&& res) {
      *this = std::move(res);
   }

   Restaurant& Restaurant::operator=(const Restaurant& res){
      if (this != &res) {
         for (size_t i = 0; i < m_CNT; i++) 
            delete m_reserPtr[i]; // deallocate all resPtr one by one
         delete[] m_reserPtr;     // deallocate container of resPtr 

         m_CNT = res.m_CNT;                // shallow copy
         if (res.m_reserPtr != nullptr) {  // deep copy
            m_reserPtr = new Reservation* [res.m_CNT];   // allocate container of resPtr 

            for (size_t i = 0; i < m_CNT; i++) {  
               m_reserPtr[i] = new Reservation;          // deallocate all resPtr one by one
               *m_reserPtr[i] = *res.m_reserPtr[i];      // should copies of all reservations
            }
         }
      }
      return *this;
   }

   Restaurant& Restaurant::operator=(Restaurant&& res)
   {
      if (this != &res) {
         for (size_t i = 0; i < m_CNT; i++)  
            delete m_reserPtr[i];
         delete[] m_reserPtr;

         m_CNT = res.m_CNT; //shallow copy
         res.m_CNT = 0;

         m_reserPtr = res.m_reserPtr; //move pointer
         res.m_reserPtr = nullptr;
      }
      return *this;
   }

   //in CPP, keyword "virtual" is not needed
   Restaurant::~Restaurant() {
      for (size_t i = 0; i < m_CNT; i++) 
         delete m_reserPtr[i]; 
      delete[] m_reserPtr;
   };


   //friend helper, do not need to put "friend" keyword in cpp, as well as Restaurant::
   std::ostream& operator<<(std::ostream& os, const Restaurant& res)
   {
      res.m_number++;
      os << "--------------------------" << std::endl;
      os << "Fancy Restaurant (" << res.size() << ")" << std::endl;
      os << "--------------------------" << std::endl;

      if (res.m_CNT != 0) 
         res.display(os);
      else {
         os << "This restaurant is empty!" << std::endl;
      }
      std::cout << "--------------------------" << std::endl;
      
      return os;
   }

   //static, it should be initialize at once outside of class in CPP
   size_t Restaurant::m_number{ 0 };
}
