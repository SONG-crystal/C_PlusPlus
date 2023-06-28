#pragma once
#include "Reservation.h"

namespace sdds
{
   class Restaurant {
      Reservation** m_reserPtr{};  //dynamically allocated arrary of pointer //Composition
      size_t m_CNT{};              //total number of guests
      static size_t m_number;      //how many it be called by system

   public:
      Restaurant();
      Restaurant(const Reservation* reservations[], size_t cnt);
      size_t size() const;
      std::ostream& display(std::ostream& os = std::cout) const;

      Restaurant(const Restaurant& res);
      Restaurant(Restaurant&& res);
      Restaurant& operator=(const Restaurant& res);
      Restaurant& operator=(Restaurant&& res);
      virtual ~Restaurant();

      friend std::ostream& operator<<(std::ostream& os, const Restaurant& res);
   };
}
