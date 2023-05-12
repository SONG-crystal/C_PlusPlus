///////////////////////////////////////////////////////////////////////////////////
// Name   : SuJung Song                                                          //
// ID     : 172745218                                                            //
// Email  : ssong49@myseneca.ca                                                  //
// Section: OOP244NDD                                                            //
//                                                                               //
//          I have done all the coding by myself and only copied the code that   //
//          my professor provided to complete my workshops and assignments.      //
///////////////////////////////////////////////////////////////////////////////////
#include <fstream>
#include <iostream>
#include "PosApp.h"

void resetDataFile();
void displayfileContent();

int main() {
   resetDataFile();
   displayfileContent();
   sdds::PosApp pos("posdata.csv");
   pos.run();
   displayfileContent();
   return 0;
}

void resetDataFile() {
   char ch{};
   std::ofstream outfile("posdata.csv"); //writeToFile
   std::ifstream infile("posdataOrigin.csv");  //readFromFile
   while (infile.get(ch)) {
      outfile.put(ch);
   }
}

void displayfileContent() {
   std::cout << "Data file:\n------------------\n";
   char ch{};
   std::ifstream infile("posdata.csv"); //readFromFile
   while (infile.get(ch)) {
      std::cout.put(ch);
   }
   std::cout << "------------------\n";
}