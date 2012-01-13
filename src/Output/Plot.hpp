/*!
*  \file Plot.hpp
*  \author Thomas Macdonald
*  \author Olivier Mullier
*/

#ifndef PLOT_HPP
#define PLOT_HPP
#include <string>
#include <utility>
#include <iostream>
#include <fstream>
#include <iosfwd>
#include <vector>
#include <sstream>

#include <stdio.h>
#include <stdlib.h>


class Plot
{
public:
    Plot();
    /**  \brief Constructor
    *	 \param points vector of pairs of points
    *	 \param fname filename to write to
    *	 \param resname filename of exact results file
    *	 \param labels x and y labels
    */
    Plot ( std::vector< std::pair< double, double > >, std::string, std::string, std::pair< std::string, std::string > );
    int exec();
    void add_extra(std::pair<double,double>);
    void add_points(std::vector<std::pair<double,double> >);
    void remove_points(int i);
    void set_name(std::string name, std::string extension="png");
    void set_res_name(std::string rname);
    void plot_to_file();
    void plot();
    void rebase();
private:
    std::string _name;
    std::string _resname;
    std::string _extension;
    std::vector<std::pair<double,double> >  _points;
    std::pair<std::string,std::string> _labels;
    std::vector<std::pair<double,double> > _extra_points;
    std::string _cmd;
    std::vector<std::vector<std::pair<double,double> > >  _lists_of_points;
    std::string _folder;
    void sendtofile(std::vector< std::pair< double, double > >, std::string);
    std::vector<std::string> _datafiles;
    void makedatafiles();
    void plotcmd(std::string);
};

#endif // PLOT_HPP
