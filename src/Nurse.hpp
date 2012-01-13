/*!
* \file Nurse.hpp
* \brief Nurse class header file.
* \author Thomas Macdonald
* \date Thu Mar  4 14:29:00 CET 2010
*/
#ifndef NURSE_HPP
#define NURSE_HPP

#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class Nurse
{
  private:
    int _id;
    string _adress;
    int _zip;
    string _city;
    double _shift_duration;
    int _skill_level;
    double _max_duration;
    double _x;
    double _y;
  public:
    Nurse();
    Nurse(int id, string adress, int zip, string city, double sdur, int skill, double mdur);
    Nurse(int id, string adress, int zip, string city, double sdur, int skill, double mdur, double x, double y);
    Nurse(const Nurse& n);
    ~Nurse();
    int get_id() {return _id;}
    int get_skill() {return _skill_level;}
    std::pair<double, double> get_point();
    friend ostream& operator<<(ostream&, const Nurse n);
};
ostream& operator<<(ostream&, const Nurse n);

#endif // NURSE_HPP
