#include "NonPerishable.h"


namespace sdds {
   NonPerishable::NonPerishable(char m_state) :Item(m_state)
   {
      m_state = itemType();
   }
   char NonPerishable::itemType() const
   {
      return 'N';
   }
   ostream& NonPerishable::write(ostream& Cout) const
   {
      if (*this) {
         Item::write();
         if (m_displayType == 1) { //LIST
            Cout << "     N / A   |";
            Cout << left;
         }
         else if (m_displayType == 2) { //FORM
            cout << "=============^" << endl;
         }
      }
      //If the object is not in a good state, nothing extra is printed.
      return Cout;
   }

}
