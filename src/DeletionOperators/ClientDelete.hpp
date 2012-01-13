#ifndef CLIENTDELETE_HPP
#define CLIENTDELETE_HPP

#include "Delete.hpp"

/*!
*	\class ClientDelete
*	\brief Deletes requests fromn solution that belong to the client with the highest consistency cost
*/
class ClientDelete : public Delete
{

public:
    ClientDelete();
    ClientDelete(int percentage);
    virtual std::vector< Request*, std::allocator< Request* > > execute(Solution& sol);
};

#endif // CLIENTDELETE_HPP
