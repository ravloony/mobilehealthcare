/*!
* \file GoldenDataImporter.cpp
* \brief 
* \author Thomas Macdonald
* \date Thu Mar  4 14:29:15 CET 2010
*/
#include "GoldenDataImporter.hpp"
#include "../Debug.hpp"

using namespace std;


GoldenDataImporter::GoldenDataImporter()
{
  
}

void GoldenDataImporter::run()
{
  cout << "parsing...\n";
  string buffer;
  vector<string> buffertokens;
  string delims = ":";
  ifstream inputFile(_confFile.c_str());
  if (inputFile) {
    //get name
    if (!inputFile.eof())
    {
      inputFile >> buffer >> _name;
    } else {
      throw Error(0,"Unexpected end of file",0);
    }
    if (!inputFile.eof())
    {
      getline (inputFile,buffer);
      inputFile >> buffer >> _type;
    } else {
      throw Error(0,"Unexpected end of file",0);
    }
    if (!inputFile.eof())
    {
      getline (inputFile,buffer);
    } else {
      throw Error(0,"Unexpected end of file",0);
    }
    if (!inputFile.eof())
    {
      inputFile >> buffer;
      getline (inputFile,_comment);
      string dim;
      inputFile >> buffer >> dim;
      _dim = atoi(dim.c_str());
    } else {
      throw Error(0,"Unexpected end of file",0);
    }
    if (!inputFile.eof())
    {
      getline (inputFile,buffer);
      string num_days;
      inputFile >> buffer >> num_days;
      _num_days = atoi(num_days.c_str());
    } else {
      throw Error(0,"Unexpected end of file",0);
    }
    if (!inputFile.eof())
    {
      getline (inputFile,buffer);
      string capacity;
      inputFile >> buffer >> capacity;
      _capacity = atoi(capacity.c_str());
    } else {
      throw Error(0,"Unexpected end of file",0);
    }
    if (!inputFile.eof())
    {
      getline (inputFile,buffer);
      string distance;
      inputFile >> buffer >> distance;
      _distance = atoi(distance.c_str());
    } else {
      throw Error(0,"Unexpected end of file",0);
    }
    if (!inputFile.eof())
    {
      getline (inputFile,buffer);
      inputFile >> buffer >> _edge_weight_type;
    } else {
      throw Error(0,"Unexpected end of file",0);
    }
    if (!inputFile.eof())
    {
      getline (inputFile,buffer);
      inputFile >> buffer >> _edge_weight_format;
    } else {
      throw Error(0,"Unexpected end of file",0);
    }
    if (!inputFile.eof())
    {
      getline (inputFile,buffer);
      inputFile >> buffer >> _node_coord_type;
    } else {
      throw Error(0,"Unexpected end of file",0);
    }
    if (!inputFile.eof())
    {
      getline (inputFile,buffer);
      inputFile >> buffer;
    } else {
      throw Error(0,"Unexpected end of file",0);
    }
    cout << "Constructing instances...getting coordinates...";
    // get node coordinates
    vector<pair<double,double> >  coords;
    while (!inputFile.eof())
    {
      double x,y;
      string node;
      inputFile >> node;
      if (node=="DEMAND_SECTION")
	break;
      inputFile >> x >> y;
      pair<double,double> current (x,y);
      coords.push_back(current);
      getline(inputFile,buffer);
    }
    _coords = coords;
    cout << "getting demands...";
    //get demands -- we dont care in fact
    vector<vector<int> > demands;
    while (!inputFile.eof())
    {
//       int x,y,z;
      string node;
      inputFile >> node;
      if (node=="SVC_TIME_SECTION")
	break;
// inputFile >> x >> y >> z;
      vector<int> current;
      cout << node;
      istringstream ss( node );
      for (unsigned int i =0; i<_num_days; i++)
      {
	double tmpDemand;
	inputFile >> tmpDemand;
	cout << tmpDemand << "|";
	current.push_back(tmpDemand);
      }
      cout << endl;
/*    
      current.push_back(x);
      current.push_back(y);
      current.push_back(z);*/
      demands.push_back(current);
      getline(inputFile,buffer);
    }
    _demands = demands;
    
    cout << "getting service times...";
    //get service times
    vector<vector<double> > svc_times;
    while (!inputFile.eof())
    {
      double x,y,z;
      string node;
      inputFile >> node;
      if (node=="DEPOT_SECTION")
	break;
      inputFile >> x >> y >> z;
      vector<double> current;
      current.push_back(x);
      current.push_back(y);
      current.push_back(z);
      svc_times.push_back(current);
      getline(inputFile,buffer);
    }
    _svc_times = svc_times;
    
    cout << "getting depot coordinates...";
    //get depot
    if (!inputFile.eof())
    {
      getline (inputFile,buffer);
      pair<double,double> tmp;
      inputFile >> tmp.first >> tmp.second;
      _depot_coords = tmp;
    } else {
      throw Error(0,"Unexpected end of file",0);
    }
    if (!inputFile.eof())
    {
      getline (inputFile,buffer);
      inputFile >> _depot_other;
    } else {
      throw Error(0,"Unexpected end of file",0);
    }
    inputFile.close();
  } else {
    cout << "File does not exist!!" << endl;
    throw Error(0,"Cannot open file");
  }
  cout << "generating missing data..." << endl;
  //TODO make more data yay
  int maxskill=0;
  Useful::init();
  //now make requests and clients.
  vector<Client*> clientVec;
  vector<Request*> requestVec;
  for (unsigned int i=0; i<_coords.size(); i++)
  {
    Client* tmpClient = new Client("None",0,"None",i+1,_coords[i].first, _coords[i].second);
    clientVec.push_back(tmpClient);
    for (int j=0; j<_num_days;j++) {
      double early, late, s_time, r_time;
      int skill;
      early = 360;
      late = 1200;
      skill = 1;
//       _skills[i][j];
      s_time = _svc_times[i][j];
      r_time = (late-early)/2; //requested time is in the middle
       if (_demands[i][j]!=-1)
       {
	Request* tmpRequest = new Request(early,late,s_time,r_time,skill,j);
      
	tmpClient->add_request(tmpRequest);
	tmpRequest->add_client(tmpClient);
	
	requestVec.push_back(tmpRequest);
       }
    }
  }
  cout << "Got " << clientVec.size() << " clients, " << requestVec.size() << " requests." << endl;
  //make nurses (how many?)
  vector<Nurse*> nurseVec;
//   int numberOfNurses = (int)(_coords.size()/5)+1;
  int numberOfNurses;
  cout << "number of nurses?";
  cin >> numberOfNurses;
  int numberOfCoords = _coords.size();
  bool maxSkillReached=false;
  for (int i=0; i<numberOfNurses; i++)
  {
    int skill = 5;
//     Useful::randbetween(1,5);
    //we need to make sure at least one nurse has the required skills.
//     if (!maxSkillReached && skill>=maxskill)
//       maxSkillReached=true;
//     if (!maxSkillReached && i==numberOfNurses-1)
//       skill = maxskill;
    Nurse* tmpNurse = new Nurse(numberOfCoords+i+1,"None",0,"None",3.0,skill,9.0);
    nurseVec.push_back(tmpNurse);
    _coords.push_back(pair<double,double>(0.0,0.0));
  }
  cout << "Got " << numberOfNurses << " nurses." << endl;

  //make distance matrix
  vector<int> ids;
  for (unsigned int i=0; i<clientVec.size();i++)
  {
    ids.push_back(clientVec[i]->get_id());
  }
  for (unsigned int i=0; i< nurseVec.size(); i++)
  {
    ids.push_back(nurseVec[i]->get_id());
  }
  vector<double> dists;
  for (unsigned int i=0; i<_coords.size();i++)
  {
    for (unsigned int j=0; j<_coords.size(); j++)
    {
      dists.push_back(sqrt(pow((_coords[j].first-_coords[i].first),2.0)+pow((_coords[j].second-_coords[i].second),2.0)));
    }
  }
  
  cout << "Checking integrity..." << endl;
  for (unsigned int i=0; i<clientVec.size();i++)
  {
    int id = clientVec[i]->get_id();
    vector<Request*> reqVec = clientVec[i]->get_requests();
    for (unsigned int j=0; j<reqVec.size();j++)
    {
      Client* cli = reqVec[j]->get_client();
      assert(cli->get_id()==id);
    }
  }
  _clients=clientVec;
  _requests=requestVec;
  _nurses=nurseVec;
  _distance_matrix = new DistanceMatrix(ids,dists);
}

void GoldenDataImporter::plot()
{
  Plot plot;
  plot.set_name("plot");
  plot.add_points(_coords);
  plot.plot();
}


GoldenDataImporter::~GoldenDataImporter()
{
  delete _distance_matrix;
  for (unsigned int i = 0; i<_clients.size(); i++)
  {
    delete _clients[i];
  }
  for (unsigned int i = 0; i<_nurses.size(); i++)
  {
    delete _nurses[i];
  } 
}


void GoldenDataImporter::print()
{
  for (unsigned int i = 0; i<_nurses.size(); i++)
  {
    
  }
}

