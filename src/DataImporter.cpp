/*!
* \file DataImporter.cpp
  * \brief Implements a Distance Matrix structure to abstract access to distances. Implementation file.
* \author Thomas Macdonald
* \date Thu Mar  4 14:29:00 CET 2010
*/
#include "DataImporter.hpp"


DataImporter::~DataImporter()
{
  
}

std::ostream& operator<<(ostream& stream, DataImporter& d)
{
  stream << "Clients:" << endl;
  for (unsigned int i=0; i<d.get_clients().size();i++)
  {
    stream << *(d.get_clients()[i]);
    for (unsigned int j=0; j<d.get_clients()[i]->get_requests().size(); j++)
    {
      stream << "\t" << *(d.get_clients()[i]->get_requests()[j]) << endl;
    }
  }
  stream << "Nurses:" << endl;
  for (unsigned int i=0; i<d.get_nurses().size();i++)
  {
    stream << *(d.get_nurses()[i]) << endl;
  }
  return stream;
}
