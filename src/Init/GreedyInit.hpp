#ifndef GREEDYINIT_HPP
#define GREEDYINIT_HPP

#include "../Init.hpp"


class GreedyInit : public Init
{
  public:
    GreedyInit();
    virtual ~GreedyInit();
    virtual Solution& execute(DataImporter* d, Solution& s, std::vector< Request* > requests);
};

#endif // GREEDYINIT_HPP
