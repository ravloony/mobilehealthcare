#include "RandomInit.hpp"

Solution& RandomInit::execute(DataImporter* d, Solution& s, std::vector< Request*, std::allocator< Request* > > requests)
{
/*  cout << "Random insert" << endl;
  cout << "there are " << requests.size() << " requests...";*/
  cout.flush();
  double bigM = d->get_distance_matrix()->getBigM()*10;
  vector<int> eligibleRoutes;
  for (unsigned int i=0; i<requests.size(); i++)
  {
    Request* r = requests[i];
    
    for (unsigned int k=0; k<s.size();k++)
      if (s.check_skills(r,k) && s.check_day(r,k))
	eligibleRoutes.push_back(k);
    int index = rand()%eligibleRoutes.size();
    int route = eligibleRoutes[index];

    bool found=false;
    while (!found) {
//       cout << "trying route " << route << "...";
//       cout.flush();
      double bestCost=bigM;
      int bestPos;
      for (unsigned int pos=0; pos<=s.size_of_route(route); pos++)
      {
	if (s.insertionPossible(r,route,pos))
	{
	  double currentCost = s.getInsertionCost(r,route,pos);
	  if (currentCost<bestCost)
	  {
	    bestCost=currentCost;
	    bestPos=pos;
	  }
	  found=true;
	  break;
	}
      }
      if (!found)
      {
	eligibleRoutes.erase(eligibleRoutes.begin()+index);
	if (eligibleRoutes.size()==0)
	{
	  _uninserted_requests.push_back(r);
	  found=true;
	} else {
	  index=rand()%eligibleRoutes.size();
	  route = eligibleRoutes[index];
	}
      } else {
	s.insert(r,route,bestPos);
      }
    }
    eligibleRoutes.clear();
//     cout << " || ";
  }
  return s;
}

RandomInit::RandomInit()
{

}

RandomInit::~RandomInit()
{

}

