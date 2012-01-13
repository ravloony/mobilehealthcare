/*!
* \file Nurse.cpp
* \brief Nurse class implementation file.
* \author Thomas Macdonald
* \date Thu Mar  4 14:29:00 CET 2010
*/
#include "Nurse.hpp"
using namespace std;

Nurse::Nurse()
{

}

Nurse::Nurse(int id, string adress, int zip, string city, double sdur, int skill, double mdur) : _id(id),_adress(adress), _zip(zip), _city(city), _shift_duration(sdur), _skill_level(skill), _max_duration(mdur) 
{
  _x=0;
  _y=0;
}

Nurse::Nurse(int id, string adress, int zip, string city, double sdur, int skill, double mdur, double x, double y): _id(id),_adress(adress), _zip(zip), _city(city), _shift_duration(sdur), _skill_level(skill), _max_duration(mdur), _x(x), _y(y)
{
}

std::pair< double, double > Nurse::get_point()
{
  std::pair<double, double> point(_x,_y);
  return point;
}


Nurse::~Nurse()
{

}

Nurse::Nurse(const Nurse& n)
{
  _adress=n._adress;
  _city=n._city;
  _id=n._id;
  _zip=n._zip;
  _max_duration=n._max_duration;
  _shift_duration=n._shift_duration;
  _skill_level=n._skill_level;
}


ostream& operator<<(ostream& stream, const Nurse n)
{
  stream << "id : " << n._id << ", skill : "  << n._skill_level << ", shift duration : " << n._shift_duration << endl;
  return stream;
}

