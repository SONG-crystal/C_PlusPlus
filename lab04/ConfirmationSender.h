#pragma once
#include "Restaurant.h"
namespace sdds
{
   class ConfirmationSender {
      const Reservation** m_restPtr{}; //  aggregation
      size_t m_size{};

   public:
      ConfirmationSender();

      ConfirmationSender(const ConfirmationSender& res);
      ConfirmationSender(ConfirmationSender&& res);
      ConfirmationSender& operator=(const ConfirmationSender& res);
      ConfirmationSender& operator=(ConfirmationSender&& res);
      virtual ~ConfirmationSender();

      ConfirmationSender& operator+=(const Reservation& res);
      ConfirmationSender& operator-=(const Reservation& res);

      friend std::ostream& operator<<(std::ostream& os, const ConfirmationSender& con);
   };
}
