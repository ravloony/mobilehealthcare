#ifndef DISTANCEDELETE_HPP
#define DISTANCEDELETE_HPP

#include "Delete.hpp"


class DistanceDelete : public Delete
{
  private:
    int _num_requests;
    void insertSorted(std::vector< std::pair< std::pair< int, int >, double > >& vec, const std::pair< std::pair< int, int >, double > rpair);
  public:
    DistanceDelete();
    DistanceDelete(int percentage);
    virtual std::vector< Request* > execute(Solution& sol);
    ~DistanceDelete();
};

#endif // DISTANCEDELETE_HPP
