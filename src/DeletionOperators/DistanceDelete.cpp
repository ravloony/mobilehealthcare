#include "DistanceDelete.hpp"
#include <bits/stl_algo.h>

DistanceDelete::DistanceDelete()
{

}

DistanceDelete::DistanceDelete(int percentage): Delete(percentage)
{
}

bool sortfunction (std::pair< std::pair<int,int>, double > i, std::pair< std::pair<int,int>, double > j);

std::vector< Request* > DistanceDelete::execute(Solution& sol)
{
  vector<pair< pair<int,int>, double > > indexes;
  vector<Request*> removedRequests;
  _num_requests = (int)(((double)_percentage/100)*sol.get_number_of_requests());
//   cout << "There are " << sol.get_number_of_requests() << " requests, trying to remove " << _num_requests << " of them" << endl;
  //gather farthest vertices
  for (unsigned int i=0; i<sol.size(); i++)
  {
    for (int j=0; j<sol.size_of_route(i); j++)
    {
      pair<pair<int,int>, double> newpair(pair<int,int>(i,j),sol.get_sum_of_distances(i,j));
//       cout << "selected route " << newpair.first.first << ", vertex " << newpair.first.second << ", sum " << newpair.second;
      insertSorted(indexes,newpair);
//       cout << "...dealt with" << endl;
    }
  }
//   cout << "done" << endl;
//   cout << "vector of selected requests (size:" << indexes.size() << ") :" << endl;
//   for (unsigned int i=0; i<indexes.size(); i++)
//   {
//     cout << "route " << indexes[i].first.first << ", vertex " << indexes[i].first.second << ", sum " << indexes[i].second << endl;
//   }
  sort(indexes.begin(),indexes.end(),sortfunction);
  for (unsigned int j=indexes.size()-1; j>0;j--)
  {
//     cout << "("<<j<<") removing request " << indexes[j].first.second << " from route " << indexes[j].first.first << endl;
    removedRequests.push_back(sol.get_request(indexes[j].first.first,indexes[j].first.second));
    sol.erase(indexes[j].first.first,indexes[j].first.second);
  }
  sol.update_values();
  return removedRequests;
}

void DistanceDelete::insertSorted(std::vector<std::pair< std::pair<int,int>, double > >& vec, const std::pair< pair<int,int>, double > rpair)
{
  if (vec.size()==0)
  {
    vec.push_back(rpair);
//     cout << "...inserted first";
    return;
  }
  vector<pair<pair<int,int>,double> >::iterator it = vec.begin();
  int i=0;
  while((*it).second>rpair.second && it!=vec.end()&& i<=_num_requests)
  {
    it++;
    i++;
  }
  vec.insert(it,rpair);
  while ((int)vec.size()>(_num_requests))
    vec.pop_back();
}

bool sortfunction (pair< pair<int,int>, double > i, pair< pair<int,int>, double > j)
{
  return (i.first.second<j.first.second);
}


DistanceDelete::~DistanceDelete()
{

}
