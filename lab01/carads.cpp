// Workshop 1 
// Student Name  : SuJung Song 
// Student Number: 172745218
// Student Email : ssong49@myseneca.ca
// Submit Date   : May/19/2023
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <iomanip> //for setw
#include <cstring> 
#include <string> 
#include "carads.h"

double g_discount = 0.0;
double g_taxrate = 0.0;

using namespace std;
namespace sdds
{
   int listArgs(int argc, char* argv[])
   {
      cout << "Command Line:" << endl;
      cout << "--------------------------" << endl;

      for (int i = 0; i < argc; i++) {
         cout << "  "<<i + 1 << ": " << argv[i] << endl; 
      }
      cout << "--------------------------" << endl<<endl;
      return 0;
   }
   std::istream& operator>>(std::istream& is, Cars& car)
   {
      return car.read(is);
   }
   void operator>>(const Cars& car1, Cars& car2)
   {
      car2 = car1;
   }
   Cars::Cars()
   {

   }
   Cars::Cars(const Cars& Ro)
   {
      *this = Ro;
   }
   Cars& Cars::operator=(const Cars& Ro)
   {
      if (this != &Ro) {

         delete[] m_brand;
         m_brand = nullptr;

         if (Ro.m_brand != nullptr){
            m_brand = new char[strlen(Ro.m_brand) + 1];
            strcpy(m_brand, Ro.m_brand);

            strcpy(m_model, Ro.m_model);
            m_year = Ro.m_year;
            m_price = Ro.m_price;
            m_used = Ro.m_used;
            m_sale = Ro.m_sale;
            m_status= Ro.m_status;
         }
      }
      return *this;
   }
   Cars::~Cars()
   {
      delete[] m_brand;
   }
   std::istream& Cars::read(std::istream& is)
   {
      string tempBrand;

      delete[] m_brand;
      m_brand = nullptr;

      if (is) { //good state
         is >> m_used; 
         is.ignore();
         
         getline(is, tempBrand, ',');     
         m_brand = new char[tempBrand.length() + 1];
         strcpy(m_brand, tempBrand.c_str());

         is.getline(m_model, 15, ',');
         is >> m_year;
         is.ignore();
         is >> m_price;
         is.ignore();
         is >> m_status;
         is.ignore();
         if (m_status == 'Y') {
            m_sale = true;
         }
         else {
            m_sale = false;
         }
      }
      return is;
   }
   void Cars::display(bool reset) const
   {
      static int m_counter = 1; //do not use global

      if (reset) //if parameter is true, reset initial value
         m_counter = 1;
      
      if (m_model) {
         cout << left << setw(2)  << m_counter << ". ";
         cout << left << setw(10) << m_brand << "| ";
         cout << left << setw(15) << m_model << "| ";
         cout << left << setw(4)  << m_year << " |";
         cout << fixed;
         cout << right << setw(12) << setprecision(2) << m_price * (1+g_taxrate) << "|";
         if (m_sale)
            cout << right << setw(12) << m_price * (1 + g_taxrate) * (1-g_discount) << endl;
         else {
            cout << right << setw(2) << endl;
         }
         m_counter++;
      }
   }
   char Cars::getStatus() const {
      return m_used=='U' ?  'Y' : 'N';
   }
   Cars::operator bool() const
   {
      return m_used == 'N' ? true : false;
   }

}
