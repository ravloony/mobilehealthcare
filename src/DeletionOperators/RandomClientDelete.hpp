#ifndef RANDOMCLIENTDELETE_HPP
#define RANDOMCLIENTDELETE_HPP

#include "Delete.hpp"


class RandomClientDelete : public Delete
{
  private:
    
  public:
    RandomClientDelete();
    RandomClientDelete(int percentage);
    virtual std::vector< Request*, std::allocator< Request* > > execute(Solution& sol);
    ~RandomClientDelete();
};

#endif // RANDOMCLIENTDELETE_HPP
