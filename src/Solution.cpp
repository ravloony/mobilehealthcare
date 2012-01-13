#include "Solution.hpp"


Solution::Solution()
{
  _total_length=0;
  _total_consistency=0;
  _number_of_requests=0;
}

void Solution::add_route(Route& route)
{
  _routes.push_back(route);
  _total_length+=route.get_cost();
//   cout << "adding " << route.get_consistency() << " to consistency" << endl;
  _total_consistency+=route.get_consistency();
  _number_of_requests+=route.size();
}

void Solution::remove_routes()
{
  _routes.clear();
  _total_consistency=0;
  _total_length=0;
  _number_of_requests=0;
}


std::vector< Route, std::allocator< Route > >& Solution::get_routes()
{
  return _routes;
}

Solution::Solution(vector< Route >& routes)
{
  _total_consistency=0.0;
  _total_length=0.0;
  _routes = routes;
  for (unsigned int i=0; i<routes.size(); i++)
  {
    _total_length+=routes[i].get_cost();
    _total_consistency+=routes[i].get_consistency();
    _number_of_requests+=routes[i].size();
  }
}

void Solution::display()
{
  for (unsigned int i=0; i<_routes.size();i++)
  {
    std::cout << _routes[i];
  }
}

double Solution::get_total_cost()
{
  return _total_length+_total_consistency;
}

double Solution::get_total_consistency() const
{
  return _total_consistency;
}

int Solution::get_number_of_requests() const
{
  return _number_of_requests;
}


double Solution::get_consistency_average()
{
  double sum = 0;
  int count = 0;
  for (unsigned int i=0; i< _routes.size(); i++)
  {
    for (unsigned int j=0; j<_routes[i].size();j++)
    {
      if (_consistency_map.find(_routes[i].get_request(j)->get_client_id())!=_consistency_map.end())
      {
	sum+=_consistency_map[_routes[i].get_request(j)->get_client_id()].size();
	count++;
      }
    }
  }
  return (sum/count);
}


bool Solution::check_day(Request* r, int route)
{
  return _routes[route].checkDay(r);
}

bool Solution::check_skills(Request* r, int route)
{
  return _routes[route].checkSkills(r);
}

double Solution::getInsertionCost(Request* r, int route, int position)
{
  double cost=0;
  cost += _routes[route].getInsertionCost(r, position);
  if (_consistency_map.find(r->get_client_id())!=_consistency_map.end())
  {
//     vector<int> tmpVec;
//     tmpVec.push_back(_routes[route].get_nurse()->get_id());
//     _consistency_map[r->get_id()]=tmpVec;
//   } else {
    bool found = false;
    for (unsigned int i=0; i<_consistency_map[r->get_client_id()].size(); i++)
    {
      if (_consistency_map[r->get_client_id()][i]==_routes[route].get_nurse()->get_id())
      {
	found=true;
	break;
      }
    }
    if (!found) //if nurse not already dealing with client
    {
       cost +=  1000;
    }
  }
  return cost;
}

bool Solution::insertionPossible(Request* r, int route, int position)
{
  return _routes[route].insertionPossible(r,position);
}

void Solution::insert(Request* r, int route, int position)
{
  assert (route>=0 && route<(int)_routes.size());
  _total_length+=_routes[route].getInsertionCost(r,position);
  try
  {
    _routes[route].insert(r,position);
  } catch (const Error& e) {
    throw Error(e.number(),"Solution::insert -> " + e.desc(),e.level()+1);
  }
  if (_consistency_map.find(r->get_client_id())==_consistency_map.end())
  {
    vector<int> tmpVec;
    tmpVec.push_back(_routes[route].get_nurse()->get_id());
    _consistency_map[r->get_client_id()]=tmpVec;
  } else {
    bool found = false;
    for (unsigned int i=0; i<_consistency_map[r->get_client_id()].size(); i++)
    {
      if (_consistency_map[r->get_client_id()][i]==_routes[route].get_nurse()->get_id())
      {
	found=true;
	break;
      }
    }
    if (!found) //if nurse not already dealing with client
    {
/*      cout << "adding consistency penalty" << endl;*/
      _consistency_map[r->get_client_id()].push_back(_routes[route].get_nurse()->get_id());
      _total_consistency+=1000;
    }
  }
  _number_of_requests++;
}

size_t Solution::size()
{
  return _routes.size();
}

int Solution::size_of_route(int route)
{
  return (int)_routes[route].size();
}

void Solution::erase(int route, int vertex)
{
  _routes[route].erase(vertex);
  _number_of_requests--;
}

void Solution::erase_request_by_id(int route, int id)
{
  int pos = _routes[route].get_vertex_pos_by_request_id(id);
  if (pos!=-1)
  {
    _routes[route].erase(pos);
  } else {
    throw Error(0,"Vertex does not exist",0);
  }
}

int Solution::get_sum_of_distances(int route,int vertex)
{
  return _routes[route].get_sum_of_distances(vertex);
}

void Solution::update_values()
{
  _consistency_map.clear();
  _total_length=0;
  _total_consistency=0;
  _number_of_requests=0;
  for (unsigned int route=0; route<_routes.size(); route++)
  {
    _routes[route].update_values();//update vertice values
    _total_length+=_routes[route].get_cost(); //update cost
    _number_of_requests+=_routes[route].size();
    for (unsigned int vertex=0; vertex<_routes[route].size(); vertex++) //update consistency
    {
      int id = _routes[route].get_id_of(vertex);
      if (_consistency_map.find(id)==_consistency_map.end())
      {
	vector<int> tmpVec;
	tmpVec.push_back(_routes[route].get_nurse()->get_id());
	_consistency_map[id]=tmpVec;
      } else {
	bool found = false;
	for (unsigned int i=0; i<_consistency_map[id].size(); i++)
	{
	  if (_consistency_map[id][i]==_routes[route].get_nurse()->get_id())
	  {
	    found=true;
	    break;
	  }
	}
	if (!found) //if nurse not already dealing with client
	{
	  /*      cout << "adding consistency penalty" << endl;*/
	  _consistency_map[id].push_back(_routes[route].get_nurse()->get_id());
	  _total_consistency+=1000;
	}
      }
    }
  }
}

int Solution::get_least_consistent_client()
{
  int id=0;
  int size=0;
  std::map<int,std::vector<int> >::iterator it;
  for (it=_consistency_map.begin(); it!=_consistency_map.end(); it++)
  {
    if ((int)(*it).second.size()>size)
    {
      id=(*it).first;
    }
  }
  return id;
}

std::vector<std::pair<int, int> > Solution::get_request_ids_by_client_id(int id)
{
  std::vector<std::pair<int, int> > retVec;
  for (unsigned int route=0; route<_routes.size(); route++)
  {
    for (unsigned int vertex=0; vertex<_routes[route].size(); vertex++)
    {
      if (_routes[route].get_id_of(vertex)==id)
      {
/*	cout << "got route " << route << ", vertex " << vertex << endl;*/
	pair<int, int> newPair(route,_routes[route].get_request_id_of(vertex));
	retVec.push_back(newPair);
      }
    }
  }
  return retVec;
}


Request* Solution::get_request(int route, int vertex)
{
/*  cout << "getting request from route " << route << " at position " << vertex << endl;*/
  return _routes[route].get_request(vertex);
}

Request* Solution::get_request_by_id(int route, int id)
{
  int pos = _routes[route].get_vertex_pos_by_request_id(id);
  if (pos!=-1)
  {
    return _routes[route].get_request(pos);
  } else {
    throw Error(0,"Vertex does not exist",0);
  }
}

int Solution::get_random_client_id()
{
  int route = rand()%_routes.size();
  while (_routes[route].size()==0)
    route = rand()%_routes.size();
  int vertex = rand()%_routes[route].size();
  return _routes[route].get_id_of(vertex);
}

Route& Solution::get_route(int route)
{
  return _routes[route];
}


double Solution::get_total_length() const
{
  return _total_length;
}

void Solution::plot(string name)
{
  Plot p(_routes[0].get_points_in_order(),name,"",std::pair<string,string>("x","y"));
  for (unsigned int i=0; i<_routes.size(); i++)
  {
    if (_routes[i].size()!=0)
    {
      std::vector<std::pair<double, double> > points = _routes[i].get_points_in_order();
      p.add_points(points);
    }
  }
//   p.plot();
  p.set_name(name);
  p.plot_to_file();
}

void Solution::plot_by_day(string name, int day)
{
  ostringstream oss;
  oss << name << "_day_" << day;
  string fullname = oss.str();
  std::vector<std::vector<std::pair<double, double> > > pointsVec;
  for (unsigned int i=0; i<_routes.size(); i++)
  {
    if (_routes[i].size()!=0 && _routes[i].get_day()==day)
    {
      std::vector<std::pair<double, double> > points = _routes[i].get_points_in_order();
      pointsVec.push_back(points);
    }
  }
  if (pointsVec.size()>0)
  {
    Plot p(pointsVec[0],fullname,"",std::pair<string,string>("x","y"));
    for (unsigned int i=1; i<pointsVec.size(); i++)
    {
	p.add_points(pointsVec[i]);
    }
//   p.plot();
    p.set_name(fullname);
    p.plot_to_file();
  }
}


Solution::~Solution()
{
}

ostream& operator<<(ostream& stream, const Solution sol)
{
  stream << "Total length: " << sol._total_length << endl;
  stream << "Total consistency: " << sol._total_consistency << endl;
  for (unsigned int i=0; i<sol._routes.size();i++)
  {
    stream << sol._routes[i];
  }
}

