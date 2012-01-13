/*!
* \file Request.hpp
* \brief Request class header file.
* \author Thomas Macdonald
* \date Thu Mar  4 14:29:01 CET 2010
*/
#ifndef REQUEST_HPP
#define REQUEST_HPP
#include <iosfwd>
#include <iostream>
#include <fstream>

#include "Client.hpp"
#include "Nurse.hpp"

using namespace std;

class Client;

class Request
{
  private:
    double _early;
    double _late;
    double _service_time;
    double _requested_time;
    int _skill;
    int _day;
    int _local_id;
    static int _next_id;
    Client* _client;
  public:
    Request();
    Request(double early, double late, double s_time, double r_time, int skill, int day);
    ~Request();
    int get_local_id();
    int get_skill() ;
    int get_day();
    int get_client_id() ;
    double get_service_time() ;
    double get_early() ;
    double get_late() ;
    double get_requested_time() ;
    Client* get_client() ;
    void add_client(Client* cli);
    bool sameTimeWindow(Request* r);
    bool sameTimeWindow(Request r);
    int timeWindowPos(Request* r); ///< relative position of time windows
    bool nurse_in(Nurse* nurse);
    friend ostream& operator<< (ostream& stream, const Request& r);
    std::pair<double,double> get_point();
};
ostream& operator<< (ostream& stream, const Request& r);
typedef Request *RequestPtr;
#endif // REQUEST_HPP
