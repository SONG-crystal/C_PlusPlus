///////////////////////////////////////////////////////////////////////////////////
// Final Project Milestone 1                                                     //
// Version 1.0                                                                   //
//                                                                               //
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

int main() {
   sdds::PosApp pos("datafile.csv");
   pos.run();
   return 0;
}
