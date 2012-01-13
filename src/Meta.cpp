#include "Meta.hpp"

Meta::Meta()
{

}

Meta::Meta(DataImporter* d, Init* init)
{
  _data_importer = d;
  _init = init;
  Solution s;
  std::vector<Nurse*> nurses = d->get_nurses();
  DistanceMatrix* dm = d->get_distance_matrix();
//   cout << *dm;
  for (unsigned int i = 0; i<nurses.size();i++)
  {
    for (int j = 0; j<d->get_num_days();j++)
    {
      Route r(nurses[i],dm);
      r.set_day(j);
      s.add_route(r);
    }
  }
  _solution = s;
  Statistics stats(d->get_requests().size(),d->get_clients().size(),d->get_nurses().size());
  _stat=stats;
}

void Meta::apply_init()
{
  _request_pool.assign(_data_importer->get_requests().begin(),_data_importer->get_requests().end());
  try {
  _solution = _init->execute(_data_importer,_solution, _request_pool);
  } catch (const Error& e)
  {
    throw Error(0,"Meta::apply_init -> "+e.desc(),e.level()+1);
  }
  _request_pool.clear();
  if (_init->has_uninserted_requests())
    {
      vector<Request*> uninserted = _init->get_uninserted_requests();
      for (unsigned int i=0; i<uninserted.size(); i++)
      {
	_request_pool.push_back(uninserted[i]);
      }
    }
  cout << _solution.get_total_cost() << endl;
  _stat.add_after_init(_solution);
}

Solution& Meta::get_solution()
{
  return _solution;
}

void Meta::apply_main()
{
  double alpha = 0.9;
  double temp = 60;
  double minTemp = 5;
  int maxNumberOfIterations = 150;
  int iter=0;
  int count=0;
  int plateau=100;
  vector<Request*> tmpRequestPool;
  vector<Request*> bestUninsertedRequests;
  cout << "in main metaheuristic\n" ;
  _best_solution=_solution;
  ofstream plot_numbers("plot_numbers.txt");
  while (temp>minTemp/* && iter<maxNumberOfIterations*/)
  {
    count = 0;
    while (count<plateau)
    {
      Solution stemp = _solution;
      tmpRequestPool = _request_pool;
      {//begin neighbour calculation
      int deleterSelect = rand()%_deleters.size();
      int inserterSelect = rand()%_inserters.size();
      cout << "selected inserter " << inserterSelect << ", deleter " << deleterSelect << endl;
      vector<Request*> deleted = _deleters[deleterSelect]->execute(stemp);
      for (unsigned int i=0; i<deleted.size(); i++)
      {
	tmpRequestPool.push_back(deleted[i]);
      }
      cout << "there are " << tmpRequestPool.size() << " requests in pool" << endl;
      _inserters[inserterSelect]->clear_uninserted_requests();
      try {
	_inserters[inserterSelect]->execute(_data_importer,stemp,tmpRequestPool);
      } catch  (const Error& e) {
/*	ofstream logfile("log",ios::app);
	if (logfile)
	{
	  logfile << "(greedy) Route number: " << r << endl;
	  logfile.close();
	}*/
	throw Error(e.number(),"Meta::apply_main -> " + e.desc(),e.level()+1);
      }
      tmpRequestPool.clear();
      if (_inserters[inserterSelect]->has_uninserted_requests())
      {
	vector<Request*> uninserted = _inserters[inserterSelect]->get_uninserted_requests();
	for (unsigned int i=0; i<uninserted.size(); i++)
	{
	  tmpRequestPool.push_back(uninserted[i]);
	}
	_inserters[inserterSelect]->clear_uninserted_requests();
      } else {
	cout << "no requests uninserted\n";
      }
	//end neighbour calculation
      }
      cout << "total requests : " << _data_importer->get_requests().size() << ", number of requests in solution : " << _solution.get_number_of_requests() << "\n";
      assert (_data_importer->get_requests().size()>=stemp.get_number_of_requests());
      //save the current solution if it is good
      cout << " == current cost : " << _solution.get_total_cost() << " == new cost : " << stemp.get_total_cost() << " == best cost : " << _best_solution.get_total_cost() << endl;
      double choice = (rand() / ((double)(RAND_MAX)));
      double moveProb = get_move_prob(stemp,_solution,temp);
      cout << moveProb << ">" << choice << "???...";
      if (moveProb>choice)
      {
	cout << "accepted.\n";
	_solution=stemp;
	_request_pool=tmpRequestPool;
      } else {
	cout << "not accpeted.\n";
      }
      if (_solution.get_number_of_requests()>_best_solution.get_number_of_requests())
      {
	_best_solution=_solution;
      } else {
	if (_solution.get_number_of_requests()==_best_solution.get_number_of_requests() && _solution.get_total_cost()<_best_solution.get_total_cost())
	{
	  _best_solution=_solution;
	}
      }
      
      double totalCost = _solution.get_total_cost();
      if (plot_numbers)
	plot_numbers << totalCost << "\n";
      count++;
      cout << count << "/" << plateau << endl;
    }
/*    if (_solution.get_number_of_requests()==_best_solution.get_number_of_requests() && _best_solution.get_total_cost()<_solution.get_total_cost()*10)
      _solution=_best_solution;*/
    iter++;
    temp*=alpha;
    cout << "================= temp = " << temp << " ===================\n";
  }
  if (plot_numbers)
    plot_numbers.close();
  _stat.add_final(_best_solution);
  cout << _stat;
  
  _stat.print_latex();
//   cout << " Best solution found : " << _best_solution.get_total_cost() << endl;
}

double Meta::get_move_prob(Solution& currentSol, Solution& newSol, double temp)
{
  if (newSol.get_number_of_requests()>currentSol.get_number_of_requests())
  {
     cout << " solution has more requests, accepting...";
    return 1;
  }
  if( newSol.get_total_cost()<currentSol.get_total_cost())
  {
     cout << " solution is better, accepting...";
    return 1.0;
  }
  cout << "solution worse, accepting with probability " << exp((currentSol.get_total_cost()-newSol.get_total_cost())/(100*temp)) << "\n";
  return exp((currentSol.get_total_cost()-newSol.get_total_cost())/(100*temp));
}

void Meta::display_solution()
{
  _solution.display();
}

void Meta::add_deleter(Delete* del)
{
  _deleters.push_back(del);
}

void Meta::add_inserter(Init* ins)
{
  _inserters.push_back(ins);
}

Statistics& Meta::get_stat()
{
  return _stat;
}

Meta::~Meta()
{

}
