#ifndef SDDS_POSAPP_H_
#define SDDS_POSAPP_H_
#include "Utils.h"
#include "Perishable.h"
#include "NonPerishable.h"
#include "Item.h"

namespace sdds
{
   class PosApp {
      char m_fileName[128 + 1]{};
      Item* m_Iptr[MAX_NO_ITEMS]{}; // Items pointer array //m_Ipt[1]->distype
      int m_nptr{};                 // number of items
      char m_actionTitle[100]{};    //Loadting Items, Listing Items, 
      double m_totalAsset{};
      //Utils* m_util{};

      
   public:
      PosApp();
      PosApp(const char fileName[]);

      PosApp(const PosApp& pA) = delete;
      PosApp& operator=(const PosApp& pA) = delete;
       
      ~PosApp(); 

      void setFileName(const char fileName[]);


      PosApp& menu();
      PosApp& run();


      operator bool() const;

      PosApp& printTotalAsset();
      PosApp& loadRecs();
      PosApp& saveRecs(); 
      PosApp& listItems();
      PosApp& addItem();
      PosApp& selectItem();
      PosApp& stockItem();
      PosApp& removeItem();
      PosApp& POS();
      PosApp& setEmpty();

      Item* search(const char sku[]) const;

      void sort();
   };
}


#endif