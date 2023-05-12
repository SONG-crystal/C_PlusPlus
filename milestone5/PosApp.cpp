#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include <iostream>
#include <iomanip> //setw
#include "PosApp.h"
#include "Utils.h"
#include "Perishable.h"
#include "NonPerishable.h"
#include "Bill.h"

using namespace std; 
namespace sdds
{
   PosApp::PosApp()
   {
      setEmpty();
   }
   PosApp::PosApp(const char fileName[])
   {
      setEmpty();
      setFileName(fileName);
   }
   void PosApp::setFileName(const char fileName[])
   {
      strcpy(m_fileName, fileName);
   }
   PosApp::operator bool() const
   {
      return m_fileName != nullptr;
   }
   PosApp::~PosApp()
   {
      for (int i = 0; i < MAX_NO_ITEMS; i++)
         delete m_Iptr[i]; //do not put [] this is single array
   }





   PosApp& PosApp::run()
   {
      loadRecs(); //sorting is in here
      strcpy(m_actionTitle, "Loading Items");
      menu();
      return *this;
   }

   PosApp& PosApp::menu()
   {
      bool ok = true;

      cout << ">>>> ";
      cout.fill('.');
      cout << std::setw(72);
      cout << std::left << m_actionTitle << endl;

      do {
         cout << "The Sene-Store" << endl;
         cout << "1- List items" << endl;
         cout << "2- Add item" << endl;
         cout << "3- Remove item" << endl;
         cout << "4- Stock item" << endl;
         cout << "5- POS" << endl;
         cout << "0- exit program" << endl;
         cout << "> ";

         m_actionTitle[0] = '\0';
         switch (U.getInt())
         {
         case 1: 
            listItems(); printTotalAsset();
            break;
         case 2: 
            strcpy(m_actionTitle, "Adding Item to the store"); addItem();
            break;
         case 3:
             removeItem();
            break;
         case 4: 
            stockItem();
            break;
         case 5:
            strcpy(m_actionTitle, "Starting Point of Sale"); POS();
            break;
         case 0:  
            strcpy(m_actionTitle, "Saving Data");   saveRecs();
            ok = false;
            break;
         default:
            break;
         }
      } while (ok);
      return *this;
   }

   PosApp& PosApp::listItems()
   {
      sort();

      strcpy(m_actionTitle, "Listing Items");
      cout << ">>>> ";
      cout.fill('.');
      cout << std::setw(72);
      cout << std::left << m_actionTitle << endl;

      cout << " Row | SKU    | Item Name          | Price |TX |Qty |   Total | Expiry Date |" << endl;
      cout << "-----|--------|--------------------|-------|---|----|---------|-------------|" << endl;

      for (int i = 0; i < m_nptr; i++) {
         m_Iptr[i]->displayType(POS_LIST);
         cout.fill(' ');
         cout.width(4);
         cout << std::right << i + 1 << " | ";
         m_Iptr[i]->write() << endl;
      }

      cout << "-----^--------^--------------------^-------^---^----^---------^-------------^" << endl;

      return *this;
   }

   PosApp& PosApp::addItem()
   {
      cout << ">>>> ";
      cout.fill('.');
      cout << std::setw(72);
      cout << std::left << m_actionTitle << endl;

      if (m_nptr == MAX_NO_ITEMS) {
         cout << "Inventroy Full!";
      }
      else {
         cout << "Is the Item perishable? (Y)es/(N)o: ";
        
         char oneChar{};
         cin >> oneChar;
         cin.ignore(100, '\n');

         if (cin) {

            if (oneChar == 'Y' || oneChar == 'y')
            {
               Item* newItem;
               newItem = new Perishable;
               cin >> *newItem;
               if (!cin) {
                  cin.clear();
                  cin.ignore(100, '\n');
                  //insert the item into cout?
                  cout << ", try again...\n";
               }
               else {
                  m_Iptr[m_nptr++] = newItem;

                  strcpy(m_actionTitle, "DONE!");
                  cout << ">>>> ";
                  cout.fill('.');
                  cout << std::setw(72);
                  cout << std::left << m_actionTitle << endl;
               }
            }
            else if (oneChar == 'N' || oneChar == 'n')
            {
               Item* newItem;
               newItem = new NonPerishable;
               cin >> *newItem;
               if (!cin) {
                  cin.clear();
                  cin.ignore(100, '\n');
                  //insert the item into cout?
                  cout << ", try again...\n";
               }
               else {
                  m_Iptr[m_nptr++] = newItem;

                  strcpy(m_actionTitle, "DONE!");
                  cout << ">>>> ";
                  cout.fill('.');
                  cout << std::setw(72);
                  cout << std::left << m_actionTitle << endl;
               }
            }
         }
      }
      return *this;
   }

   PosApp& PosApp::selectItem()
   {
      strcpy(m_actionTitle, "Item Selection by row number");
      cout << ">>>> ";
      cout.fill('.');
      cout << std::setw(72);
      cout << std::left << m_actionTitle << endl;
      cout << "Press <ENTER> to start....";
      cin.ignore(1000, '\n');

      listItems();

      return *this;
   }

   PosApp& PosApp::stockItem()
   {
      ofstream write(m_fileName);

      strcpy(m_actionTitle, "Select an item to stock");
      cout << ">>>> ";
      cout.fill('.');
      cout << std::setw(72);
      cout << std::left << m_actionTitle << endl;

      selectItem();

      bool flag = true;
      int index = 0;

      do {
         cout << "Enter the row number: ";
         index = U.getInt();

         if (U.getInt(1, 26, index)) {
            flag = false;
            m_Iptr[index - 1]->setIndex(index);
            m_Iptr[index - 1]->displayType(POS_FORM);
            cout << "Selected Item:" << endl;
            m_Iptr[index - 1]->write();
         }
      } while (flag);


      int Index = m_Iptr[index - 1]->getIndex();
      flag = true;
      do {
         cout << "Enter quantity to add: ";
         int addQuantity = U.getInt();

         if (U.getInt(1, 69, addQuantity)) {
            m_Iptr[Index - 1]->addQuantity(addQuantity);
            flag = false;

            strcpy(m_actionTitle, "DONE!");
            cout << ">>>> ";
            cout.fill('.');
            cout << std::setw(72);
            cout << std::left << m_actionTitle << endl;
         }
      } while (flag);


      return *this;
   }

   PosApp& PosApp::removeItem()
   {
      strcpy(m_actionTitle, "Remove Item");
      cout << ">>>> ";
      cout.fill('.');
      cout << std::setw(72);
      cout << std::left << m_actionTitle << endl;

      bool flag = true;
      selectItem();

      cout << "Enter the row number: ";
      int index = U.getInt();
      while (flag) {
         if (U.getInt(1, 26, index)) {
            cout << "Removing...." << endl;
            flag = false;

            m_Iptr[index - 1]->displayType(POS_FORM);
            m_Iptr[index - 1]->write();
         }
         else {
            cout << "Enter the row number: ";
            index = U.getInt();
         }
      }

      delete m_Iptr[index - 1];
      for (; index < m_nptr; index++) {
         m_Iptr[index - 1] = m_Iptr[index];
      }
      m_Iptr[m_nptr - 1] = nullptr;
      m_nptr--;

      strcpy(m_actionTitle, "DONE!");
      cout << ">>>> ";
      cout.fill('.');
      cout << std::setw(72);
      cout << std::left << m_actionTitle << endl;

      return *this;
   }

   PosApp& PosApp::POS()
   {
      cout << ">>>> ";
      cout.fill('.');
      cout << std::setw(72);
      cout << std::left << m_actionTitle << endl;



      bool done = true;
      char sku[MAX_SKU_LEN + 1]{};
      double total = 0;
      Item* item{};
      Bill bill{};
      do {
         cout << "Enter SKU or <ENTER> only to end sale..." << endl;
         cout << "> ";

         if (cin.peek() != '\n') 
         {
            cin >> sku;
            if (cin) //istream is good state, search the item
            { 
               cin.ignore(100, '\n');
               
               if (search(sku) == nullptr) 
               {
                  cout << "!!!!! Item Not Found !!!!!" << endl;
                  bill.clear();
                  done = false;
               }
               else 
               {
                  if (search(sku)->getQuantity()==0) 
                  {
                     cout << "Item out of stock" << endl;
                  }
                  else 
                  {
                     search(sku)->displayType(POS_FORM);

                     *search(sku) += -1;

                     search(sku)->write();

                     item = search(sku); //Move Name, SKU, Price, Taxed, Quantity
                     total += item->cost();
                     cout << endl;
                     cout << ">>>>> Added to bill" << endl;
                     cout << ">>>>> Total: ";
                     cout << total << endl;
                     
                     bill.add(item);
                  }
               }
            }
            else 
            {
               cin.clear();
               if (!done) cin.ignore(10000, '\n');
            }
         }
         else //press ENTER
         {
            bill.print(cout);
            done = true;
         }
      } while(!done);






      return *this;
   }
   
   PosApp& PosApp::printTotalAsset()
   {
      for (int i = 0; i < m_nptr; i++) 
         m_totalAsset += (m_Iptr[i]->cost() * m_Iptr[i]->quantity());

      cout << "                               Total Asset: $  |";
      cout.fill(' ');
      cout.width(14);
      cout << std::right << m_totalAsset << "|" << endl;
      cout << "-----------------------------------------------^--------------^" << endl << endl;

      return *this;
   }

   PosApp& PosApp::loadRecs(){

      ifstream input(m_fileName); //opening the file! "posdata.csv" ready for read

      if (!input) 
      {
         ofstream output; //creating the file
         output.open(m_fileName);
         output.close();
      }
      else 
      {
         //setEmpty(); //this made errors

         for (int i = 0; i < MAX_NO_ITEMS; i++) 
            m_Iptr[i] = nullptr;

         while (input && !input.eof() && m_nptr < MAX_NO_ITEMS)   //if input is in a good state, and Iptr array is not full
         {
            char oneChar{};
            input >> oneChar;
            input.ignore();

            if (input ) {

               if (oneChar == 'P')
               {
                  m_Iptr[m_nptr] = new Perishable;
                  input >> *(m_Iptr[m_nptr]);
               }
               else if (oneChar == 'N')
               {
                  m_Iptr[m_nptr] = new NonPerishable;
                  input >> *(m_Iptr[m_nptr]);
               }
               m_nptr++;
            }
         }
         input.close();
      }
      return *this;
    }

   PosApp& PosApp::saveRecs() {
      cout << ">>>> ";
      cout.fill('.');
      cout << std::setw(72);
      cout << std::left << m_actionTitle << endl;
      cout << "Goodbye!" << endl;

       ofstream output(m_fileName); 
    
       for (int i = 0; i < m_nptr; i++) 
          output << *m_Iptr[i] << endl; 

       output.close();

       return *this;
    }

   PosApp& PosApp::setEmpty()
   {
      m_fileName[0] = '\0';
      m_nptr = 0;
      m_actionTitle[0] = '\0';
      m_totalAsset = 0.0;
      return *this;
   }

   Item* PosApp::search(const char sku[]) const
   {
      bool match = false;
      Item* ptr = nullptr;

      for (int i = 0; i < m_nptr && !match; i++)
      {
         if (*m_Iptr[i] == sku) // if match the item (found)
         {
            match = true;
            ptr = m_Iptr[i];
         }
      }
      return ptr;
   }

   void PosApp::sort()
   {
      int i, j;
      Item* tempt{};

      for (i = m_nptr-1; i > 0; i--)
      {
         for (j = 0; j < i; j++)
         {
            if (*m_Iptr[j] > *m_Iptr[j + 1])  //call operator >
            {
               tempt = m_Iptr[j];
               m_Iptr[j] = m_Iptr[j + 1];
               m_Iptr[j + 1] = tempt;
            }
         }
      }
   }
}






