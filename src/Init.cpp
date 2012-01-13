/*!
* \file Init.cpp
* \brief Mother class for all construction methods. Implementation file.
* \author Thomas Macdonald
* \date Thu Mar  4 14:29:00 CET 2010
*/
/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) <year>  <name of author>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#include "Init.hpp"


Init::Init()
{

}

Init::~Init()
{

}

std::vector< Request*, std::allocator< Request* > >& Init::get_uninserted_requests()
{
  return _uninserted_requests;
}

bool Init::has_uninserted_requests()
{
  return (_uninserted_requests.size()>0);
}

void Init::clear_uninserted_requests()
{
  _uninserted_requests.clear();
}
