#ifndef SDDS_ITEM_H
#define SDDS_ITEM_H
#include "POS.h"
#include "PosIO.h"
#include "Error.h"

using namespace std;
namespace sdds {

   class Item :public PosIO {

      char m_SKU[MAX_SKU_LEN];
      char* m_Name; // upto [MAX_NAME_LEN] ;
      double m_Price;
      bool m_Taxed; //if the Item is taxable(1) or not(0).
      int m_Quantity; //number of items
      char m_state;
      int m_index; 

   protected:
      int m_displayType; //either POS_LIST(1) or POS_FORM(2)
      Error m_ErrorState; //Invoke MS2's Error class


   public:
      Item();
      Item(char state);
      Item(const Item& I);
      Item& operator= (const Item& I);
      virtual ~Item();

      operator bool() const;
      bool operator==(const char* rightValue) const;
      bool operator>(const Item& rightItem) const;
      int operator+=(const int value);
      int operator-=(const int value);

      Item& displayType(int flag);
      double cost() const;  //return price + Tax
      int quantity() const; //return m_Quantity
      Item& addQuantity(int value);
      Item& clear();
      bool fetchTaxed() const;

      //implement four pure virtual methods of the base class
      virtual ostream& write(ostream& Cout = cout) const;
      virtual istream& read(istream& Cin = cin);
      virtual ofstream& save(ofstream& writeToFile) const;
      virtual ifstream& load(ifstream& readFromFile);

      ostream& bprint(ostream& Cout = cout) const; //Name and price

      virtual char itemType() const = 0;
      int setIndex(int value);
      int getIndex();
      char* getSKU();
      double getQuantity();

      
   };
   double operator+=(double& value, const Item& rightItem);

   
}

#endif