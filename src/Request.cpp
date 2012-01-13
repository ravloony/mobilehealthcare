/*!
* \file Request.cpp
* \brief Request class implementation file.
* \author Thomas Macdonald
* \date Thu Mar  4 14:29:01 CET 2010
*/
#include "Request.hpp"
#include "Client.hpp"
#include "Error.hpp"

using namespace std;
int Request::_next_id=0;
Request::Request()
{

}

Request::~Request()
{
  _client = 0;
}

Request::Request(double early, double late, double s_time, double r_time, int skill, int day)
{
  _skill = skill;
  _early = early;
  _late = late;
  _day = day;
  _requested_time = r_time;
  _service_time = s_time;
  _local_id=_next_id;
  _next_id++;
}

int Request::get_local_id()
{
  return _local_id;
}


void Request::add_client(Client* cli)
{
  _client = cli;
//   std::cout << "adding client to request" << endl;
}

bool Request::sameTimeWindow(Request* r)
{
  return (r->_early == _early && r->_late == _late);
}

bool Request::sameTimeWindow(Request r)
{
  return (r._early == _early && r._late == _late);
}

/*!
*	Returns the position of the time window of the current request wrt r: -1 if this is before r, 0 if it is the same time window, 1 if it is afterwards.
*/
int Request::timeWindowPos(Request* r)
{
  if (sameTimeWindow(r))
    return 0;
  if (_early<r->_early && _late<r->_late)
    return -1;
  if (_early>r->_early && _late>r->_late)
    return 1;
  throw Error(0,"Time window is neither before or after - this is strange!",0);
}

ostream& operator<<(ostream& stream, const Request& r)
{
   stream << r._skill << " | " << r._early << " to " << r._late << " on day " << r._day << " for " << r._service_time << "minutes, servicing client " << r._client->get_id();
  return stream;
}
double Request::get_service_time() {
    return _service_time;
}
double Request::get_early() {
    return _early;
}
double Request::get_late() {
    return _late;
}
double Request::get_requested_time() {
    return _requested_time;
}
Client* Request::get_client() {
    return _client;
}
int Request::get_skill() {
    return _skill;
}
int Request::get_day() {
    return _day;
}

std::pair< double, double > Request::get_point()
{
  return _client->get_point();
}


bool Request::nurse_in(Nurse* nurse)
{
  return _client->nurse_in(nurse);
}
int Request::get_client_id() {
    return _client->get_id();
}
