#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#pragma once

namespace sdds
{
   class Reservation {
      std::string m_id{};
      std::string m_name{};
      std::string m_email{};
      size_t m_numPeople{};
      size_t m_day{};
      size_t m_time{};
      std::string m_bld{};

   public:
      Reservation();

      void update(int day, int time);

      Reservation(std::string& res);

      std::ostream& display(std::ostream& os = std::cout) const;

      friend std::ostream& operator<<(std::ostream& os, const Reservation& res);
   };


}