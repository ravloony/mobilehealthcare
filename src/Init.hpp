/*!
* \file Init.hpp
* \brief Mother class for all construction methods. Header file.
* \author Thomas Macdonald
* \date Thu Mar  4 14:29:00 CET 2010
*
* Class Init is the mother/meta class for all different initialisation methods. This class is not instanciable
*
*/

#ifndef INIT_H
#define INIT_H

#include <vector>
#include "Route.hpp"
#include "DataImporter.hpp"
#include "Solution.hpp"

using namespace std;

class Init {
protected:
    Init();
    vector<Request*> _uninserted_requests;
public:
    virtual ~Init();
    virtual Solution& execute(DataImporter* d, Solution& s, vector<Request*> requests) = 0;
    bool has_uninserted_requests();
    virtual vector<Request*>& get_uninserted_requests();
    void clear_uninserted_requests();
};

#endif // INIT_H
