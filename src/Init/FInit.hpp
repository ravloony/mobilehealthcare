#ifndef FINIT_HPP
#define FINIT_HPP

#include "../Init.hpp"


class FInit : public Init
{
  virtual Solution& execute(DataImporter* d, Solution& s, std::vector< Request* > requests);
};

#endif // FINIT_HPP
