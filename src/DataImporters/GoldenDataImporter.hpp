/*!
* \file GoldenDataImporter.hpp
* \brief imports data from Bruce Golden's test samples
* \author Thomas Macdonald
* \date Thu Mar  4 14:29:15 CET 2010
*/

#ifndef GOLDENDATAIMPORTER_HPP
#define GOLDENDATAIMPORTER_HPP

#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "../DataImporter.hpp"
#include "../Useful.hpp"

using namespace std;
class GoldenDataImporter : public DataImporter
{
  private:
    string _confFile;
    string _name;
    string _type;
    string _comment;
    int _dim;
    int _num_days;
    int _capacity;
    int _distance;
    string _edge_weight_type;
    string _edge_weight_format;
    string _node_coord_type;
    vector<pair<double, double> > _coords;
    vector<vector<int> > _demands;
    vector<vector<double> > _svc_times;
    pair<double,double> _depot_coords;
    double _depot_other;
    vector<vector<int> > _time_windows;
    vector<vector<int> > _skills;
  public:
    GoldenDataImporter();
    GoldenDataImporter(string confFile) : _confFile(confFile) {}
    int get_num_days() { return _num_days;}
    virtual void run();
    virtual void plot();
    virtual ~GoldenDataImporter();
    virtual void print();
};
#endif // GOLDENDATAIMPORTER_HPP
