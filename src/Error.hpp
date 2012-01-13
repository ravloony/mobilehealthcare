/*!
* \file Error.hpp
* \brief Error handling header file.
* \author Thomas Macdonald
* \date Thu Mar  4 14:29:00 CET 2010
*/

#ifndef ERROR_H
#define ERROR_H

#include <string>

using namespace std;

class Error : public std::exception
{
  public:
    Error ( int num=0, const std::string& desc="", int level=0 ) throw()
    :_number ( num ),_desc ( desc ),_level ( level )
    {}

    virtual const char* what() const  throw()
    {
      string result = "\033[01;31mError : " + _desc + "\033[0m";
      return result.c_str();
    }

    virtual ~Error() throw()
    {}

    int level() const { return _level;}
    
    int number() const { return _number;}
    
    string desc() const { return _desc; }
    
  private:
    int _number;               // Numéro de l'erreur.
    std::string _desc;       // Description de l'erreur.
    int _level;               // Niveau de l'erreur.
};

#endif // ERROR_H
