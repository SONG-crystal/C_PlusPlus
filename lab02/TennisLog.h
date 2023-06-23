#ifndef SDDS_TENNISLOG_H
#define SDDS_TENNISLOG_H


namespace sdds {

   struct TennisMatch {
      std::string m_id{};
      std::string m_name{};
      size_t m_matchId{};
      std::string m_winner{};
      std::string m_loser{};
   };
   std::ostream& operator<<(std::ostream& os, const TennisMatch& match);


   class TennisLog {
      TennisMatch* m_matched{};
      size_t m_count{};
   public:
      TennisLog();
      TennisLog(const char* fileName);

      TennisLog(const TennisLog& log);
      TennisLog(TennisLog&& log);
      TennisLog& operator=(const TennisLog& log);
      TennisLog& operator=(TennisLog&& log);
      virtual ~TennisLog();

      void addMatch(const TennisMatch& match);
      TennisLog findMatches(const std::string& playerName) const;
      TennisMatch operator[](size_t index) const;
      operator size_t() const;
   };

}

#endif
