#include <iostream>
#include "POS.h"
#include "Date.h"
#include <iomanip>
namespace sdds {


   Date::Date()
   {
      setEmpty();
      U.getSystemDate(m_year, m_month, m_day, m_hour, m_minute, m_dateOnlyflag);
      m_dateOnlyflag = false;
   }

   Date::Date(int year, int month, int day)
   {
      setEmpty();
      m_year = year;
      m_month = month;
      m_day = day;

      m_dateOnlyflag = true;

      if (m_year < MIN_YEAR || m_year > MAX_YEAR) {
         m_trackError.setPointer("Invalid Year");
      }
      else 
      {
         if (m_month < 1 || m_month > 12) {
            m_trackError.setPointer("Invalid Month");
         }
         else 
         {
            if (m_day < 1 || m_day > U.daysOfMonth(m_year, m_month)) {
               m_trackError.setPointer("Invalid Day");
            }
         }
      }
   }


   Date::Date(int year, int month, int day, int hour, int min)
   {
      setEmpty(); // must nedded 

      *this = Date(year, month, day);

      m_hour = hour;
      m_minute = min;
      m_dateOnlyflag = false;

      if (m_hour < 0 || m_hour > 23) {
         m_trackError.setPointer("Invalid Hour");
      }
      else 
      {
         if (m_minute < 0 || m_minute > 50) {
            m_trackError.setPointer("Invlid Minute");
         }
      }

   }

   int Date::getYear()
   {
      return m_year;
   }

   int Date::getMonth()
   {
      return m_month;
   }

   int Date::getDay()
   {
      return m_day;
   }

   int Date::getHour()
   {
      return m_hour;
   }

   int Date::getMin()
   {
      return m_minute;
   }

   Date& Date::dateOnly(bool date)
   {
      if (date == true)
      {
         m_hour=0;
         m_minute=0;
         m_dateOnlyflag = date;
      }
      else 
      {
         m_dateOnlyflag = date;
      }
      return *this;
   }

   Date::operator bool() const
   {
      return !bool(m_trackError);
   }

   const Error& Date::error() const
   {
      return m_trackError; 
   }

   //precision
   std::ostream& Date::display(std::ostream& os) 
   {
      if (bool(m_trackError)) 
      {
         os << m_trackError << "(";
      }

      os << m_year << "/";
      os << std::setfill('0') << std::setw(2) << m_month << "/";
      os << std::setfill('0') << std::setw(2) << m_day;


      if (m_dateOnlyflag == false) 
      {
         os << ", ";
         os << std::setfill('0') << std::setw(2) << m_hour << ":";
         os << std::setfill('0') << std::setw(2) << m_minute;
      }

      if (m_trackError) 
      {
         os << ")";
      }
     return os;
   }

   std::istream& Date::read(std::istream& is)
   {
      setEmpty();

      if (m_dateOnlyflag == true) 
      {
         is >> m_year;
         if (is)
         {
            is.ignore();
            is >> m_month;
            if (is)
            {
               is.ignore();
               is >> m_day;
               if (is) 
               {
                  *this = Date(m_year, m_month, m_day);
               }
               else 
               {
                  *this = Date(m_year, m_month, 0);
                  m_trackError.setPointer("Cannot read day entry");
               }
            }
            else 
            {
               *this = Date(m_year, 0, 0);
               m_trackError.setPointer("Cannot read month entry");
            }
         }
         else 
         {
            *this = Date(0, 0, 0);
            m_trackError.setPointer("Cannot read year entry");
         }
      }


      if (m_dateOnlyflag == false)
      {
         is >> m_year;
         if (is)
         {
            is.ignore();
            is >> m_month;
            if (is)
            {
               is.ignore();
               is >> m_day;
               if (is)
               {
                  is.ignore();
                  is >> m_hour;
                  if (is) 
                  {
                     is.ignore();
                     is >> m_minute;
                     if (is) 
                     {
                        *this = Date(m_year, m_month, m_day, m_hour, m_minute);
                     }
                     else 
                     {
                        *this = Date(m_year, m_month, m_day, m_hour, 0);
                        m_trackError.setPointer("Cannot read minute entry");
                     }
                  }
                  else 
                  {
                     *this = Date(m_year, m_month, m_day, 0, 0);
                     m_trackError.setPointer("Cannot read hour entry");
                  }
               }
               else
               {
                  *this = Date(m_year, m_month, 0, 0, 0);
                  m_trackError.setPointer("Cannot read day entry");
               }
            }
            else
            {
               *this = Date(m_year, 0, 0, 0, 0);
               m_trackError.setPointer("Cannot read month entry");
            }
         }
         else
         {
            *this = Date(0, 0, 0, 0, 0);
            m_trackError.setPointer("Cannot read year entry");
         }
      }

       //is.ingore();   //when I try to erase buffer twice, it need to me input something

       return is;
   }
   

   Date& Date::setEmpty()
   {
      m_year =0;
      m_month = 0;
      m_day = 0;
      m_hour = 0;
      m_minute = 0;
      //m_dateOnlyflag = false;
      
      m_trackError.clear(); //  m_emPointer = nullptr;

      return *this;
   }

   bool operator==(Date& lDate, Date& rDate)
   {
      bool ok = false;
      if ((lDate.getYear() == rDate.getYear())
         && (lDate.getMonth() == rDate.getMonth())
         && (lDate.getDay() == rDate.getDay())
         && (lDate.getHour() == rDate.getHour())
         && (lDate.getMin() == rDate.getMin())) {
         ok = true;
      }
      return ok;
   }

   bool operator!=(Date& lDate, Date& rDate)
   {
      bool ok = false;
      if ((lDate.getYear() != rDate.getYear())
         || (lDate.getMonth() != rDate.getMonth())
         || (lDate.getDay() != rDate.getDay())
         || (lDate.getHour() != rDate.getHour())
         || (lDate.getMin() != rDate.getMin())) {
         ok = true;
      }
      return ok;
   }

   bool operator<(Date& lDate, Date& rDate)
   {
      bool ok = false;
      if ((lDate.getYear() < rDate.getYear())
         || (lDate.getMonth() < rDate.getMonth())
         || (lDate.getDay() < rDate.getDay())
         || (lDate.getHour() < rDate.getHour())
         || (lDate.getMin() < rDate.getMin())) {
         ok = true;
      }
      return ok;
   }

   bool operator>(Date& lDate, Date& rDate)
   {
      bool ok = false;
      if ((lDate.getYear() > rDate.getYear())
         || (lDate.getMonth() > rDate.getMonth())
         || (lDate.getDay() > rDate.getDay())
         || (lDate.getHour() > rDate.getHour())
         || (lDate.getMin() > rDate.getMin())) {
         ok = true;
      }
      return ok;
   }

   bool operator<=(Date& lDate, Date& rDate)
   {
      bool ok = false;
      if ((lDate.getYear() <= rDate.getYear())
         && (lDate.getMonth() <= rDate.getMonth())
         && (lDate.getDay() <= rDate.getDay())
         && (lDate.getHour() <= rDate.getHour())
         && (lDate.getMin() <= rDate.getMin())) {
         ok = true;
      }
      return ok;
   }

   bool operator>=(Date& lDate, Date& rDate)
   {
      bool ok = false;
      if ((lDate.getYear() >= rDate.getYear())
         && (lDate.getMonth() >= rDate.getMonth())
         && (lDate.getDay() >= rDate.getDay())
         && (lDate.getHour() >= rDate.getHour())
         && (lDate.getMin() >= rDate.getMin())) {
         ok = true;
      }
      return ok;
   }

   std::ostream& operator<<(std::ostream& os, Date& dateObj)
   {
      dateObj.display(os);

      return os;
   }

   std::istream& operator>>(std::istream& is, Date& dateObj)
   {
      dateObj.read(is);
      return is;
   }



}