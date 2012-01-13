#include "Statistics.hpp"

Statistics::Statistics()
{

}

Statistics::Statistics(int nOfRequests, int nOfClients, int nOfNurses): _no_of_requests(nOfRequests), _no_of_clients(nOfClients), _no_of_nurses(nOfNurses)
{
}

// Statistics::Statistics(const Statistics& stat)
// {
// 
// }

void Statistics::add_after_init(Solution& sol)
{
  _after_init=sol;
}

void Statistics::add_final(Solution& sol)
{
  _after_meta=sol;
}

void Statistics::print_latex()
{
  double initLength = _after_init.get_total_length();
  double initConsist = _after_init.get_total_consistency();
  double metaLength = _after_meta.get_total_length();
  double metaConsist = _after_meta.get_total_consistency();
  int insertedRequestsInit = _after_init.get_number_of_requests();
  int insertedRequestsMeta = _after_meta.get_number_of_requests();
  cout << " & " << _no_of_clients << " & " << _no_of_requests << " & " << _no_of_nurses << " & " << initLength << " & " << initConsist << " & " << metaLength << " & " << metaConsist << " & " << ((initLength-metaLength)/initLength)*100 << " & " << ((initConsist-metaConsist)/initConsist)*100 << endl;
}

ostream& operator<<(ostream& stream, const Statistics& stat)
{
  double initLength = stat._after_init.get_total_length();
  double initConsist = stat._after_init.get_total_consistency();
  double metaLength = stat._after_meta.get_total_length();
  double metaConsist = stat._after_meta.get_total_consistency();
  int insertedRequestsInit = stat._after_init.get_number_of_requests();
  int insertedRequestsMeta = stat._after_meta.get_number_of_requests();
  stream << "After init : Length : " << initLength << ", Consistency : " << initConsist << ", " << insertedRequestsInit << "/" << stat._no_of_requests << " inserted\n"
  "After VLNS : Length : " << metaLength << ", Consistency : " << metaConsist << ", " << insertedRequestsMeta << "/" << stat._no_of_requests << " inserted\n"
  "Improvement : Length : " << ((initLength-metaLength)/initLength)*100 << ", Consistency : " << ((initConsist-metaConsist)/initConsist)*100 << endl;
  return stream;
}

Statistics::~Statistics()
{

}

