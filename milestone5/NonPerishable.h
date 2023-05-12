#ifndef SDDS_NONPERISHABLE_H
#define SDDS_NONPERISHABLE_H
#include "Item.h"

namespace sdds {
   class NonPerishable : public Item {
   public:
      NonPerishable(char m_state = 'N');
      char itemType() const; //override pure virtual function, retrun N
      ostream& write(ostream& Cout = cout) const;

   };
}

#endif
