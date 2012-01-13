#ifndef FDATAIMPORTER_HPP
#define FDATAIMPORTER_HPP

#include "../DataImporter.hpp"


class FDataImporter : public DataImporter
{
  private:
    int _num_days;
  public:
    FDataImporter();
    virtual ~FDataImporter();
    virtual void print();
    virtual void plot();
    virtual void run();
    virtual int get_num_days() {return _num_days;}
//     virtual ~DataImporter();
};

#endif // FDATAIMPORTER_HPP
