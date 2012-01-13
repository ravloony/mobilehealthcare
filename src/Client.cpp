/*!
* \file Client.cpp
* \brief Client class implementation file.
* \author Thomas Macdonald
* \date Thu Mar  4 14:29:00 CET 2010
*/
#include "Client.hpp"
using namespace std;

Client::Client()
{

}

Client::Client(string adress, int zip, string city, int id) : _adress(adress), _zip(zip), _city(city), _id(id) {}

Client::Client(string adress, int zip, string city, int id, double x, double y): _adress(adress), _zip(zip), _city(city), _id(id), _x(x), _y(y)
{
}


void Client::add_request(Request* r)
{
  _requests.push_back(r);
}

Client::~Client()
{

}

std::pair< double, double > Client::get_point()
{
  std::pair<double, double> point(_x,_y);
  return point;
}

ostream& operator<<(ostream& stream, const Client cli)
{
  stream << "ID: "<< cli._id << " Adress: " << cli._adress << " " << cli._zip << " " << cli._city << " | Number of requests: " << cli._requests.size() << endl;
  return stream;
}


void Client::add_nurse(Nurse* n)
{
  if (!nurse_in(n))
    _nurses.push_back(n);
}

int Client::get_no_of_nurses()
{
  return (int)_nurses.size();
}

bool Client::nurse_in(Nurse* nurse)
{
  for (unsigned int i = 0; i < _nurses.size(); i++)
  {
    if (_nurses[i]->get_id()==nurse->get_id())
      return true;
  }
  return false;
}



