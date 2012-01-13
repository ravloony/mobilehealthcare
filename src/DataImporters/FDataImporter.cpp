#include "FDataImporter.hpp"

FDataImporter::FDataImporter()
{
  _num_days=1;
}

void FDataImporter::print()
{

}

void FDataImporter::plot()
{

}

void FDataImporter::run()
{
  Client* c = new Client("",1,"",1);
  _clients.push_back(c);
  Client* c2 = new Client("",1,"",2);
  Request* r = new Request(360,479,15,9.0,3,0);
  r->add_client(c);
  c->add_request(r);
  _requests.push_back(r);
  r = new Request(360,479,15,15.0,2,0);
  r->add_client(c);
  c->add_request(r);
  _requests.push_back(r);
  r = new Request(360,479,15,12.0,2,0);
  r->add_client(c2);
  c->add_request(r);
  _requests.push_back(r);
  r = new Request(360,479,15,12.0,3,0);
  r->add_client(c2);
  c->add_request(r);
  _requests.push_back(r);
  Nurse* n = new Nurse(3,"",0,"",8.0,3,33.0);
  Nurse* n2 = new Nurse(4,"",0,"",8.0,3,33.0);
  _nurses.push_back(n);
  _nurses.push_back(n2);
  vector<double> dists;
  dists.push_back(0.0);
  dists.push_back(4);
  dists.push_back(2);
  dists.push_back(4.47);
  dists.push_back(4);
  dists.push_back(0);
  dists.push_back(4.47);
  dists.push_back(2);
  dists.push_back(2);
  dists.push_back(4.47);
  dists.push_back(0);
  dists.push_back(4);
  dists.push_back(4.47);
  dists.push_back(2);
  dists.push_back(4);
  dists.push_back(0);  
  vector<int> ids;
  ids.push_back(1);
  ids.push_back(2);
  ids.push_back(3);
  ids.push_back(4);
  _distance_matrix = new DistanceMatrix(ids, dists);
  
}
// FDataImporter::~DataImporter()
// {
// 
// }

FDataImporter::~FDataImporter()
{

}
