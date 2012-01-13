/*!
* \file DistanceMatrix.hpp
* \brief Implements a Distance Matrix structure to abstract access to distances. Header file.
* \author Thomas Macdonald
* \date Thu Mar  4 14:29:25 CET 2010
*/
/**
* \file DistanceMatrix.hpp
* 
**/

#ifndef DISTANCEMATRIX_HPP
#define DISTANCEMATRIX_HPP
#include <map>
#include <vector>
#include <iostream>
#include <assert.h>


#include "../Error.hpp"

using namespace std;

class DistanceMatrix
{
  private:
    map<int,int> _translation;
    vector<vector<double> > _matrix;
  public:
    DistanceMatrix();
    DistanceMatrix(std::vector< int >& ids, std::vector< double >& dist);
    double getDistance(int from, int to);
    double getBigM();
    friend ostream& operator<< (ostream& stream, const DistanceMatrix d);
    double  operator() (unsigned int row, unsigned int col);
};
ostream& operator<< (ostream& stream, const DistanceMatrix d);
#endif // DISTANCEMATRIX_HPP
