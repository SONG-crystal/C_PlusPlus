#ifndef SDDS_ERROR_H
#define SDDS_ERROR_H
#include <cstring>
#include <iostream>

namespace sdds 
{
   class Error 
   {
      char* m_emPointer{};  //null means the object is no error

   public:
      Error();
      Error(const char* errorMsg);

      //rule of three
      Error(const Error& E);
      Error& operator=(const Error& E);
      ~Error();

      operator bool() const;
      std::ostream& getPointer(std::ostream& os = std::cout);
      Error& setPointer(const char* warning);

      Error& clear();
      std::ostream& display(std::ostream& os = std::cout) const;
      
   };
   std::ostream& operator<<(std::ostream& os, const Error& E);

}
#endif