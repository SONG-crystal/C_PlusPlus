#include "PosIO.h"

namespace sdds {
   ostream& operator<<(ostream& cout, const PosIO& P)
   {
      P.write(cout);
      return cout;
   }
   istream& operator>>(istream& cin, PosIO& P)
   {
      P.read(cin);
      return cin;
   }
   ofstream& operator<<(ofstream& writeToFile, const PosIO& P)
   {
      P.save(writeToFile);
      return writeToFile;
   }
   ifstream& operator>>(ifstream& readFromFile, PosIO& P)
   {
      P.load(readFromFile);
      return readFromFile;
   }



}
