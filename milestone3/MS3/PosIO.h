#ifndef SDDS_POSIO_H
#define SDDS_POSIO_H
#include <iostream>
#include <fstream>

using namespace std;
namespace sdds {

   class PosIO { //as an interface 

   public:
      virtual ostream& write(ostream& cout = cout) const =0; //This method does not modify its owner.
      virtual istream& read(istream& cin = cin) = 0;

      virtual ofstream& save(ofstream& writeToFile) const = 0;
      virtual ifstream& load(ifstream& readFromFile) = 0;

      //a virtual empty destructor.
      //virtual ~PosIO() {};

      //pure virtual destructor.
      virtual ~PosIO() = default;
   };
   ostream& operator<< (ostream& cout, const PosIO& P); //write
   istream& operator>> (istream& cin, PosIO& P);  //read

   ofstream& operator<< (ofstream& writeToFile, const PosIO& P);  //save
   ifstream& operator>> (ifstream& readFromFile, PosIO& P); //load
}

#endif