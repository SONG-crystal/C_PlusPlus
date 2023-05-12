#ifndef SDDS_POSAPP_H_
#define SDDS_POSAPP_H_
#include "Utils.h"

namespace sdds 
{
   class PosApp {
      char* m_fileName{};
      //Utils* m_util{};

      PosApp& setEmpty();
   public:
      PosApp();
      PosApp(const char * fileName);

      PosApp(const PosApp& pA) = delete;
      PosApp& operator=(const PosApp& pA) = delete;

      ~PosApp();

      void setFileName(const char* fileName);

      //std::istream& read(std::istream& istr = std::cin);
      std::ostream& display(std::ostream& ostr = std::cout);

      PosApp& setLine();
      PosApp& menu();
      PosApp& run();
      PosApp& listItem();
      PosApp& addItem();
      PosApp& removeItem();
      PosApp& stockItem();
      PosApp& pointOfSale();
      PosApp& exitProgram();

      operator bool() const;
   };



}
#endif