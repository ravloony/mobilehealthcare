#ifndef MYDATAIMPORTER_HPP
#define MYDATAIMPORTER_HPP

#include <string.h>
#include <stdio.h>
#include <math.h>

#include "../DataImporter.hpp"


class MyDataImporter : public DataImporter
{
  private:
    int _num_days;
    std::string _conf_file;
    std::vector<pair<double, double> > _coords;
    std::vector<int> _ids;
    void make_client(string buffer);
    void make_nurse(string buffer);
    void make_request(string buffer);
  public:
    MyDataImporter();
    MyDataImporter(std::string filename);
    virtual ~MyDataImporter();
    virtual void print();
    virtual void plot();
    virtual void run();
    virtual int get_num_days();
};

#endif // MYDATAIMPORTER_HPP
