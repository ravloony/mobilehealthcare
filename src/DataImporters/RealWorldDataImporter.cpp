/*!
* \file RealWorldDataImporter.cpp
* \brief 
* \author Thomas Macdonald
* \date Thu Mar  4 14:29:15 CET 2010
*/
#include "RealWorldDataImporter.hpp"
#include "../Debug.hpp"

using namespace std;



void RealWorldDataImporter::run()
{
  vector<int> idList;
  vector<Client*> clientList;
  vector< Request* > requestList;
  vector< Nurse* > nurseList;
  Client* tmpclient;
  Request* tempreq;
  string line;
  //get clients/requests
  ifstream reqFile(_req_file.c_str());
  int linenum = 0;
  getline(reqFile,line);
  int currentid=0;
  int numberOfClients=0;
  int numberOfRequests=0;
  while (getline(reqFile,line))
  {
    linenum++;
    istringstream linestream(line);
    string item;
    //get id
    getline (linestream, item, ';');
    int id = atoi(item.c_str());
    getline (linestream, item, ';');
    string address = item;
    getline (linestream, item, ';');
    int zip = atoi(item.c_str());
    getline (linestream, item, ';');
    string city = item;
    getline (linestream, item, ';');
    string time = item;
    getline (linestream, item, ';');
    string termineinsatz = item;
    getline (linestream, item, ';');
    double length = atof(item.c_str());
    getline (linestream, item, ';');
    string day = item;
    getline (linestream, item, ';');
    string timewindow = item;
    getline (linestream, item, ';');
    string skill = item;
    bool newClient = true;
    for (unsigned int i=0; i<idList.size(); i++)
      if (idList[i]==id) {
	newClient=false;
	break;
      }
    if (newClient)
    {
      tmpclient = new Client(address,zip,city,id);
      currentid = id;
      idList.push_back(id);
      clientList.push_back(tmpclient);
      numberOfClients++;
    }
    tempreq = makerequest(time, termineinsatz, length, day, timewindow, skill,tmpclient);
    requestList.push_back(tempreq);
    tmpclient->add_request(tempreq);
    numberOfRequests++;
  }
  reqFile.close();
  cout << "Request/Client file read. Got " << linenum << " lines." << endl;
  Debug::print<string>("Imported ");
  Debug::print<int>(numberOfClients);
  Debug::print<string>(" clients, ");
  Debug::print<int>(numberOfRequests);
  Debug::println<string>(" requests.");
  
  //get nurses
  ifstream nurseFile(_nurse_file.c_str());
  linenum = 0;
  int numberOfNurses = 0;
  getline(nurseFile,line);
  while (getline(nurseFile,line))
  {
    linenum++;
    istringstream linestream(line);
    string item;
    getline(linestream,item,';');
    int id = atoi(item.c_str());
    idList.push_back(id);
    getline(linestream,item,';');
    string adress = item;
    getline(linestream,item,';');
    int zip = atoi(item.c_str());
    getline(linestream,item,';');
    string city = item;
    getline(linestream,item,';');
    string shift = item;
    idList.push_back(id);
    Nurse* newNurse = new Nurse(id,adress,zip,city,8.0,6,35);
    nurseList.push_back(newNurse);
    numberOfNurses++;
  }
  cout << "Nurse file read. Got " << linenum << " lines." << endl;
  Debug::print<string>("Imported ");
  Debug::print<int>(numberOfNurses);
  Debug::println<string>(" nurses.");
  //get distance matrix
  ifstream matFile(_dm_file.c_str());
  linenum = 0;
  vector<int> from,to;
  vector<double> dist;
  getline(matFile,line);
  while (getline (matFile, line))
  {
    linenum++;
    //     cout << "\nLine #" << linenum << ":" << endl;
    istringstream linestream(line);
    string item;
    int itemnum = 0;
    
    
    while (getline (linestream, item, ';'))
    {
      itemnum++;
      //       cout << "Item #" << itemnum << ": " << item << endl;
      if (itemnum==2)
	from.push_back(atoi(item.c_str()));
      if (itemnum==3)
	to.push_back(atoi(item.c_str()));
      if (itemnum==5)
      {
	replace(item.begin(),item.end(),',','.'); //we can take commas or dots yay!
	dist.push_back(atof(item.c_str()));
      }
    }
  }
  _clients = clientList;
  _requests = requestList;
  _nurses = nurseList;
  vector<int> ids;
  for (unsigned int i=0; i<_clients.size(); i++)
    ids.push_back(_clients[i]->get_id());
  for (unsigned int i=0; i<_nurses.size(); i++)
    ids.push_back(_nurses[i]->get_id());
  _distance_matrix = new DistanceMatrix(ids, dist);
}

Request* RealWorldDataImporter::makerequest(string time, string termineinsatz, double length, string daystr, string timewindow, string skillstr, Client* client)
{
  double early, late, stime, rtime;
  int skill, day;
  if (doesStringContain(timewindow,"06:00"))
  {
    early = 6.0;
    late = 7.59;
  } else if (doesStringContain(timewindow,"08:00"))
  {
    early = 8.0;
    late = 10.59;
  } else if (doesStringContain(timewindow,"11:00"))
  {
    early = 11.0;
    late = 12.59;
  } else if (doesStringContain(timewindow,"13:00"))
  {
    early = 13.0;
    late = 15.59;
  } else if (doesStringContain(timewindow,"16:00"))
  {
    early = 16.0;
    late = 20.0;
  }
  map<string,int> m;
  m["Montag"] = 1;
  m["Dienstag"] = 2;
  m["Mittwoch"] = 3;
  m["Donnerstag"] = 4;
  m["Freitag"] = 5;
  m["Samstag"] = 6;
  m["Sonntag"] = 7;
  day = m[daystr];
  stime = length;
  replace(time.begin(),time.end(),':','.');
  rtime = atof(time.c_str());
  if (doesStringContain(skillstr,"Reinigungsdienst"))
  {
    skill=1;
  } else if (doesStringContain(skillstr,"Besuchsdienst"))
  {
    skill=2;
  } else if (doesStringContain(skillstr,"Heimhilfe"))
  {
    skill=3;
  } else if (doesStringContain(skillstr,"MHKP"))
  {
    skill=5;
  } else if (doesStringContain(skillstr,"DGKP"))
  {
    skill=6;
  }
  Request* result = new Request(early,late,stime,rtime,skill,day);
  result->add_client(client);
  return result;
}


bool RealWorldDataImporter::doesStringContain(string str, string substr)
{
  size_t found;
  found = str.find(substr);
  return (found!=string::npos);
}

void RealWorldDataImporter::plot()
{
  cout << "Cannot plot this type of data" << endl;
}

void RealWorldDataImporter::print()
{

}


RealWorldDataImporter::~RealWorldDataImporter()
{

}
RealWorldDataImporter::RealWorldDataImporter(string fileName) : DataImporter()
{
    _fname = fileName;
    ifstream confFile(fileName.c_str());
    if (!confFile.eof())
    {
        getline(confFile, _req_file);
    } else {
        throw Error(0,"RealWorldDataImporter(constructor): unexpected end of conf file!", 0);
    }
    if (!confFile.eof())
    {
        getline(confFile, _nurse_file);
    } else {
        throw Error(0,"RealWorldDataImporter(constructor): unexpected end of conf file!", 0);
    }
    if (!confFile.eof())
    {
        getline(confFile, _dm_file);
    } else {
        throw Error(0,"RealWorldDataImporter(constructor): unexpected end of conf file!", 0);
    }
    confFile.close();
}
RealWorldDataImporter::RealWorldDataImporter() : DataImporter() {}
int RealWorldDataImporter::get_num_days() {
    return 7;
}

