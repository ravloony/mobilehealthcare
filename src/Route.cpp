/*!
* \file Route.cpp
* \brief Route class implementation file.
* \author Thomas Macdonald
* \date Thu Mar  4 14:29:01 CET 2010
*/
#include "Route.hpp"
#include "Error.hpp"
#include "Debug.hpp"

int Route::_next_id=0;

Route::Route()
{
  _day = 0;
  _cost = 0.0;
  _length=0;
  _consistency = 0;
  _order = 0;
}

Route::Route(const Route& r)
{
  _distance_matrix=r._distance_matrix;
  _nurse=r._nurse;
  _day=r._day;
  _vertices=r._vertices;
  _cost = r._cost;
  _length = r._length;
  _consistency=r._consistency;
  _order=r._order;
  _id=r._id;
}


Route::~Route()
{
  _distance_matrix = 0;
  _nurse = 0;
}

int Route::get_id()
{
  return _id;
}


size_t Route::size()
{
  return _vertices.size();
}

/*!
*  inserts a request at the specified position (starts at 0).
*
*  Assumes that request _can_ be inserted at that position.
*/
void Route::insert(RequestPtr r, int position)
{
  if (position>(int)size() || position<0)
  {
    cout << __PRETTY_FUNCTION__ << endl;
    throw Error(0,"Route::insert -> index out of bounds",0);
  }
  if (!insertionPossible(r,position))
  {
    ofstream logfile("log",ios::app);
    if (logfile)
    {
      logfile << "============ insertion error ==============" << endl;
      logfile << "Route is: " << endl;
      logfile << *this << endl;
      logfile << "Request is:\n" << *r << endl;
      logfile << "we were trying to insert at position " << position << endl;
      if (position>0)
	logfile << "distance to previous : " << _distance_matrix->getDistance(_vertices[position-1].get_client_id(),r->get_client_id()) << endl;
      if (position<size())
	logfile << "distance to next : " << _distance_matrix->getDistance(r->get_client_id(),_vertices[position].get_client_id()) << endl;
      logfile.close();
    }
    throw Error(0,"Route::insert -> Insertion not possible",0);
  }
  //what time do we begin?
  double begin=0;
  //How long do we wait?
  double wait=0;
  try{
    _length+=getInsertionCost(r,position);
  } catch (const Error& e)
  {
    throw Error(0,"Route::insert -> "+e.desc(),e.level()+1);
  }
  _order++;
  Vertex tmpVertex(wait,begin,_order, r);
  vector<Vertex>::iterator vIt = _vertices.begin();
  _vertices.insert(vIt+position,tmpVertex);
   //update vertices
   _vertices[0].set_begin(_vertices[0].get_tw_start());
   if (_vertices.size()==1)
     return;
   double tmpBegin = _vertices[0].get_end();
   for (unsigned int i = 1; i< _vertices.size(); i++)
   {
     _vertices[i].set_begin(max<double>(tmpBegin+_distance_matrix->getDistance(_vertices[i-1].get_client_id(),_vertices[i].get_client_id()),_vertices[i].get_tw_start()));
     tmpBegin=_vertices[i].get_end();
   }
}

/*!
*  checks whether a request can be inserted at the specified position.
*/
bool Route::insertionPossible(RequestPtr r, int position)
{
//   Debug::print<string>("checking for insertion... ");
  if (position>(int)size() || position<0)
      throw Error(0,"Route::insertionPossible : Index out of bounds",0);
  try {
    if (_vertices.size()==0)
    {
//       cout << "empty route" << endl;
      return true;
    } else {
      if (position==(int)size())
      {
//  	cout << "last pos" << endl;
	return canRequestGoAfter(r,(int)size()-1);
      }
      double cost;
      if (position==0)
      {
	cost = r->get_early();
// 	cout << "position = 0 -- cost : " << cost << endl;
      } else {
	Vertex theOneBefore = _vertices[position-1];
	Vertex theOneAfter = _vertices[position];
	//do the time windows correspond?
// 	cout << "time windows: before : " << theOneBefore.get_tw_start() << "->" << theOneBefore.get_tw_end() << "|| current : " << r->get_early() << "->" << r-> get_late() << " || after : " << theOneAfter.get_tw_start() << "->" << theOneAfter.get_tw_end() << endl;

	if ((theOneBefore.get_tw_end()<r->get_early() && theOneAfter.get_tw_start()>r->get_late())
	  || (theOneBefore.get_tw_end()==r->get_late() && theOneAfter.get_tw_start()==r->get_early())
	  || (theOneBefore.get_tw_end()==r->get_late() && theOneAfter.get_tw_start()>r->get_late())
	  || (theOneBefore.get_tw_end()<r->get_early() && theOneAfter.get_tw_start()==r->get_early()))
	{
// 	  cout << "time windows: before : " << theOneBefore.get_tw_start() << "->" << theOneBefore.get_tw_end() << "|| current : " << r->get_early() << "->" << r-> get_late() << " || after : " << theOneAfter.get_tw_start() << "->" << theOneAfter.get_tw_end() << endl;
	  if (!theOneBefore.get_request()->sameTimeWindow(r))
	  {
	    cost = max<double>(theOneBefore.get_end()+_distance_matrix->getDistance(theOneBefore.get_client_id(),r->get_client_id()),r->get_early());
// 	    cout << "setting cost to beginning of time window or distance from last request -- ";
	  } else {
	    cost = theOneBefore.get_end()+_distance_matrix->getDistance(theOneBefore.get_client_id(),r->get_client_id());
// 	    cout << "setting cost to distance from last request -- ";
	  }
	} else {
//   	  cout << "wrong time window...";
	  return false;
	}
// 	cout << "cost : " << cost << endl;
      }
      cost += r->get_service_time();
//       cout << "adding service time for potential request -- cost : " << cost << endl;
      if (cost>r->get_late())
      {
//  	cout << "time window exceeded (1)" << endl;
	return false;
      }
      cost += _distance_matrix->getDistance(r->get_client_id(),_vertices[position].get_client_id());
//       cout << "adding distance to next request -- cost : " << cost << endl;
      if (r->get_late()<_vertices[position].get_tw_start() && cost < r->get_late())
      {
// 	cout << "end of time window and space left" << endl;
	return true;
      }
      // we loop through the requests, recalculating as we go.
      for (unsigned int i = position; i<_vertices.size(); i++)
      {
// 	cout << "checking vertice : "<< _vertices[i] << endl;
	//we add the service time to the current end time
	cost += _vertices[i].get_length();
// 	cout << "adding service time -- cost : " << cost << endl;
	//if this leads to overlapping the time window we stop - it is wrong
	if (cost>_vertices[i].get_tw_end())
	{
/*	  cout << "distance to next request: " <<_distance_matrix->getDistance(r->get_id(),_vertices[position].get_id());
 	  cout << "Time window exceeded (2)" << endl;*/
	  
	  return false;
	}
	//if it is not the last request we add the time to next target, if it is we return true - the route works (time from last request to nurse is not counted)
	if (i<_vertices.size()-1)
	{
	  cost += _distance_matrix->getDistance(_vertices[i].get_request()->get_client_id(),_vertices[i+1].get_request()->get_client_id());
// 	  cout << "adding distance -- cost : " << cost << endl;
	} else {
// 	  cout << "last request time window not exceeded" << endl;
	  return true;
	}
	//if this is the last request of a time window and the return journey does not overlap the time window we can return safely
	if (_vertices[i].get_tw_end()<_vertices[i+1].get_tw_start() && cost < _vertices[i].get_tw_end())
	{
// 	  cout << "last request in tw -- space left" << endl;
	  return true;
	}
      }
    }
//     return false;
  } catch (const exception& e) {
    throw Error(0,"Route::insertionPossible : Unknown error.",0);
  }
}

bool Route::checkSkills(RequestPtr r)
{
  if (r->get_skill()<=_nurse->get_skill())
  {
/*    cout << "skill level sufficient"<< endl;*/
    return true;
  }
  return false;
}

bool Route::checkDay(RequestPtr r)
{
  if  (r->get_day()==_day)
  {
/*    cout << "right day" << "(" << r->get_day() << "==" << _day << ")" << endl;*/
    return true;
  }
  return false;
}


bool Route::canRequestGoAfter(RequestPtr r, int i)
{
  return   (_vertices[i].get_tw_start()<=r->get_early() && _vertices[i].get_tw_end()<=r->get_late() && _vertices[i].get_end()+_distance_matrix->getDistance(_vertices[i].get_client_id(),r->get_client()->get_id())+r->get_service_time()<r->get_late());
}

double Route::getInsertionCost(RequestPtr request, unsigned int position)
{
  if (position>size() || position<0)
    throw Error(0,"Route::getInsertionCost : Index out of bounds",0);
  double cost;
//   cout << "getting insertion cost >>>>>  size : " << size() << ", position : " << position;
  int nurseID = _nurse->get_id();
  int requestID = request->get_client_id();
  double distFromNurseToRequest = _distance_matrix->getDistance(nurseID,requestID);
  double distFromRequestToNurse = _distance_matrix->getDistance(requestID,nurseID);
  
  if (size()==0)
  {
    //cout << "size = 0" << endl;
    cost = distFromNurseToRequest+distFromRequestToNurse;
  } else if (position==size())
  {
//     cout << "position = size" << endl;
    int prevID = _vertices[position-1].get_client_id();
    double distFromPrevToRequest = _distance_matrix->getDistance(prevID,requestID);
    double distFromPrevToNurse = _distance_matrix->getDistance(prevID,nurseID);

    cost = distFromPrevToRequest+distFromRequestToNurse-distFromPrevToNurse;
  } else if (position==0)
  {
//     cout << "position=0" << endl;
    int nextID = _vertices[position].get_client_id();
    double distFromNurseToNext = _distance_matrix->getDistance(nurseID,nextID);
    double distFromRequestToNext = _distance_matrix->getDistance(requestID,nextID);
    cost = distFromNurseToRequest+distFromRequestToNext-distFromNurseToNext;
//    cout << "cost = " << distFromNurseToRequest << "+" << distFromRequestToNext << "-" << distFromNurseToNext << endl;
  } else {
  int nextID = _vertices[position].get_client_id();
  double distFromRequestToNext = _distance_matrix->getDistance(requestID,nextID);
  int prevID = _vertices[position-1].get_client_id();
  double distFromPrevToRequest = _distance_matrix->getDistance(prevID,requestID);
  double distFromPrevToNext = _distance_matrix->getDistance(prevID,nextID);
  
  cost = distFromPrevToRequest+distFromRequestToNext-distFromPrevToNext;
  }
  //are we adding a nurse to this client?
//   if (request->get_client()->nurse_in(_nurse) && request->get_client()->get_no_of_nurses()!=0)
//   {
//     //no
// //     cout << "not adding nurse" << endl;
//     return cost;
//   } else {
//     //yes
// //     cout << "adding nurse" << endl;
//     return cost + 1000.0;
//   }
  return cost;
}

double Route::get_cost()
{
  return _length;
}

double Route::get_consistency()
{
  return _consistency;
}


Request* Route::get_request(int index)
{
  assert(index>=0);
  assert(index<(int)size());
  return _vertices[index].get_request();
}

double Route::get_sum_of_distances(int index)
{
  assert(index>=0 && index<(int)size());
  if (size()==1) {
    return _distance_matrix->getDistance(_nurse->get_id(),_vertices[index].get_client_id())+_distance_matrix->getDistance(_vertices[index].get_client_id(),_nurse->get_id());
  }
  if (index==0)
    return _distance_matrix->getDistance(_nurse->get_id(),_vertices[index].get_client_id())+_distance_matrix->getDistance(_vertices[index].get_client_id(),_vertices[index+1].get_client_id());
  if (index==(int)(size()-1))
    return _distance_matrix->getDistance(_vertices[index-1].get_client_id(),_vertices[index].get_client_id())+_distance_matrix->getDistance(_vertices[index].get_client_id(),_nurse->get_id());
  return _distance_matrix->getDistance(_vertices[index-1].get_client_id(),_vertices[index].get_client_id())+_distance_matrix->getDistance(_vertices[index].get_client_id(),_vertices[index+1].get_client_id());
}

std::ostream& operator<<(ostream& stream, const Route route)
{
  int size = route._vertices.size();
  stream << endl << "Route length: " << route._length  << ", Day: " << route._day << ", nurse: " << route._nurse->get_id() <<  endl;
  if (size>0)
    stream << "distance : " << route._distance_matrix->getDistance(route._nurse->get_id(),route._vertices[0].get_client_id()) << endl;
  for (unsigned int i=0; i< route._vertices.size(); i++)
  {
    stream << route._vertices[i];
    if (i<route._vertices.size()-1)
      stream << "distance : " << route._distance_matrix->getDistance(route._vertices[i].get_client_id(),route._vertices[i+1].get_client_id()) << endl;
  }
  if (size>0)
    stream << "distance : " << route._distance_matrix->getDistance(route._vertices[size-1].get_client_id(),route._nurse->get_id()) << endl;
  return stream;
}

void Route::erase(int index)
{
  assert(index>=0 && index<(int)size());
  _vertices.erase(_vertices.begin()+index);
}

void Route::update_values()
{
  _length=0;
  if (_vertices.size()==0)
    return;
  _vertices[0].set_begin(_vertices[0].get_tw_start());
  _length+=_distance_matrix->getDistance(_nurse->get_id(),_vertices[0].get_client_id());
  if (_vertices.size()>1)
  {
    double tmpBegin = _vertices[0].get_end();
    for (unsigned int i=1; i< _vertices.size(); i++)
    {
      _length+=_distance_matrix->getDistance(_vertices[i-1].get_client_id(),_vertices[i].get_client_id());
      _vertices[i].set_begin(max<double>(tmpBegin+_distance_matrix->getDistance(_vertices[i-1].get_client_id(),_vertices[i].get_client_id()),_vertices[i].get_tw_start()));
      tmpBegin=_vertices[i].get_end();
    }
  }
  _length+=_distance_matrix->getDistance(_vertices[_vertices.size()-1].get_client_id(),_nurse->get_id());
  return;
}

int Route::get_id_of(int vertex)
{
  return _vertices[vertex].get_client_id();
}

int Route::get_request_id_of(int vertex)
{
  return _vertices[vertex].get_request_id();
}

int Route::get_vertex_pos_by_request_id(int id)
{
  for (unsigned int i=0; i<_vertices.size(); i++)
  {
    if (_vertices[i].get_request_id()==id)
    {
      return i;
    }
  }
  return -1;
}

vector< std::pair< double, double > > Route::get_points_in_order()
{
  std::vector<std::pair<double,double> > points;
  points.push_back(_nurse->get_point());
  for (unsigned int i=0; i<_vertices.size(); i++)
  {
    points.push_back(_vertices[i].get_point());
  }
  points.push_back(_nurse->get_point());
  return points;
}


Route::Route(Nurse* nurse, DistanceMatrix* d) : _nurse(nurse), _distance_matrix(d) {
    _day=0;
    _cost=0.0;
    _length=0;
    _consistency=0.0;
    _id=_next_id;
    _next_id++;
    _order=0;
}
