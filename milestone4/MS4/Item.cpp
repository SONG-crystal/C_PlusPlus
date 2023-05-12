#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include <iomanip>
#include "Item.h"


namespace sdds {

   Item::Item()
   {
      clear();
   }

   Item::Item(char state)
   {
      clear();
      m_state = state;
   }

   Item::Item(const Item& I)
   {
      m_Name = nullptr;
      *this = I;
   }
   Item& Item::operator=(const Item& I) //getTool()
   {
      if (this != &I) {
         //clear();
         delete[] m_Name; //T[4](new) <- T(old)
         clear();

         if (I && (strlen(I.m_Name) <= MAX_NAME_LEN)) {
            m_Name = new char[strlen(I.m_Name) + 1];
            strcpy(m_Name, I.m_Name);
         }

         strcpy(m_SKU, I.m_SKU);
         m_Price = I.m_Price;
         m_Taxed = I.m_Taxed;
         m_Quantity = I.m_Quantity;
      }
      return *this;
   }
   Item::~Item()
   {
      delete[] m_Name;
   }


   //Returns the opposite of the status of the error attribute.
   Item::operator bool() const
   {
      return !bool(m_ErrorState);
   }

   bool Item::operator==(const char* rightValue) const
   {
      bool ok = true;
      unsigned int i;
      for (i = 0; i < strlen(rightValue); i++) {
         if (m_SKU[i] != rightValue[i]) {
            ok = false;
         }
      }
      return ok;
   }
   //A 65
   //B 66
   //a 97
   //b 98
   bool Item::operator>(const Item& rightItem) const
   {
      bool ok = true;

      if (m_Name[0] < rightItem.m_Name[0]) {
         ok = true;
      }
      else if (m_Name[0] == rightItem.m_Name[0]) {
         if (m_Name[1] < rightItem.m_Name[1]) {
            ok = true;
         }
      }

      return ok;
   }
   int Item::operator+=(const int value)
   {
      m_Quantity += value;
      if (m_Quantity > MAX_STOCK_NUMBER) {
         m_Quantity = MAX_STOCK_NUMBER;
         m_ErrorState = ERROR_POS_QTY;
      }
      return m_Quantity;
   }
   int Item::operator-=(const int value)
   {
      m_Quantity -= value;
      if (value > m_Quantity) {
         m_Quantity = 0;
         m_ErrorState = ERROR_POS_STOCK;
      }
      return m_Quantity;
   }

   //Receives an integer (POS_LIST or POS_FORM) and sets the corresponding attribute. 
   //This method returns the reference of the current object.
   Item& Item::displayType(int flag)
   {
      if (flag == POS_LIST) {
         m_displayType = 1;
      }
      else if (flag == POS_FORM) {
         m_displayType = 2;
      }
      return *this;
   }
   double Item::cost() const
   {
      return m_Taxed ? (m_Price * (1 + TAX)) : m_Price;
      //return m_Taxed ? (m_Price *(1+TAX))*m_Quantity : m_Price * m_Quantity;
   }
   int Item::quantity() const
   {
      return m_Quantity;
   }
   Item& Item::clear()
   {
      m_SKU[0] = '\0';
      m_Name = nullptr;
      m_Price = 0.0;
      m_Taxed = false;
      m_Quantity = 0;
      m_displayType = 0; //1 or 2? which one is the empty state?
      //Error m_ErrorState; //let's set empty Error class
      m_ErrorState.clear();

      return *this;
   }

   bool Item::fetchTaxed() const
   {
      return m_Taxed;
   }





   ostream& Item::write(ostream& Cout) const
   {
      if (m_ErrorState)
      {
         m_ErrorState.display();
      }
      else
      {
         if (m_displayType == 1)
         { // POS_LIST mode

            Cout << std::setfill(' ') << std::setw(7);
            Cout << std::left << m_SKU;
            Cout << "|";
            char temp[61];
            Cout.fill(' ');
            Cout.width(20);
            if (strlen(m_Name) > 20) {
               strcpy(temp, m_Name);
               temp[20] = '\0';
               Cout << temp;
            }
            else {
               Cout << m_Name;
            }
            Cout << "|";


            Cout.setf(ios::fixed);
            Cout.precision(2);
            Cout.fill(' ');
            Cout.width(7);
            Cout << std::right << m_Price;
            Cout << "|";

            if (m_Taxed) {
               Cout << " X |"; //taxable
            }
            else {
               Cout << "   |";
            }


            Cout.fill(' ');
            Cout.width(4);
            Cout << std::right << m_Quantity;
            Cout << "|";

            if (m_Taxed) {
               Cout.fill(' ');
               Cout.width(9);
               Cout << std::right << m_Price * (1 + TAX) * m_Quantity;
               Cout << "|";
            }
            else {
               Cout.fill(' ');
               Cout.width(9);
               Cout << std::right << m_Price * m_Quantity;
               Cout << "|";
            }
         }
         else if (m_displayType == 2)
         { //POS_FORM
            Cout << "=============v" << endl;

            Cout.fill(' ');
            Cout.width(13);
            Cout << std::left << "Name: " << m_Name << endl;

            Cout.fill(' ');
            Cout.width(13);
            Cout << std::left << "Sku: " << m_SKU << endl;

            Cout.fill(' ');
            Cout.width(13);
            Cout << std::left << "Price: " << m_Price << endl;

            Cout.fill(' ');
            Cout.width(13);
            if (m_Taxed) {
               Cout << std::left << "Price + tax: " << m_Price * (1+TAX) << endl;
            }
            else {
               Cout << std::left << "Price + tax: " << "N/A" << endl;
            }

            Cout.fill(' ');
            Cout.width(13);
            Cout << std::left << "Stock Qty: " << m_Quantity << endl;
         }
      }


      return Cout;
   }

   istream& Item::read(istream& Cin)
   {
      bool ok = 1;
      char sku[101];
      char name[101];
      double price = 0.0;
      char tax;
      int quantity;

      cout << "Sku" << endl;
      do {
         cout << "> ";
         Cin >> sku;
         if (Cin) {
            if (strlen(sku) > MAX_SKU_LEN) {
               cout << ERROR_POS_SKU << endl;
            }
            else {
               strcpy(m_SKU, sku);
               ok = 0;
            }
         }
         else {
            cout << ERROR_POS_SKU << endl;
            Cin.clear();
         }
      } while (ok);
      Cin.ignore(200, '\n');
      //cout << m_SKU << "TEST" << endl;

      ok = 1;
      cout << "Name" << endl;
      do {
         cout << "> ";
         Cin.getline(name, 100, '\n');

         if (Cin) {
            if (strlen(name) > MAX_NAME_LEN) {
               cout << ERROR_POS_NAME << endl;
            }
            else {
               //delete[]m_Name;  //newly created it
               m_Name = nullptr;
               m_Name = new char[strlen(name) + 1];
               strcpy(m_Name, name);
               ok = 0;
            }
         }
         else {
            cout << ERROR_POS_NAME << endl;
            Cin.clear();
         }
      } while (ok);


      ok = 1;
      cout << "Price" << endl;
      do {
         cout << "> ";
         Cin >> price; //-1입력하면 -1.0입력됨
         if (Cin) {
            if (price > -1.0) {
               m_Price = price;
               ok = 0;
            }
            else {
               cout << ERROR_POS_PRICE << endl;
            }
         }
         else {
            cout << ERROR_POS_PRICE << endl;
            Cin.clear();
            Cin.ignore(200, '\n');
         }
      } while (ok);


      ok = 1;
      cout << "Taxed?" << endl;
      cout << "(Y)es/(N)o: ";
      do {
         Cin >> tax;
         if (Cin) {

            if (tax == 'y' || tax == 'Y')
            {
               m_Taxed = 1;
               ok = 0;
            }
            else if (tax == 'n' || tax == 'N')
            {
               m_Taxed = 0;
               ok = 0;
            }
            else
            {
               cout << "Only 'y' and 'n' are acceptable: ";
               Cin.ignore(200, '\n');
            }
         }
         else {
            cout << ERROR_POS_TAX << endl;
         }
      } while (ok);


      ok = 1;
      cout << "Quantity" << endl;
      do {
         cout << "> ";
         Cin >> quantity;
         if (Cin) {
            if (quantity > 0 && quantity <= MAX_STOCK_NUMBER) {
               m_Quantity = quantity;
               ok = 0;
            }
            else {
               cout << ERROR_POS_QTY << endl;
            }
         }
         else {
            cout << ERROR_POS_QTY << endl;
            Cin.clear();
            Cin.ignore(200, '\n');
         }
      } while (ok);

      return Cin;
   }

   ofstream& Item::save(ofstream& writeToFile) const
   {
      if (m_Name != nullptr) {
         writeToFile << m_state << ",";
         writeToFile << m_SKU << ",";
         writeToFile << m_Name << ",";


         writeToFile.setf(ios::fixed);
         writeToFile.precision(2);
         writeToFile << m_Price << ",";


         writeToFile << m_Taxed << ",";
         writeToFile << m_Quantity;
      }
      else {
         writeToFile << "not valid" << endl;
      }

      return writeToFile;
   }

   ifstream& Item::load(ifstream& readFromFile)
   {
      char t_SKU[101];
      char t_Name[101];
      double t_Price;
      bool t_Taxed;
      int t_Quantity;

      //the error status will be cleared
      //readFromFile.clear();
      m_ErrorState.clear();



      readFromFile.getline(t_SKU, 100, ',');
      if (readFromFile) {
         if (strlen(t_SKU) < MAX_SKU_LEN) {
            strcpy(m_SKU, t_SKU);

            readFromFile.getline(t_Name, 100, ',');
            if (readFromFile) {
               if (strlen(t_Name) < MAX_NAME_LEN) {
                  delete[] m_Name;
                  m_Name = new char[strlen(t_Name) + 1];
                  strcpy(m_Name, t_Name);

                  readFromFile >> t_Price;
                  readFromFile.ignore();
                  if (readFromFile) {
                     if (t_Price > -1.0) {
                        m_Price = t_Price;

                        readFromFile >> t_Taxed;
                        readFromFile.ignore();
                        if (readFromFile) {
                           if (t_Taxed == 1 || t_Taxed == 0) {
                              m_Taxed = t_Taxed;

                              readFromFile >> t_Quantity;
                              //readFromFile.ignore(); //do not use
                              if (readFromFile) {
                                 if (t_Quantity > 0 && t_Quantity <= MAX_STOCK_NUMBER) {
                                    m_Quantity = t_Quantity;
                                 }
                                 else {
                                    m_ErrorState.setPointer(ERROR_POS_QTY);
                                 }
                              }
                           }
                           else {
                              m_ErrorState.setPointer(ERROR_POS_TAX);
                           }
                        }
                     }
                     else {
                        m_ErrorState.setPointer(ERROR_POS_PRICE);
                     }
                  }
               }
               else {
                  m_ErrorState.setPointer(ERROR_POS_NAME);
               }
            }
         }
         else {
            m_ErrorState.setPointer(ERROR_POS_SKU);
         }
      }
 
      return readFromFile;
   }








   ostream& Item::bprint(ostream& Cout) const
   {


      Cout << "| ";
      char temp[61];
      Cout.fill(' ');
      Cout.width(20);
      if (strlen(m_Name) > 20) {
         strcpy(temp, m_Name);
         temp[20] = '\0';

         Cout << std::left << temp;
      }
      else {
         Cout << std::left << m_Name;
      }
      Cout << "|";

      Cout.fill(' ');
      Cout.width(10);
      if (m_Taxed) {
         Cout << std::right << m_Price * (1 + TAX) << " |";
         Cout << "  T  |";
      }
      else {
         Cout << std::right << m_Price << " |";
         Cout << "     |";
      }
      Cout << endl;
      return Cout;
   }

   double operator+=(double& value, const Item& rightItem)
   {
      if (rightItem.fetchTaxed()) {
         value += (rightItem.cost() * rightItem.quantity());
      }
      else {
         value += rightItem.cost() * rightItem.quantity();
      }

      return value;
   }
}