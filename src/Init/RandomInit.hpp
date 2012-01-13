#ifndef RANDOMINIT_HPP
#define RANDOMINIT_HPP

#include "../Init.hpp"


class RandomInit : public Init
{

public:
    virtual Solution& execute(DataImporter* d, Solution& s, std::vector< Request*, std::allocator< Request* > > requests);
    RandomInit();
    virtual ~RandomInit();
};

#endif // RANDOMINIT_HPP
