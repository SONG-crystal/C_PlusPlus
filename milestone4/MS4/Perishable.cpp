#define _CRT_SECURE_NO_WARNINGS
#include "Perishable.h"
#include "Utils.h"

namespace sdds {
   Perishable::Perishable(char m_state) :Item(m_state)
   {
      m_state = itemType();
   }
   char Perishable::itemType() const
   {
      return 'P';
   }
   ostream& Perishable::write(ostream& Cout) const
   {
      Item::write();

      if (*this && Cout) {
         if (m_displayType == 1) { //POS_LIST
            Cout << "  ";
            Cout << m_date;
            Cout << " |";
            Cout << left;
         }
         else if (m_displayType == 2) { //POS_FORM
            Cout << "Expiry date: ";
            Cout << m_date;
            Cout << '\n';
            Cout << "=============^";
            Cout << '\n';
         }
      }

      return Cout;
   }
   istream& Perishable::read(istream& Cin)
   {
      Item::read();

      //If the object is in a good state and istream has seccess
      if (*this && Cin) { 
         char date[15]{};

         cout << "Expiry date (YYYY/MM/DD)" <<endl;
         cout << "> ";
         Cin.ignore();
         Cin.getline(date, 15, '\n');

         if (Cin) {
            strcpy(m_date,date);

         }
         else {
            m_ErrorState = nullptr;
         }
      }


      return Cin;
   }
   ofstream& Perishable::save(ofstream& writeToFile) const
   {
      Item::save(writeToFile);


      if (*this && writeToFile) {
         writeToFile << ",";
         writeToFile << m_date;
      }

      return writeToFile;
   }
   ifstream& Perishable::load(ifstream& readFromFile)
   {
      Item::load(readFromFile);

      //If the object is in a good state and istream has seccess
      if (*this && readFromFile) {
         char date[15]{};

         readFromFile.ignore(); //, Comma
         readFromFile.get(date, 11); //do not use getline!!!

         if (readFromFile) {
            strcpy(m_date, date);
            //cout << "Test!!  " << m_date;
         }
         else {
            m_ErrorState = nullptr;
         }
      }

      return readFromFile;
   }
}