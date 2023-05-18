#ifndef SDDS_CARADS_H
#define SDDS_CARADS_H

//Global Variables
//will be accessed and and be changed from main function
extern double g_taxrate;
extern double g_discount;

namespace sdds
{
   int listArgs(int argc, char* argv[]);

   class Cars {
      char* m_brand{};
      char m_model[15]{};
      int m_year{};
      double m_price{};
      char m_used{};
      bool m_sale{};
      char m_status{};

   public:
      Cars(); 
      
      Cars(const Cars& Ro);
      Cars& operator=(const Cars& Ro);
      virtual ~Cars();

      std::istream& read(std::istream& is = std::cin);
      void display(bool reset) const;
      char getStatus() const;
      operator bool() const;
   };

   //Global function
   std::istream& operator>>(std::istream& is, Cars& car);
   void operator>>(const Cars& car1, Cars& car2);
}

#endif
