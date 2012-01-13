#include "MyDataImporter.hpp"

MyDataImporter::MyDataImporter() : DataImporter()
{

}

MyDataImporter::~MyDataImporter()
{

}

MyDataImporter::MyDataImporter(std::string filename) : DataImporter(), _conf_file(filename)
{  
}

void MyDataImporter::print()
{

}

void MyDataImporter::plot()
{

}

void MyDataImporter::run()
{
  try{
    string buffer;
    string ndays;
    ifstream inputFile(_conf_file.c_str());
    if (inputFile)
    {
      inputFile >> ndays;
  //     inputFile.getline();
      _num_days = atoi(ndays.c_str());
      cout << "number of days: " << _num_days << endl;
      int progress=1;
      getline(inputFile,buffer);
      getline(inputFile,buffer);
      while (!inputFile.eof())
      {
// 	cout << "buffer: \"" << buffer << "\"" << endl;

	if (buffer.find("CLIENTS")<string::npos)
	{
// 	  cout << "client section" << endl;
	  progress = 1;
	  getline(inputFile,buffer);
	  continue;
	}
	if (buffer.find("REQUESTS")<string::npos)
	{
// 	  cout << "request section" << endl;
	  progress = 2;
	  getline(inputFile,buffer);
	  continue;
	}
	if (buffer.find("NURSES")<string::npos)
  //       if (buffer[0]=='N')
	{
// 	  cout << "nurse section" << endl;
	  progress = 3;
	  getline(inputFile,buffer);
	  continue;
	}
	switch (progress)
	{
	  case 1:
	    //cout << "making client" << endl;
	    make_client(buffer);
	    break;
	  case 2:
	    make_request(buffer);
	    break;
	  case 3:
	    make_nurse(buffer);
	    break;
	}
	getline(inputFile,buffer);
      }
      make_nurse(buffer);
    } else {
      throw Error(0,"cannot open data file",0);
    }
    vector<double> dists;
    for (unsigned int i=0; i<_coords.size();i++)
    {
      for (unsigned int j=0; j<_coords.size(); j++)
      {
	dists.push_back(10*sqrt(pow((_coords[j].first-_coords[i].first),2.0)+pow((_coords[j].second-_coords[i].second),2.0)));
      }
    }
    _distance_matrix = new DistanceMatrix(_ids,dists);
  } catch (Error& e)
  {
    throw Error(e.number(),"MyDataImporter::run() -> ",e.level()+1);
  }
}

int MyDataImporter::get_num_days()
{
  return _num_days;
}

void MyDataImporter::make_client(string buffer)
{
  char buf[100];
  strcpy(buf,buffer.c_str());
  std::vector<char*> bufary;
  char* p = strtok(buf," ");
  while (p)
  {
    bufary.push_back(p);
    p = strtok(NULL," ");
  }
  int id = atoi(bufary[0]);
  double x = atof(bufary[1]);
  double y = atof(bufary[2]);
  Client* client = new Client("",0,"",id,x,y);
  _ids.push_back(id);
  _coords.push_back(std::pair<double,double>(x,y));
  _clients.push_back(client);
}

void MyDataImporter::make_nurse(string buffer)
{
  cout << "_" << buffer << "_" << endl;
  if (buffer.empty())
    return;
  char buf[100];
  strcpy(buf,buffer.c_str());
  std::vector<std::string> bufary;
  char* p = strtok(buf," ");
  while (p)
  {
    bufary.push_back(string(p));
    p = strtok(NULL," ");
  }
  int id = atoi(bufary[0].c_str());
  int skill = atoi(bufary[1].c_str());
  double x = atof(bufary[2].c_str());
  double y = atof(bufary[3].c_str());
  double sd = atof(bufary[4].c_str());
  double md = atof(bufary[5].c_str());
  Nurse* nurse = new Nurse(id,"",0,"",sd,skill,md,x,y);
  _ids.push_back(id);
  _coords.push_back(std::pair<double,double>(x,y));
  _nurses.push_back(nurse);
}

void MyDataImporter::make_request(string buffer)
{
  char buf[100];
  strcpy(buf,buffer.c_str());//WRONG!!
  std::vector<char*> bufary;
  char* p = strtok(buf," ");
  while (p)
  {
    bufary.push_back(p);
    p = strtok(NULL," ");
  }
  int id = atoi(bufary[0]);
  int day = atoi(bufary[1]);
  int skill = atoi(bufary[2]);
  int tw = atoi(bufary[3]);
  int st = atoi(bufary[4]);
  double early, late, s_time, r_time;
  switch (tw) {
    case 1:
      early = 360;
      late = 479;
      break;
    case 2:
      early = 480;
      late = 659;
      break;
    case 3:
      early = 660;
      late = 779;
      break;
    case 4:
      early = 780;
      late = 959;
      break;
    case 5:
    default:
      early = 960;
      late = 1200;
      break;
  }
  r_time = (late-early)/2;
  s_time = (double)st*0.10*30;
  Request* request = new Request(early,late,s_time,r_time,skill,day);
  bool found = false;
  Client* tmpclient;
  for (unsigned int i = 0; i<_clients.size() && !found;i++)
  {
    if (_clients[i]->get_id()==id)
    {
      found=true;
      tmpclient=_clients[i];
    }
  }
  if (!found)
    throw Error(0,"MyDataImporter::make_request() -> Request corresponds to no clients",0);
  tmpclient->add_request(request);
  request->add_client(tmpclient);
  _requests.push_back(request);
}
