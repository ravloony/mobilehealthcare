/*!
* \file DataImporter.hpp
* \brief Data Importer Mother class header file.
* \author Thomas Macdonald
* \date Thu Mar  4 14:29:00 CET 2010
*/

#ifndef DATAIMPORTER_HPP
#define DATAIMPORTER_HPP

#include "DataStructures/DistanceMatrix.hpp"
#include "Output/Plot.hpp"
#include "Client.hpp"
#include "Nurse.hpp"
#include "Request.hpp"

using namespace std;

class DataImporter
{
  protected:
    vector<Client*> _clients;
    vector<Request*> _requests;
    vector<Nurse*> _nurses;
    DistanceMatrix* _distance_matrix;
    DataImporter() {}
  public:
    virtual ~DataImporter() =0;
    vector<Client*>& get_clients() { return _clients; }
    vector<Request*>& get_requests(){return _requests; }
    vector<Nurse*>& get_nurses() { return _nurses; }
    DistanceMatrix* get_distance_matrix() { return _distance_matrix; }
    virtual int get_num_days() = 0;
    virtual void run() = 0;
    virtual void plot() = 0;
    virtual void print()=0;
};
ostream& operator<< (ostream& stream, DataImporter& d);
#endif // DATAIMPORTER_HPP
