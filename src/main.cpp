/*!
* \file main.cpp
* \brief This is the entry point for the program.
* \author Thomas Macdonald
* \date 2010-02-22
*
* This is the entry point for the program.
*
*/


#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <fstream>
#include <string>
#include <algorithm>
#include <time.h>
#include <mcheck.h>
//#include <google/profiler.h>


#include "DataStructures/DistanceMatrix.hpp"
#include "Client.hpp"
#include "Nurse.hpp"
#include "DataImporters/RealWorldDataImporter.hpp"
#include "DataImporters/GoldenDataImporter.hpp"
#include "DataImporters/FDataImporter.hpp"
#include "DataImporters/MyDataImporter.hpp"
#include "Debug.hpp"
#include "Init/RegretInit.hpp"
#include "Init/GreedyInit.hpp"
#include "Init/FInit.hpp"
#include "Init/RandomInit.hpp"
#include "Meta.hpp"
#include "Init/TestInit.hpp"
#include "DeletionOperators/DistanceDelete.hpp"
#include "DeletionOperators/ClientDelete.hpp"
#include "DeletionOperators/RandomClientDelete.hpp"

void help(char *);
void term_func();

int main(int argc, char **argv) {
  /*/*mtrace();
  string pfname = "/tmp/profile1";
  ProfilerStart(pfname.c_str());*/
  set_terminate(term_func);
  clock_t start = clock();
  
  srand ( time(NULL) );

  if (argc!=4)
  {
    help(argv[0]);
    exit(1);
  }
  int mode = atoi(argv[1]);
  string confFileName(argv[2]);
  /* get basename */
  string::size_type idx = confFileName.find_last_of('.');
  string basename;
  string tmpbasename;
  if (idx != string::npos) {
    tmpbasename = confFileName.substr(0, idx);
    string::size_type idx2 = tmpbasename.find_last_of('/');
    if (idx2 != string::npos)
      basename = tmpbasename.substr(idx2+1);
    else
      basename = tmpbasename;
  } else {
    tmpbasename = confFileName;
    string::size_type idx2 = tmpbasename.find_last_of('/');
    if (idx2 != string::npos)
      basename = tmpbasename.substr(idx2+1);
    else
      basename = tmpbasename;
  }
  int initmode = atoi(argv[3]);
  DataImporter* d;
  if (mode==1) {
    RealWorldDataImporter* r = new RealWorldDataImporter(confFileName);
    d=r;
    std::cout << "Data import done." << endl;
  } else if (mode==2) {
    GoldenDataImporter* g = new GoldenDataImporter(confFileName);
    d=g;
  } else if (mode==3) {
    FDataImporter* f = new FDataImporter();
    d=f;
  } else if (mode==4) {
    MyDataImporter* m = new MyDataImporter(confFileName);
    d=m;
  } else {
    help(argv[0]);
  }
  time_t rawtime;
  time( &rawtime );
  ofstream logfile("log",ios::app);
  if (logfile)
  {
    logfile << "===============\n=================\nNew run on " << ctime(&rawtime) << endl;
    logfile.close();
  }
  //import data
  try {
    d->run();
  } catch (const Error& e) {
    cout << e.desc() << endl;
    cout.flush();
    exit(1);
  }
  //d->plot();
//   cout << *d;
  //run construction heuristic
  cout << "Running Construction Heuristic" << endl;
  Init* init;
  if (initmode==1)
  {
    RegretInit* rinit = new RegretInit();
    init = rinit;
  } else if (initmode==2) {
    GreedyInit* ginit = new GreedyInit();
    init = ginit;
  } else if (initmode==3) {
    FInit* finit = new FInit();
    init = finit;
  } else if (initmode==4) {
    TestInit* tinit = new TestInit();
    init = tinit;
  }
  vector<Route> routes;
  Meta meta(d,init);
  try {
    
    meta.apply_init();
    
  } catch (const Error& e) {
    cout << e.desc() << endl;
    cout.flush();
    exit(1);
  }
  DistanceDelete* dd = new DistanceDelete(10);
  meta.add_deleter(dd);
  ClientDelete* cd = new ClientDelete(10);
  meta.add_deleter(cd);
  RandomClientDelete* rcd = new RandomClientDelete(10);
  meta.add_deleter(rcd);
  RegretInit* rinit2 = new RegretInit();
  meta.add_inserter(rinit2);
  GreedyInit* ginit2 = new GreedyInit();
  meta.add_inserter(ginit2);
/*  FInit* finit2 = new FInit();
  meta.add_inserter(finit2);*/
//   RandomInit* randinit = new RandomInit();
//   meta.add_inserter(randinit);
  routes = meta.get_solution().get_routes();
  cout << "Finished Construction Heuristic" << endl;
  for (unsigned int i=0; i<routes.size(); i++)
  {
    cout << "Route number " << i;
    cout << routes[i] << endl;
  }
  cout << "Done" << endl;
  clock_t end = clock();
  double time_taken = ((double)end - (double)start)/CLOCKS_PER_SEC;
  cout << " Length of solution: " << meta.get_solution().get_total_length() << "  || Consistency average: " << meta.get_solution().get_consistency_average() << "  || Total consistency: " << meta.get_solution().get_total_consistency() << " || time taken: " << time_taken << " seconds " << endl;
//   cout << *d;
  cout << "Running main algorithm" << endl;
  try {
  meta.apply_main();
  } catch  (const Error& e) {
/*	ofstream logfile("log",ios::app);
	if (logfile)
	{
	  logfile << "(greedy) Route number: " << r << endl;
	  logfile.close();
	}*/
	cout << "error found : ";
	cout << e.desc() << endl;
	ofstream errorResult("errorresult.log");
	if (errorResult)
	{
	  errorResult << meta.get_solution();
	}
      }
  int no_of_nurses = d->get_nurses().size();
  int no_of_clients = d->get_clients().size();
  int no_of_requests = d->get_requests().size();
  ostringstream oss;
  oss << "output_" << no_of_clients << "_" << no_of_requests << "_" << no_of_nurses;
  string outputFileName = oss.str();
  meta.get_solution().plot(outputFileName);
  for (unsigned int i=0;i<d->get_num_days();i++)
  {
    meta.get_solution().plot_by_day(outputFileName,i);
  }
  oss << ".txt";
  ostringstream oss2;
  oss2 << "results/" << basename << "-" << oss.str();
  string resultsFileName = oss2.str();
  ofstream resultsFile(resultsFileName.c_str(),ios::app);
  if (resultsFile)
  {
    resultsFile << meta.get_stat();
    resultsFile << "===\n";
    resultsFile.close();
  }
  delete dd;
  delete init;
  delete d;
//   ProfilerStop();
//   muntrace();
  return 0;
}


void help(char* program_name)
{
  cout << "Mobile Health Care" << endl;
  cout << "Usage: " << program_name << " importmode filename initmode" << endl;
  cout << "Import Modes:\n\
	   1 : Real World Data\n\
	   2 : Golden Data\n\
	   3 : Fake Data\n\
	   4 : My Data\n";
  cout << "Init Modes:\n\
	   1 : Regret Init\n\
	   2 : Greedy Init\n\
	   3 : Finit\n\
	   4 : Test Init\n";
}

void term_func()
{
  cout << "dude, we crashed"  << endl;
}