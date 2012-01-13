#ifndef STATISTICS_HPP
#define STATISTICS_HPP
#include "../Solution.hpp"

class Statistics
{
  friend std::ostream& operator<<(std::ostream& stream, const Statistics& stat);
  private:
    Solution _after_init;
    Solution _after_meta;
    int _no_of_requests;
    int _no_of_clients;
    int _no_of_nurses;
  public:
    Statistics();
    Statistics(int nOfRequests, int nOfClients, int nOfNurses);
    void add_after_init(Solution& sol);
    void add_final(Solution& sol);
//     Statistics(const Statistics& stat);
    void print_latex();
    virtual ~Statistics();
};

#endif // STATISTICS_HPP
