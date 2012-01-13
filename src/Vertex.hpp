/*!
* \file Vertex.hpp
* \brief Vertex class header file.
* \author Thomas Macdonald
* \date Thu Mar  4 14:29:01 CET 2010
*/
#ifndef VERTEX_HPP
#define VERTEX_HPP
#include "Request.hpp"
#include "Client.hpp"
using namespace std;

typedef Request *RequestPtr;
class Vertex
{
  private:
    double _wait;
    double _begin;
    int _order;
    RequestPtr _request;
  public:
    Vertex();
    Vertex(double wait, double begin, int order, RequestPtr request);
    ~Vertex();
    double get_end();
    double get_begin() {return _begin;}
    double get_wait();
    void set_begin(double begin);
    void set_wait(double wait);
    int get_client_id() const ;
    int get_request_id() const;
    std::pair<double,double> get_point();
    double get_length(); 
    double get_tw_start();
    double get_tw_end();
    Request* get_request() {return _request;}
    friend bool operator< (Vertex& v, Vertex& w);
    friend bool operator<= (Vertex& v, Vertex& w);
    friend bool operator> (Vertex& v, Vertex& w);
    friend bool operator>= (Vertex& v, Vertex& w);
    friend ostream& operator<< (ostream& stream, const Vertex vertex);
};
bool operator< (Vertex& v, Vertex& w);
bool operator<= (Vertex& v, Vertex& w);
bool operator> (Vertex& v, Vertex& w);
bool operator>= (Vertex& v, Vertex& w);

ostream& operator<< (ostream& stream, const Vertex vertex);
#endif // VERTEX_HPP
