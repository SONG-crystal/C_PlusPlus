#include <iomanip>
#include "Dictionary.h"

namespace sdds {

   Dictionary::Dictionary() {}

   std::ostream& Dictionary::display(std::ostream& os) const{
      return os << std::setw(20) << getTerm() << ": " << getDefinition();
   }

   bool Dictionary::operator==(const Dictionary& dic)
   {
      return dic.m_term == m_term;
   }

   std::ostream& operator<<(std::ostream& os, const Dictionary& dic) {
      dic.display();
      return os;
   }
}