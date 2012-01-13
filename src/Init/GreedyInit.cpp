#include "GreedyInit.hpp"
#include "../Useful.hpp"

using namespace std;

GreedyInit::GreedyInit()
{

}

GreedyInit::~GreedyInit()
{

}



Solution& GreedyInit::execute(DataImporter* d, Solution& s, std::vector<Request*> requests)
{ 
//   cout << "Greedy Insertion Procedure...there are " << requests.size() << " requests to insert...";
  int routeIndex;
  int bestPosition;
  int count=0;
  int notcount=0;
  vector<Request*> notinserted;
  double bigM = d->get_distance_matrix()->getBigM()*100;
  for (unsigned int rIndex=0; rIndex<requests.size(); rIndex++)
  {
    Request* r = requests[rIndex];
    double bestCost=bigM;
    
    bool found=false;
    for (unsigned int route=0;route<s.size();route++)
    {
      if (s.check_day(r,route) && s.check_skills(r,route))
      {
	for (unsigned int position = 0;position<s.size_of_route(route); position++)
	{
	  if (s.insertionPossible(r,route,position))
	  {
	    double currentCost=s.getInsertionCost(r,route,position);
	    if (currentCost<bestCost)
	    bestPosition = position;
	    routeIndex = route;
	    found=true;
	    break;
	  }
	}
      }
    }
    if (found)
    {
//       cout << "inserting" << endl;
      try {
	s.insert(r,routeIndex,bestPosition);
	count++;
      } catch (const Error& e) {
	ofstream logfile("log",ios::app);
	if (logfile)
	{
	  logfile << "(greedy) Route number: " << r << endl;
	  logfile.close();
	}
	throw Error(e.number(),":: (inserting) -> " + e.desc(),e.level()+1);
      }
    } else {
//       cout << "no insertion" << endl;
      notinserted.push_back(r);
      notcount++;
    }
  }
//   cout << "Inserted " << count << " requests, skipped " << notcount << "\n";
  _uninserted_requests=notinserted;
  requests.clear();
  return s;
}

