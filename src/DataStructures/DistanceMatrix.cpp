/*!
* \file DistanceMatrix.cpp
* \brief 
* \author Thomas Macdonald
* \date Thu Mar  4 14:29:25 CET 2010
*/
/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) <year>  <name of author>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

*/

#include <math.h>

#include "DistanceMatrix.hpp"
using namespace std;

DistanceMatrix::DistanceMatrix()
{

}

DistanceMatrix::DistanceMatrix (vector< int >& ids, vector< double >& dist )
{
  unsigned int size = dist.size();
  vector<double> tmprow;
  for (unsigned int i=0; i<size; i++)
  {
    if (i<ids.size())
      _translation.insert(pair<int,int>(ids[i],i));
    tmprow.push_back(dist[i]);
    if ((i+1)%(int)sqrt(dist.size())==0)
    { //if we reach the end of a row
      _matrix.push_back(tmprow);
      tmprow.clear();
    }
  }
  int square = ids.size()*ids.size();
  cout << "Distance Matrix file read. Got " << dist.size() << " distances. ("<< ids.size() << "*"<< ids.size() << "=" << square << ")" << endl;
}

double DistanceMatrix::getDistance ( int from, int to )
{
//   cout << "size of matrix : " << _translation.size() << ", from : " << from << " (" << _translation[from] << "), to : " << to << " (" << _translation[to] << ")" << endl;
//   assert(from<_translation.size() && to<_translation.size());
  return _matrix[_translation[from]][_translation[to]];
}

ostream& operator<<(ostream& stream, const DistanceMatrix d)
{
  stream << "  | ";
  for (unsigned int i=0; i<d._matrix.size(); i++)
  {
    stream << i << "\t\t";
  }
  stream << endl;
  for (unsigned int i=0; i<d._matrix.size(); i++)
  {
    stream << i << " | ";
    for (unsigned int j=0; j<d._matrix[i].size();j++)
    {
      stream << d._matrix[i][j] << "\t\t";
    }
    stream << endl;
  }
  return stream;
}

double DistanceMatrix::operator()(unsigned int row, unsigned int col)
{
  return getDistance(row,col);
}


double DistanceMatrix::getBigM()
{
  double tmpMax=0;
  for (unsigned int i = 0; i<_matrix.size();i++)
  {
    for (unsigned int j = 0; j<_matrix[i].size(); j++)
    {
      if (tmpMax<_matrix[i][j])
	tmpMax=_matrix[i][j];
    }
  }
  return (double)(2*tmpMax+2000);
}


