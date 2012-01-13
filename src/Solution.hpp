/*!
* \file Solution.hpp
* \brief Solution class header file.
* \author Thomas Macdonald
* \date Thu May 4 14:29:01 CET 2010
*/
#ifndef SOLUTION_HPP
#define SOLUTION_HPP
#include <vector>
#include "Route.hpp"
#include "Output/Plot.hpp"

/*!
*	\class Solution
*	\brief A solution is a set of routes which partially or completely solve the problem.
*
*	Each solution has as a value the sum of all the lengths of the routes it contains, plus its consistency. This is how solutions are compared to one another.
*/
class Solution
{
  friend ostream& operator<< (ostream& stream, const Solution sol);
  private:
    std::vector<Route> _routes; ///< the routes contained in the solution
    double _total_length; ///< total traveled distance (or time)
    double _total_consistency; ///< total consistency, ie +N for each time an extra nurse is added to a clients schedule N=1000
    int _number_of_requests; ///< number of requests treated in the solution.
    std::map<int,std::vector<int> > _consistency_map; ///< Map of nurses per client. Allows us to calculate consistency in a self contained way.
  public:
    Solution(); ///<default constructor
    Solution(std::vector<Route>& routes); ///< secondary constructor from a vector of routes.
    ~Solution(); ///default destructor
    void add_route(Route& route); ///< adds a route to the solution
    std::vector<Route>& get_routes(); ///< returns a reference to the internal vector of routes (deprecated and uselessly pointless)
    void remove_routes(); ///< removes all the routes (also deprecated and useless)
    double get_total_cost(); ///< returns the total cost of the solution
    double get_total_length() const; ///< returns the total distance covered by all the routes
    double get_total_consistency() const; ///< returns the total consistency of the solution
    double get_consistency_average(); ///< returns the average consistency of the solution
    void insert(Request* r, int route, int position); ///< insert a request r in route 
    bool insertionPossible(Request* r, int route, int position); ///< returns true if the request can be inserted in the route at the position, false otherwise
    double getInsertionCost(Request* r, int route, int position); ///< returns the cost of inserting the request in the route at the position
    bool check_skills(Request* r, int route);
    bool check_day(Request* r, int route);
    int size_of_route(int route);
    void erase(int route, int vertex);
    void erase_request_by_id(int route, int id);
    void update_values();
    int get_sum_of_distances(int route, int vertex);
    int get_number_of_requests() const;
    int get_least_consistent_client();
    std::vector<std::pair<int, int> > get_request_ids_by_client_id(int id);
    int get_random_client_id();
    size_t size();
    void plot(std::string name="image");
    void plot_by_day(string name, int day);
    void display();
    Request* get_request(int route, int vertex);
    Request* get_request_by_id(int route, int id);
    Route& get_route(int route); ///< retuns a reference to the route 
};

#endif // SOLUTION_HPP
