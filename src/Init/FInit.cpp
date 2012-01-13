#include "FInit.hpp"

Solution& FInit::execute(DataImporter* d, Solution& s, vector<Request*> requests)
{
  cout << "First come, first served insertion\n";
  int untreated = 0;
  int insertedCount=0;
  for(unsigned int j=0; j<requests.size();j++)
  {
//     int i = 1;
//     vector<Route>::iterator riter;
//     for (riter=vr.begin();riter!=vr.end();riter++)
    bool found=false;
    for (unsigned int i=0; i<s.size();i++)
    {
//       cout << "============================================" << endl;
//       cout << vr[i] << endl;
//       cout << "============================================" << endl;
//       cout << j+1 << " : " << i+1 << endl;
//       cout << *(requests[j]) << endl;
      if (s.check_day(requests[j],i) && s.check_skills(requests[j],i))
      {
	for (unsigned int k=0; k<=s.size_of_route(i);k++)
	{

	  if (s.insertionPossible(requests[j],i,k))
	  {
  // 	  cout << "insertion possible" << endl;
	    s.insert(requests[j],i,k);
	    insertedCount++;
  // 	  cout << "insertion cost: " << vr[i].getInsertionCost(requests[j],k) << endl;
	    found=true;
	    break;
	  } else {
  // 	  cout << "insertion not possible" << endl;
	  }
	}
      }
      if (found)
	break;
    }
    if (!found)
    {
      _uninserted_requests.push_back(requests[j]);
    }
  }

  cout << "done" << endl;
  cout << "requests inserted: " << insertedCount << ", skipped: " << _uninserted_requests.size() << endl;
  return s;
}

