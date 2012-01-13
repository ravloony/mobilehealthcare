/*!
* \file Useful.hpp
* \brief Useful functions static class. Should really be a namespace. Header file.
* \author Thomas Macdonald
* \date Thu Mar  4 14:29:01 CET 2010
*/
/*!
*	\author Thomas Macdonald
*	\author Olivier Mullier
*/

#ifndef USEFUL_HPP
#define USEFUL_HPP
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <math.h>
using namespace std;
class Useful
{
	public:
		static void init();
		static double randbetween(double, double);
		static int randbetween(int, int);
		static bool decision(double);
		static int percent_of(int,int);
		static bool is_in(int, vector<int>);
		static string add_number_to_string(string, int);
		static double max(double, double);
		static string stringify(double x);
		static double distance(vector<double>, vector<double>);
};

#endif // USEFUL_HPP
