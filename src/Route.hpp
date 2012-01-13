/*!
* \file Route.hpp
* \brief Route class header file.
* \author Thomas Macdonald
* \date Thu Mar  4 14:29:01 CET 2010
*/
#ifndef ROUTE_HPP
#define ROUTE_HPP

#include <vector>
#include <map>
#include <float.h>
#include <assert.h>

#include "Nurse.hpp"
#include "Vertex.hpp"
#include "Client.hpp"
#include "DataStructures/DistanceMatrix.hpp"

using namespace std;
/*!
*	\class Route
*	\brief Implements a route, which is a vector of vertices associated to a nurse.
*
*	Each vertex services a request, and a route is also associated to a day, and carries a cost (in accordance with the cost function).
*/
class Route
{
  private:
    Nurse* _nurse; ///< Pointer to the nurse this route belongs to
    vector<Vertex> _vertices; ///< vector of vertices replying to requests
    int _day; ///< Day this route takes place on
    DistanceMatrix* _distance_matrix; ///< Pointer to distance matrix for convenience
    double _cost; ///< cost of the route
    double _length;
    double _consistency;
    int _id;
    int _order;
  public:
    static int _next_id;
    Route(); ///<default constructor
    Route(Nurse* nurse, DistanceMatrix* d) ; ///< constructor
    Route(const Route& r); ///< copy constructor
    ~Route(); ///< destructor (sets _nurse and _distance_matrix to 0)
    int get_id();
    size_t size(); ///< size of the internal vertice array
    Request* get_request(int index); ///< returns a pointer to the request used by the vertex at index
    void insert(RequestPtr r, int position); ///< inserts a new request in the given position
    void erase(int index); ///< removes a vertex from the position passed
    bool insertionPossible(Request* r, int position); ///< checks insertion feasibility
    bool checkSkills(Request* r); ///< checks whether the nurse has the right skillset to service the request
    bool checkDay(Request* r); ///< checks whether the request is on the same day as the route.
    int get_day() {return _day;} ///< returns the day the route takes place on
    void set_day(int day) { _day= day;} ///< sets the day the route takes place on
    Nurse* get_nurse() {return _nurse;} ///< returns a pointer to the nurse the route belongs to
    bool canRequestGoAfter(Request* r, int i); ///< returns true if a request fits just after a vertex
    double getInsertionCost(Request* request, unsigned int position); ///< returns the cost of inserting a request at the given position.
    double get_cost(); ///< returns the length of the route 
    double get_consistency(); ///< returns the overall consistency of the route
    double get_sum_of_distances(int index); ///< returns the sum of the the distances to get to a vertex from its predecessor and to get from it to its successor
    void update_values();///< recalculates cost and consistency of the route
    int get_id_of(int vertex);
    int get_request_id_of(int vertex);
    int get_vertex_pos_by_request_id(int id); 
    std::vector<std::pair<double,double> > get_points_in_order();
    std::vector<int> get_client_ids();
    friend ostream& operator<< (ostream& stream, const Route route);

};
ostream& operator<< (ostream& stream, const Route route
);
#endif // ROUTE_HPP
