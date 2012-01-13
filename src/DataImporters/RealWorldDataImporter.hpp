/*!
* \file RealWorldDataImporter.hpp
* \brief imports real world data
* \author Thomas Macdonald
* \date Thu Mar  4 14:29:15 CET 2010
*/


#ifndef REALWORLDDATAIMPORTER_HPP
#define REALWORLDDATAIMPORTER_HPP

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#include "../DataImporter.hpp"
#include "../Error.hpp"

using namespace std;

class RealWorldDataImporter : public DataImporter
{
  private:
    string _fname;
    string _req_file;
    string _nurse_file;
    string _dm_file;
    Request* makerequest(string time, string termineinsatz, double length, string daystr, string timewindow, string skillstr, Client* client);
    bool doesStringContain(string str, string substr);
  public:
    RealWorldDataImporter() ;
    RealWorldDataImporter(string fileName) ;
    virtual ~RealWorldDataImporter();
    virtual void plot();
    void run();
    virtual int get_num_days() ;
    virtual void print();
};

#endif // REALWORLDDATAIMPORTER_HPP
