#include "ClientDelete.hpp"

ClientDelete::ClientDelete()
{
}

ClientDelete::ClientDelete(int percentage): Delete(percentage)
{
}


std::vector< Request*, std::allocator< Request* > > ClientDelete::execute(Solution& sol)
{
//   cout << "Deleting by client...";
  std::vector<Request*> deleted;
//   cout << "there are " << sol.get_number_of_requests() << " requests...";
  int initialNoOfRequests=sol.get_number_of_requests();
//   cout << "removing " << _percentage << "% -> " << (int)(((double)_percentage*initialNoOfRequests)/100.0) << " requests...";
  while (deleted.size()<(int)(((double)_percentage*initialNoOfRequests)/100.0))
  {
    int id = sol.get_least_consistent_client();
//     cout << "client id is " << id << "...";
    std::vector<std::pair<int, int> > setForRemoval = sol.get_request_ids_by_client_id(id);
    for (unsigned int i=0; i<setForRemoval.size(); i++)
    {
      deleted.push_back(sol.get_request_by_id(setForRemoval[i].first,setForRemoval[i].second));
      sol.erase_request_by_id(setForRemoval[i].first,setForRemoval[i].second);
    }
    sol.update_values();
  }
//   cout << deleted.size() << " values removed" << endl;
  return deleted;
}

