#ifndef SDDS_PERISHABLE_H
#define SDDS_PERISHABLE_H
#include "Item.h"

namespace sdds {
   class Perishable : public Item {
      char m_date[15]{}; //attribute for expiry date of perishable
   public:
      Perishable(char m_state = 'P');
      char itemType() const;  //return P

      //override all input and output functions of Base class
      ostream& write(ostream& Cout = cout) const;
      istream& read(istream& Cin = cin);
      ofstream& save(ofstream& writeToFile) const;
      ifstream& load(ifstream& readFromFile);
   };
}

#endif