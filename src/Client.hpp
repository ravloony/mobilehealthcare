/*!
* \file Client.hpp
* \brief Client class header file.
* \author Thomas Macdonald
* \date Thu Mar  4 14:29:00 CET 2010
*/
#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>
#include <vector>
#include <iostream>

#include "Request.hpp"
#include "Nurse.hpp"

using namespace std;

class Request;

typedef Request* RequestPtr;
class Client
{
  private:
    string _adress;
    int _zip;
    string _city;
    int _id;
    double _x;
    double _y;
    vector<RequestPtr> _requests;
    vector<Nurse*> _nurses;
  public:
    Client();
    Client(string adress, int zip, string city, int id);
    Client(string adress, int zip, string city, int id, double x, double y);
    ~Client();
    void add_request(Request* r);
    int get_id() {return _id;}
    std::pair<double, double> get_point();
    vector<Request*>& get_requests() {return _requests;}
    friend ostream& operator<< (ostream& stream, const Client cli);
    void add_nurse(Nurse* arg1);
    int get_no_of_nurses();
    bool nurse_in(Nurse* nurse);
};
typedef Client *ClientPtr;
ostream& operator<< (ostream& stream, const Client cli);
#endif // CLIENT_HPP
