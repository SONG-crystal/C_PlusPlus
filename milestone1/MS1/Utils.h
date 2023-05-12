#ifndef SDDS_UTILS_H_
#define SDDS_UTILS_H_
namespace sdds
{
   class Utils {
   public:
      void flushkeys();
      int getInt();
      int getInt(int min, int max, int value);

   };

   extern Utils U; //this prototype
                   //extern make a filescope variable global




}
#endif