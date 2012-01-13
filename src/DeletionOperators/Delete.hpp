#ifndef DELETE_HPP
#define DELETE_HPP
#include "../Solution.hpp"

class Delete
{
  protected:
    int _percentage;
  public:
    Delete();
    Delete(int percentage);
    virtual vector<Request*> execute(Solution& sol)=0;
    ~Delete();
};

#endif // DELETE_HPP
