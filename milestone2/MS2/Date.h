#ifndef SDDS_DATE_H
#define SDDS_DATE_H
#include "Error.h"
#include "Utils.h"
namespace sdds 
{
   class Date 
   {
      int m_year{};
      int m_month{};
      int m_day{};

      int m_hour{};
      int m_minute{};

      bool m_dateOnlyflag{}; 
      Error m_trackError; 

   public:
      Date();
      Date(int year, int month, int day);
      Date(int year, int month, int day, int hour, int min=0);

      int getYear();
      int getMonth();
      int getDay();
      int getHour();
      int getMin();

      Date& dateOnly(bool date);
      operator bool() const;
      const Error& error() const;
      std::ostream& display(std::ostream& os = std::cout);
      std::istream& read(std::istream& os = std::cin);

      Date& setEmpty();
   };
   bool operator==(Date& lDate, Date& rDate);
   bool operator!=(Date& lDate, Date& rDate);
   bool operator<(Date& lDate, Date& rDate);
   bool operator>(Date& lDate, Date& rDate);
   bool operator<=(Date& lDate, Date& rDate);
   bool operator>=(Date& lDate, Date& rDate);

   std::ostream& operator<<(std::ostream& os, Date& dateObj);
   std::istream& operator>>(std::istream& is, Date& dateObj);

}                                                   
#endif