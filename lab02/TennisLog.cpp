#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <iomanip>
#include "TennisLog.h"


using namespace std;

namespace sdds {
   std::ostream& operator<<(std::ostream& os, const TennisMatch& match)
   {
      if (match.m_id.empty()) //string, empty()
         os << "Empty Match";
      else {
         os.fill('.');
         os << right << setw(23) << "Tourney ID : ";
         os << left << setw(30) << match.m_id << endl;

         os << right << setw(23) << "Match ID : ";
         os << left << setw(30) << match.m_matchId << endl;

         os << right << setw(23) << "Tourney : ";
         os << left << setw(30) << match.m_name << endl;

         os << right << setw(23) << "Winner : ";
         os << left << setw(30) << match.m_winner << endl;

         os << right << setw(23) << "Loser : ";
         os << left << setw(30) << match.m_loser << endl;
      }
      return os;
   }

   TennisLog::TennisLog()
   {
   }
   TennisLog::~TennisLog()
   {
      delete[] m_matched;
   }
   TennisLog::TennisLog(const char* fileName)
   {
      string temp{};
      ifstream read(fileName);

      if (read) {
         read.ignore(1000, '\n');

         while (read) {
            getline(read, temp, '\n');
            m_count++;
         }

         read.clear(); //rewind file pointer
         read.seekg(0); //closed and open again
         
         read.ignore(1000, '\n');

         m_matched = new TennisMatch[m_count]; //pointing: csv file's total game number
         for (size_t i = 0; i < m_count; i++) {
            getline(read, m_matched[i].m_id, ',');
            getline(read, m_matched[i].m_name, ',');
            //getline(read, m_matched[i].m_matchId, ','); can not use it
            read >> m_matched[i].m_matchId;
            read.ignore();
            getline(read, m_matched[i].m_winner, ',');
            getline(read, m_matched[i].m_loser); //','
         }
         m_count--; //needed
      }
   }

   TennisLog::TennisLog(const TennisLog& log)
   {
      *this = log;
   }

   TennisLog::TennisLog(TennisLog&& log)
   {
      *this = std::move(log);
   }

   TennisLog& TennisLog::operator=(const TennisLog& log)
   {
      if (this != &log) {
         delete[] m_matched;
         m_matched = nullptr;

         if (log) {
            m_matched = new TennisMatch[log.m_count];
            for (size_t i = 0; i < log.m_count; i++) { 
              m_matched[i] = log.m_matched[i];
            }
            //strcpy(m_matched, log.m_matched);
            m_count = log.m_count;
         }
      }
      return *this;
   }

   TennisLog& TennisLog::operator=(TennisLog&& log)
   {
      if (this != &log) {
         delete[] m_matched;

         m_matched = log.m_matched;
         log.m_matched = nullptr;

         m_count = log.m_count;
         log.m_count = 0;
      }
      return *this;
   }


   void TennisLog::addMatch(const TennisMatch& match)
   {
      TennisMatch* temp = new TennisMatch[m_count+1];
      for (size_t i = 0; i < m_count; i++) {
         temp[i] = m_matched[i];
      }
      temp[m_count] = match;
      delete[] m_matched;
      m_matched = temp;
      m_count++;
   }



   TennisLog TennisLog::findMatches(const std::string& playerName) const
   {
      TennisLog tennislog;

      for (size_t i = 0; i < m_count; i++) {
         if (m_matched[i].m_winner == playerName || m_matched[i].m_loser == playerName) {
            //cout << i << ". winner " << m_matched[i].m_winner << endl;
            //cout << i << ". loser " << m_matched[i].m_loser << endl;
            //cout << "playerName: "<< playerName << endl;
            tennislog.addMatch(m_matched[i]);
         }
      }
      return tennislog;
   }

   TennisMatch TennisLog::operator[](size_t index) const
   {
      TennisMatch empty;
      return m_count > 0 ? m_matched[index] : empty;
   }
   TennisLog::operator size_t() const
   {
      return (size_t)m_count;
   }
}