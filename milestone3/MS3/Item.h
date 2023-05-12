#ifndef SDDS_ITEM_H
#define SDDS_ITEM_H
#include "POS.h"
#include "PosIO.h"
#include "Error.h"

using namespace std;
namespace sdds {

   class Item:public PosIO {

      char m_SKU[MAX_SKU_LEN];
      char* m_Name; // upto [MAX_NAME_LEN] ;
      double m_Price;
      bool m_Taxed; //if the Item is taxable(1) or not(0).
      int m_Quantity; //number of items


   protected:
      int m_displayType; //either POS_LIST(1) or POS_FORM(2)
      Error m_ErrorState; //Invoke MS2's Error class

   public:
      Item();

      Item (const Item& I);
      Item& operator= (const Item& I);
      ~Item();

      operator bool() const;
      bool operator==(const char* rightValue) const;
      bool operator>(const Item& rightItem) const;
      int operator+=(const int value);
      int operator-=(const int value);

      Item& displayType(int flag);
      double cost() const;  //return price + Tax
      int quantity() const; //return m_Quantity
      Item& clear();
      bool fetchTaxed() const;

      //implement four pure virtual methods of the base class
      ostream& write(ostream& Cout = cout) const; 
      istream& read(istream& Cin = cin);
      ofstream& save(ofstream& writeToFile) const;
      ifstream& load(ifstream& readFromFile);

      ostream& bprint(ostream& Cout = cout) const;
   };
   double operator+=(double& value, const Item& rightItem);
}

#endif