#include "TestInit.hpp"

TestInit::TestInit()
{

}

TestInit::~TestInit()
{

}

Solution& TestInit::execute(DataImporter* d, Solution& s, std::vector< Request* > requests)
{
  vector<Route> routes = s.get_routes();
  vector<Nurse*> nurses = d->get_nurses();
//   vector<Request*> requests = d->get_requests();

  cout << "trying to insert " << *requests[0] << endl;
  
  if (routes[0].insertionPossible(requests[0],0))//works
  {
    cout << "can insert" << endl;
    cout << "insertion cost: " << routes[0].getInsertionCost(requests[0],0) << endl;
    cout << "inserting" << endl;
    routes[0].insert(requests[0],0);
  }
  cout << "trying to insert " << *requests[1] << endl;
  if (routes[0].insertionPossible(requests[1],0))//fails
  {
    cout << "can insert" << endl;
    cout << "insertion cost: " << routes[0].getInsertionCost(requests[1],0) << endl;
    cout << "inserting" << endl;
    routes[0].insert(requests[1],0);
  } else {
    cout << "cannot insert" << endl;
  }
  cout << "trying to insert " << *requests[1] << endl;
  if (routes[0].insertionPossible(requests[1],1))//works
  {
    cout << "can insert" << endl;
    cout << "insertion cost: " << routes[0].getInsertionCost(requests[1],1) << endl;
    cout << "inserting" << endl;
    routes[0].insert(requests[1],1);
  } else {
    cout << "cannot insert" << endl;
  }

  cout << "trying to insert " << *requests[1] << endl;
  if (routes[0].insertionPossible(requests[1],1))//fails
  {
    cout << "can insert" << endl;
    cout << "insertion cost: " << routes[0].getInsertionCost(requests[1],1) << endl;
    cout << "inserting" << endl;
    routes[0].insert(requests[1],1);
  } else {
    cout << "cannot insert" << endl;
  }

  cout << "trying to insert " << *requests[1] << endl;
  if (routes[0].insertionPossible(requests[1],2))//fails
  {
    cout << "can insert" << endl;
    cout << "insertion cost: " << routes[0].getInsertionCost(requests[1],2) << endl;
    cout << "inserting" << endl;
    routes[0].insert(requests[1],2);
  } else {
    cout << "cannot insert" << endl;
  }
  s.remove_routes();
  s.add_route(routes[0]);
  cout << s.get_total_consistency() << " |-| " << s.get_total_cost() << endl; 
  return s;
}

