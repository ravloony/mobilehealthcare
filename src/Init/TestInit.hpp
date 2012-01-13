#ifndef TESTINIT_HPP
#define TESTINIT_HPP

#include "../Init.hpp"


class TestInit : public Init
{

  public:
    TestInit();
    virtual ~TestInit();
    virtual Solution& execute(DataImporter* d, Solution& s, vector<Request*> requests);
};

#endif // TESTINIT_HPP
