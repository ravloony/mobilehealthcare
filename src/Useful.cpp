/*!
* \file Useful.cpp
* \brief Useful functions static class. Should really be a namespace. Implementation file.
* \author Thomas Macdonald
* \date Thu Mar  4 14:29:01 CET 2010
*/
/*!
*	\author Thomas Macdonald
*	\author Olivier Mullier
*/

#include <cstdlib>
#include <time.h>
#include "Useful.hpp"



void Useful::init()
{
	static int n=0;
	if (n==0)
		srand((unsigned) time(NULL));
	n++;
}

double Useful::randbetween ( double low, double high)
{
	double range=(high-low);
	double num = static_cast<double>( rand() ) * range / static_cast<double>( RAND_MAX ) + low ;
	return num;
}


int Useful::randbetween ( int low, int high)
{
	return (low + (int)(((double)rand()/(double)RAND_MAX)*((double)(high-low+1))));
}


bool Useful::decision ( double proba)
{
	return (randbetween(0.0,100.0) < proba*100.0);
}



int Useful::percent_of ( int p, int x)
{
	return (int)floor((double)(x/100)*p);
}


bool Useful::is_in ( int elem, std::vector< int > v)
{
	if (v.size()==0)
		return false;
	for (unsigned int i=0;i<v.size();i++) {
		if (v[i] == elem)
			return true;
	}
	return false;
}


string Useful::add_number_to_string(string str, int i)
{
	ostringstream s;
	s << i;
	return str + s.str();
}

/**
 * \return the max of two doubles, the first one if they're equal.
 */
double Useful::max(double x, double y)
{
  if(x<y) return y;
  else return x;
}


double Useful::distance(std::vector< double > x, std::vector< double > y)
{
  return sqrt(pow(x[0]-y[0],2)+pow(x[1]-y[1],2));
}


string Useful::stringify(double x)
{
  std::ostringstream o;
  o << x;
  return o.str();
} 