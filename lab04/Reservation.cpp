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

namespace sdds
{
   Reservation::Reservation() {};

   void Reservation::update(int day, int time) {
      m_day = static_cast<size_t>(day);
      m_time = static_cast<size_t>(time);
   };

   Reservation::Reservation(std::string& res) { 

      m_id = res.substr(0, res.find(':'));        // Extract ID
      m_id.erase(0, m_id.find_first_not_of(' ')); // Remove left whitespace
      m_id.erase(m_id.find_last_not_of(' ') + 1); // Remove right whitespace
      res.erase(0, res.find(':') + 1);            // Erase Until ID for next step

      m_name = res.substr(0, res.find(','));          
      m_name.erase(0, m_name.find_first_not_of(' ')); 
      m_name.erase(m_name.find_last_not_of(' ') + 1); 
      res.erase(0, res.find(',') + 1);                

      m_email = res.substr(0, res.find(','));
      m_email.erase(0, m_email.find_first_not_of(' '));
      m_email.erase(m_email.find_last_not_of(' ') + 1);
      m_email = "<" + m_email + ">";
      res.erase(0, res.find(',') + 1);                         

      m_numPeople = std::stoi(res.substr(0, res.find(','))); 
      res.erase(0, res.find(',') + 1);                      

      m_day = std::stoi(res.substr(0, res.find(',')));        
      res.erase(0, res.find(',') + 1);                       

      m_time = std::stoi(res);  // Extract Time (size_t <--- string using "stoi")



      if (6 <= m_time && m_time <= 9) {
         m_bld = "Breakfast";
      }
      else if (11 <= m_time && m_time <= 15) {
         m_bld = "Lunch";
      }
      else if (17 <= m_time && m_time <= 21) {
         m_bld = "Dinner";
      }
      else {
         m_bld = "Drinks";
      }
   }

   std::ostream& Reservation::display(std::ostream& os) const {

      os << "Reservation ";
      os << std::setw(10) << std::right << m_id << ": ";
      os << std::setw(20) << std::right << m_name << "  ";
      os << std::setw(20) << std::left << m_email << "    ";
      os << m_bld << " on day ";
      os << m_day;
      os << " @ ";
      os << m_time;
      os << ":00 for ";
      os << m_numPeople;
      if (m_numPeople == 1) {
         os << " person." << std::endl;
      }
      else {
         os << " people." << std::endl;
      }
      return os;
   }


   std::ostream& operator<<(std::ostream& os, const Reservation& res)
   {
      return res.display(os);
   }

}