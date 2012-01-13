/*!
* \file RegretInit.hpp
* \brief Regret construction Heuristic header file.
* \author Thomas Macdonald
* \date Thu Mar  4 14:29:32 CET 2010
* 
* 
*
*/

#ifndef REGRETINIT_HPP
#define REGRETINIT_HPP

#include <assert.h>
#include <float.h>

#include "../Init.hpp"
#include "../Useful.hpp"
#include "../DataStructures/Requestcache.hpp"

using namespace std;

/*!
*	\class RegretInit
*	\brief Initialisation algorithm implementing the regret method from Potvin & Rousseau (1993).
*
*	Basically, this algorithm produces a vector of Routes in the following fashion: For each request, for each route, the best insertion cost is decided. The regret for a request is the difference between the insertion costs between the two routes with the best insertion costs. The request with the highest regret is then chosen to be inserted (in the best position) and the process is repeated until all requests are served. An infeasible insertion is given a large value (big M).
*/
class RegretInit : public Init
{
  private:
    double _max_cost;
    vector<Route> _routes;
    map<int,Requestcache> _costmap;
    int cantorPair(int x, int y);
  public:
    RegretInit(); ///< Constructor
    ~RegretInit(); ///< Destructor
    Solution& execute(DataImporter* d, Solution& s, std::vector< Request* > requests); ///< main algorithm
    friend ostream& operator<< (ostream& stream, const RegretInit r);
};
ostream& operator<< (ostream& stream, const RegretInit r);

#endif // REGRETINIT_HPP
