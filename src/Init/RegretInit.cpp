/*!
* \file RegretInit.cpp
* \brief Regret construction Heuristic implementation file.
* \author Thomas Macdonald
* \date Thu Mar  4 14:29:32 CET 2010
*/
#include "RegretInit.hpp"
using namespace std;

RegretInit::RegretInit()
{

}

RegretInit::~RegretInit()
{

}


Solution& RegretInit::execute(DataImporter* d, Solution& s, vector<Request*> requests)
{
/*  ofstream logfile("log",ios::app);
  if (logfile)
  {
    logfile << "There are " << requests.size() << " requests." << endl;
    logfile.close();
  }
  cout << "Executing Regret insertion" << endl;*/
//   cout << "Getting data\n";
//   cout << "BigM is " << d->get_distance_matrix()->getBigM()*10 << endl;
  vector<Client*> clients = d->get_clients();
  vector<Nurse*> nurses = d->get_nurses();
  _costmap.clear();

  //create routes
/*  vector<Route> tmpVecRoute = s.get_routes();*/
  double bigM = (d->get_distance_matrix()->getBigM())*10;
//   cout << "Getting Routes\n";
//   cout << tmpVecRoute.size() << " Routes." << endl;
  int numberOfRequests = (int)requests.size();
  double maxRegret;
//   cout << "Calculating best insertion for requests.\n";
  bool foundAtLeastOneRoute = false;
  bool inserted = false;
  try {
    std::vector<int, std::vector<std::pair<double,int> > > costTable; //indexed by ROUTE
    for (unsigned int k=0; k<s.size();k++)
    {
      std::vector<std::pair<double,int> > costLine;
      for (unsigned int i=0; i<requests.size();i++)
      {
	costLine.push_back(std::pair<double,int>(bigM,0));
      }
      costTable.push_back(costLine);
    }
    while (!requests.empty())
    {
      for (unsigned int k=0; k<s.size();k++)
      {
// 	if (costTableIter!=costTable.end() && (*costTableIter).first!=0) //if the line is in the map, and the route has been changed, then we need to recalculate the best cost.
// 	{
	  for (unsigned int i=0; i<requests.size();i++)
	  {
	    if (s.check_skills(requests[i],k) && s.check_day(requests[i],k))
	    {
	      //find best insertion position
	      double bestInsertionCost = bigM;
	      int bestInsertionPos = -1;
	      for (unsigned int j=0; j<=s.size_of_route(k); j++)
	      {
		if (s.insertionPossible(requests[i],k,j))
		{
		  double currentCost = s.getInsertionCost(requests[i],k,j);
		  if (currentCost<bestInsertionCost)
		  {
		    bestInsertionCost=currentCost;
		    bestInsertionPos=j;
		  }
		}
	      }
	      if (bestInsertionPos!=-1) //if a position was found
	      {
		costTable[k][i] = std::pair<double,int>(bestInsertionCost,bestInsertionPos);
	      } else {
		costTable[k][i] = std::pair<double,int>(-1,-1);
	      }
	    }
	  } 
      }
      //now we have a map of the best costs and positions per route per request, we need to calculate the regret for each request
      //to do so we iterate over the map, for each request updating the regret value as we go
      std::map<int,std::pair<int, double> > regretMap; //map of regret values indexed by request id
      //for each route
      for (std::map<int, std::pair<int,std::map<int, std::pair<double,int> > > >::iterator costTableIter=costTable.begin(); costTableIter!=costTable.end();costTableIter++)
      {
	std::map<int, std::pair<double,int> > lineMap = costTableIter->second.second;
	//for each request that is insertable in the route
	for (std::map<int, std::pair<double,int> >::iterator lineMapIt = lineMap.begin(); lineMapIt != lineMap.end(); lineMapIt++)
	{
	  //if request is found in route
	  if (regretMap.find(lineMapIt->first)==regretMap.end())
	  {
	    
	  } else {
	    
	  }
	}
      }
      
//       //prettiness
//       cout << "\r";
//       string progbar;
//       for (unsigned int i = 6; i>0;i--)
// 	if (requests.size()%7==i)
// 	{
// 	  progbar+="#";
// 	} else {
// 	  progbar += " ";
// 	}
// 	int requestsLeft = (int)requests.size();
//       cout << "["+progbar+"] Requests remaining:  " << requestsLeft << "  "<< 100-(100*requestsLeft/numberOfRequests) << "%    ";
// 
//       vector<int> eligibleRoutes;
//      
//       int routeNum = -1;
//       int requestPosition = 0;
//       maxRegret=0.0;
//       unsigned int requestIndex = 0;
//       foundAtLeastOneRoute = false;
//       
//       //for all requests, calculate regret values (difference between 2 lowest costs) and save best regret
//       for (unsigned int i=0; i<requests.size();i++)
//       {
// 	int bPos;
// 	int bRouteNum;
// 	double bCost=bigM, sbCost=bigM;
// /*	cout << "$$$$$$$$$$$$";
//  	cout << "trying request " << requests[i]->get_local_id() << "\n";*/
// 	// create short list
// 	for (unsigned int k=0; k<s.size();k++)
// 	  if (s.check_skills(requests[i],k) && s.check_day(requests[i],k))
// 	    eligibleRoutes.push_back(k);
// 	
// 	//for all eligible routes
// 	for (unsigned int l=0; l<eligibleRoutes.size();l++)
// 	{
// // 	  cout << "testing route " << eligibleRoutes[l] << "...";
// 	  double minCost = bigM;
// 	  int minPos=0;
// 	  bool found = false;
// 	  bool cachehit=false;
// 	  map<int, Requestcache>::iterator cmi = _costmap.find(cantorPair(requests[i]->get_local_id(),eligibleRoutes[l]));
// 	  if (cmi!=_costmap.end() && cmi->second.routeSize==s.size_of_route(eligibleRoutes[l])) //if the route has not been modified
// 	  {
// // 	    cout << "cache hit...";
// 	    minCost=cmi->second.minCost;
// 	    minPos=cmi->second.minPos;
// 	    foundAtLeastOneRoute=true;
// 	    found=true;
// 	  } else {
// 	    //for all positions we get the insertion cost
// // 	    cout << "there are " << s.size_of_route(eligibleRoutes[l])+1 << " positions in route...";
// 	    for (int m=0; m<=(s.size_of_route(eligibleRoutes[l])); m++)
// 	    {
// // 	      cout << "pos : " << m << "...";
// 	      //get cost
// 	      if (s.insertionPossible(requests[i],eligibleRoutes[l],m))
// 	      {
// // 		cout << "yes...";
// 		double currentCost = s.getInsertionCost(requests[i],eligibleRoutes[l],m);
// // 		cout << "cost: " << currentCost << "...";
// 		if (currentCost<minCost)
// 		{
// 		  minCost=currentCost;
// 		  minPos=(int)m;
// 		  found = true;
// 		  foundAtLeastOneRoute=true;
// 		  
// 		}
// 	      } else {
// // 		cout << "no...";
// 	      }
// 	    }
// 	    if (found)
// 	    {
// 	      Requestcache rc(s.size_of_route(eligibleRoutes[l]), minCost, minPos);
// 	      _costmap[cantorPair(requests[i]->get_local_id(),eligibleRoutes[l])]=rc;
// // 	      cout << "cache fill -- min cost is " << minCost << "...";
// 	    }
// 	  }
// 
// 	  //if the lowest cost for the current route is smaller than the best cost so far we save the cost, the route, and the position
// // 	  cout <<"#";
// 	  if (minCost<bCost)
// 	  {
// // 	    cout << "updating best cost from " << bCost << " to " << minCost << "...";
// 	    sbCost=bCost;
// 	    bCost=minCost;
// 	    bPos=minPos;
// 	    bRouteNum=eligibleRoutes[l];
// 	  } else { 
// 	    //if the lowest cost for the current route is smaller than the second best cost so far we save the value
// 	    if (minCost<sbCost) {
// // 	      cout << "updating second best cost from " << sbCost << " to " << minCost << "...";
// 	      sbCost=minCost;
// 	    }
// 	  }
// // 	  cout <<"#";
// 	}//end for
// 	
// 	if ((sbCost-bCost)>maxRegret)
// 	{ 
// // 	  cout << "maxregret updated from " << maxRegret << " to " << (sbCost-bCost) << "...";
// 	  maxRegret=(sbCost-bCost);
// 	  routeNum=bRouteNum;
// 	  requestPosition=bPos;
// 	  requestIndex=i;
// // 	  cout << "routeNum: " << routeNum << ", pos: " << requestPosition;
// 	}
// 	eligibleRoutes.clear();
// // 	cout << endl;
//       } //end for
//       if (foundAtLeastOneRoute && routeNum!=-1)
//       {
// 	Request* rToInsert = requests[requestIndex];
// 	try
// 	{
// // 	  cout << "got route " << routeNum << " pos " << requestPosition << " -> trying to insert...";
// 	  s.insert(rToInsert,routeNum,requestPosition);
// 	} catch (const Error& e) {
// 	  ofstream logfile("log",ios::app);
// 	  if (logfile)
// 	  {
// 	    logfile << "Route number: " << routeNum <<  ", Max regret : " << maxRegret << endl;
// 	    logfile.close();
// 	  }
// 	  throw Error(e.number(),":: (inserting) -> " + e.desc(),e.level()+1);
// 	}
// 	//remove request pointer from vector
// 	requests.erase(requests.begin()+requestIndex);
// 	//reset values after insertion
// 	maxRegret=0.0;
//       } else {
// /*	cout << "could not insert" << endl;
// 	cout << "there are " << requests.size() << " requests remaining" << endl;*/
// 	_uninserted_requests=requests;
// 	return s;
//       }
//       cout << "\n#####################insertion done, starting again with remainder###########################\n";
      cout.flush();
    }//end while
//     cout << "\r" << "Done. " << numberOfRequests << " requests treated                              ";
  } catch (const Error& e) {
    ofstream logfile("log",ios::app);
    if (logfile)
    {
      logfile << "There are " << requests.size() << " requests remaining." << endl;
      logfile.close();
    }
    throw Error(e.number(),"RegretInit::execute -> " + e.desc(),e.level()+1);
  }
  cout << endl;
  return s;
}

int RegretInit::cantorPair(int x, int y)
{
  int cantor = (((x+y)*(x+y+1))/2+y);
//   cout << "cantor : (" << x << "," << y << ")->" << cantor << endl;
  return cantor;
}



std::ostream& operator<<(ostream& stream, const RegretInit r)
{
  for (unsigned int i=0; i<r._routes.size(); i++)
  {
    stream << r._routes[i] << endl;
  }
  return stream;
}
