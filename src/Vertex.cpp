/*!
* \file Vertex.cpp
* \brief Vertex class implementation file.
* \author Thomas Macdonald
* \date Thu Mar  4 14:29:01 CET 2010
*/
#include "Vertex.hpp"
using namespace std;


Vertex::Vertex()
{

}

Vertex::Vertex(double wait, double begin, int order, RequestPtr request) :_wait(wait), _begin(begin), _order(order), _request(request)
{
  //int test = _request->get_day();
}


Vertex::~Vertex()
{

}

double Vertex::get_end()
{
  double length = get_length();
  return _begin+length;
}

double Vertex::get_length()
{
  return _request->get_service_time();
}

void Vertex::set_begin(double begin)
{
  _begin=begin;
}

void Vertex::set_wait(double wait)
{
  _wait=wait;
}


double Vertex::get_tw_start()
{
  return _request->get_early();
}

double Vertex::get_tw_end()
{
  return _request->get_late();
}

bool operator<(Vertex& v, Vertex& w)
{
  return v.get_tw_start()<w.get_tw_start() && v.get_tw_end()<w.get_tw_end();
}

bool operator<=(Vertex& v, Vertex& w)
{
  return v.get_tw_start()<w.get_tw_start() && v.get_tw_end()<=w.get_tw_end();
}

bool operator>(Vertex& v, Vertex& w)
{
  return v.get_tw_start()>w.get_tw_start() && v.get_tw_end()>w.get_tw_end();
}

bool operator>=(Vertex& v, Vertex& w)
{
  return v.get_tw_start()>=w.get_tw_start() && v.get_tw_end()>w.get_tw_end();
}
int Vertex::get_client_id() const {
    return _request->get_client_id();
}

int Vertex::get_request_id() const
{
  return _request->get_local_id();
}

std::pair< double, double > Vertex::get_point()
{
  return _request->get_point();
}


std::ostream& operator<<(ostream& stream, const Vertex vertex)
{
  stream << "insertion no : " << vertex._order << " |"<< vertex._wait << " -> \033[01;31m" << vertex._begin << " || service time : " << vertex._request->get_service_time() << "\033[0m| >> servicing request for client " << vertex.get_client_id() << "<< " << endl;
  stream << "time window : " << vertex._request->get_early() << " to " << vertex._request->get_late() << endl;
  return stream;
}
