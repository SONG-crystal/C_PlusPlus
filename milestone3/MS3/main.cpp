///////////////////////////////////////////////////////////////////////////////////
// Name   : SuJung Song                                                          //
// ID     : 172745218                                                            //
// Email  : ssong49@myseneca.ca                                                  //
// Section: OOP244NDD                                                            //
//                                                                               //
//          I have done all the coding by myself and only copied the code that   //
//          my professor provided to complete my workshops and assignments.      //
///////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <fstream>
#include "Item.h"

using namespace sdds;
using namespace std;
class Tool :public Item {
public:
   char itemType()const {
      return 'T';
   }
};
void displayFile(const char* name) {
   ifstream file(name);
   char ch;
   cout << "<thefile>"; //write
   while(file.get(ch)) cout << ch;
   cout << "</thefile>" << endl;
}
Tool getTool() {
   Tool T;
   cout << "Please enter the Tool information: " << endl;
   cin >> T; //2. istream& operator>> read
   return T;
}


int main() {
   double sum{};
   Tool T[50];
   Tool M;
   int cnt{}, i;
   ifstream ifile("tools.csv"); //reading from file
   ofstream ofile("output.csv"); //wrting to file
   ifstream badFile("bad_tools.csv");
   while(ifile) {
      ifile.ignore(2); //T,
      ifile >> T[cnt]; //1. T[0],T[1],T[2],T[3]  //PosIO, ifstream& operator>> load
      ifile.ignore(1000, '\n');
      if(ifile) cnt++;
   }
   cout << "Enter the following:\n"
      " 1> 12345678\n"
      " 2> 1111\n"
      " 3> this is a very long name that exceeds "
      << MAX_NAME_LEN << " characters\n"
      " 4> Chisel\n"
      " 5> -1\n"
      " 6> abc\n"
      " 7> 10\n"
      " 8> abc\n"
      " 9> n\n"
      "10> abc\n"
      "11> 0\n"
      "12> " << MAX_STOCK_NUMBER + 1 << endl <<
      "13> 10\n";
   T[cnt++] = getTool(); //T[4] = T (user's)
   M = T[0];
   for(i = 0; i < cnt; i++) {
      T[i].displayType(POS_LIST);

      //3. ostream operator <<, write
      cout << T[i] << (T[i] == "3456" ? "<- Knife!" : "") << endl;
      if(M > T[i]) M = T[i];
      sum = sum += T[i];////////////////////
   }
   cout.setf(ios::fixed);
   cout.precision(2);
   cout << "Total price of all items: " << sum << endl;
   M.displayType(POS_FORM);
   cout << "First name in dictionary:" << endl << M << endl;
   sum = 0;
   for(i = 0; i < cnt; i++) {
      T[i].bprint(cout);
      sum += T[i].cost();//////////////////
   }
   cout << "Total cost: " << sum << endl;
   for(i = 0; i < cnt; i++) {
      cout << "qty: " << T[i].quantity() << endl;
      cout << "+=1: " << (T[i] += 1) << endl;
      cout << "-=2: " << (T[i] -= 2) << endl;
      cout << "------------------" << endl;
      ofile << T[i] << endl;
   }
   ofile.close();
   displayFile("output.csv");
   cnt = 1;
   while(badFile) {
      badFile.ignore(2);
      badFile >> M;
      badFile.ignore(1000, '\n');
      if(badFile) {
         M.displayType(POS_LIST);
         if(M)
            cout << M << endl; //errorState is 0
         else//errorState is 1 (error!)
            cout << "Record number " << cnt++ << " " << M << endl;
      }
   }
   return 0;
}
