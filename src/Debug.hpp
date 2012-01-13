/*!
* \file Debug.hpp
* \brief Debugging functions header file.
* \author Thomas Macdonald
* \date Thu Mar  4 14:29:00 CET 2010
*/
/*!
*	\author Thomas Macdonald
*	\author Olivier Mullier
*/

#ifndef DEBUG_HPP
#define DEBUG_HPP
#include <string>
#include <iostream>

using namespace std;

class Debug
{
	public:
		static void printfunc(const char* s,int enter)
		{
#ifdef DEBUG
			if (enter) {
				cout << "\033[22;34mentering " << s << "\033[0m" << endl;
			} else {
				cout << "\033[22;34mexiting " << s << "\033[0m" << endl;
			}
#endif
		}
		template<typename T>
		static void println(T t)
		{
#ifdef DEBUG
			cout << "\033[22;36m" << t << "\033[0m" << endl;
#endif	
		}
		template<typename T>
		static void print(T t)
		{
#ifdef DEBUG
			cout << "\033[22;36m" << t << "\033[0m";
#endif	
		}
};

#endif // DEBUG_HPP
