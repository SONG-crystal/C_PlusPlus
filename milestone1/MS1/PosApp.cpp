#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include <iostream>
#include <iomanip> //setw
#include "PosApp.h"
#include "Utils.h"

using namespace std; //ifstream
namespace sdds
{  
   //***********************************Special Functions**********************************************
   PosApp::PosApp()
   {
      setEmpty();
   }
   PosApp::PosApp(const char* fileName)
   {
      setEmpty();
      setFileName(fileName);
   }


   PosApp::~PosApp() 
   {
      delete[] m_fileName;
   }

   //***********************************private Functions**********************************************
   PosApp& PosApp::setEmpty()
   {
      m_fileName = nullptr;
      return*this;
   }

   //**************************************************************************************************
   void PosApp::setFileName(const char* fileName)
   {
      delete[] m_fileName;
      m_fileName = new char[strlen(fileName) + 1];
      strcpy(m_fileName, fileName);
   }

   std::ostream& PosApp::display(std::ostream& ostr)
   {
      ostr << "The Sene-Store" << endl;
      ostr << "1- List items" << endl;
      ostr << "2- Add item" << endl;
      ostr << "3- Remove item" << endl;
      ostr << "4- Stock item" << endl;
      ostr << "5- Point of Sale" << endl;
      ostr << "0- exit program" << endl;
      ostr << "> ";

      menu();

      return ostr;
   }

   //***********************************Menu Functions**********************************************
   PosApp& PosApp::setLine()
   {
      cout << ">>>> ";
      cout.fill('.');
      cout << std::setw(72);
      return *this;
   }

   PosApp& PosApp::menu()
   {
      switch (U.getInt())  //m_util->getInt();
      {
      case 1: listItem();
         break;
      case 2: addItem();
         break;
      case 3: removeItem();
         break;
      case 4: stockItem();
         break;
      case 5: pointOfSale();
         break;
      case 0: exitProgram();
         break;
      default:
         break;
      }
      return *this;
   }

   PosApp& PosApp::run()
   {
      setLine();
      cout<< std::left << "Loading Items";
      cout << endl;
      cout << "Loading data from " << m_fileName<<endl;
      display();

      return* this;
   }

   PosApp& PosApp::listItem()
   {
      setLine();
      cout << std::left << "Listing Items";
      cout << endl;
      cout << "Running listItems()"<< endl;
      display();

      return*this;
   }

   PosApp& PosApp::addItem()
   {
      setLine();
      cout << std::left << "Adding Item to the store";
      cout << endl;
      cout << "Running addItem()" << endl;
      display();

      return*this;
   }

   PosApp& PosApp::removeItem()
   {
      setLine();
      cout << std::left << "Remove Item";
      cout << endl;
      cout << "Running removeItem()" << endl;
      display();

      return*this;
   }

   PosApp& PosApp::stockItem()
   {
      setLine();
      cout << std::left << "Select an item to stock";
      cout << endl;
      cout << "Running stockItem()" << endl;
      display();

      return*this;
   }

   PosApp& PosApp::pointOfSale()
   {
      setLine();
      cout << std::left << "Starting Point of Sale";
      cout << endl;
      cout << "Running POS()" << endl;
      display();

      return*this;
   }

   PosApp& PosApp::exitProgram()
   {
      setLine();
      cout << std::left << "Saving Data";
      cout << endl;
      cout << "Saving data in " << m_fileName <<endl;
      cout << "Goodbye!"<<endl;

      return *this;
   }

   PosApp::operator bool() const
   {
      return m_fileName != nullptr;
   }


}