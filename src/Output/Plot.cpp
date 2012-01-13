/*!
* \file Plot.cpp
* \author Thomas Macdonald
* \author Olivier Mullier
*/

#include "Plot.hpp"

using namespace std;

Plot::Plot()
{
}

/**
* Constructor.
*/
Plot::Plot ( vector< std::pair< double, double > > points, string fname, string resname, pair< string, string > labels)
{
	_points = points;
	_name = "plots/" + fname;
	_resname = resname;
	_labels = labels;
}

/**
* Add extra points.
* Sometimes one needs to add a single point to the plot. This allows one to do so. All single points added will have their own color
*/
void Plot::add_extra(std::pair< double, double > point)
{
  _extra_points.push_back(point);
  
}

/**
*	Remake all the points.
*/
void Plot::rebase()
{
  vector<vector<pair<double, double> > > points_copy = _lists_of_points;
  _lists_of_points.clear();
  _datafiles.clear();
  for (unsigned int i=0; i<points_copy.size();i++) {
    add_points(points_copy[i]);
  }
}


void Plot::remove_points(int i)
{
    _lists_of_points.erase(_lists_of_points.begin()+i);
    _datafiles.erase(_datafiles.begin()+i);
    rebase();
}



void Plot::add_points(vector< std::pair< double, double > > points)
{
  ostringstream o;
  o << _datafiles.size();
  string filename = "plots/.data."+o.str()+".dat";
  _datafiles.push_back(filename);
  sendtofile(points,filename);
}

void Plot::plot()
{
  string cmd = "set terminal x11\nset grid x y \n";
  cmd += "plot ";
  if (_resname!="") {
    cmd += "\""+_resname + "\" using 1:2 title \'Exact results\' with points, ";
  }
  for (unsigned int i=0; i<_datafiles.size(); i++) {
    ostringstream o;
    o << i;
    cmd += "\""+ _datafiles[i] +"\" using 1:2 title \'Route " + o.str() + "\' with linespoints";
    if (i<_datafiles.size()-1) {
      cmd += ", ";
    }
  }
  cmd += "\npause -1\n";
  plotcmd(cmd);
}


void Plot::sendtofile(vector< std::pair< double, double > > points, string filename)
{
  ofstream file(filename.c_str(), ios::out | ios::trunc);
  if (file) {
    for(unsigned int i = 0; i < points.size(); i++)
    {
      file << points[i].first << " " << points[i].second << "\n";
    }
    file.close();
  }
}



void Plot::plot_to_file()
{
    string cmd = "set terminal postscript eps enhanced color\n";
    cmd += "set output \"" + _name + ".eps\"\n";
    cmd += "set grid x y \n";
    cmd += "plot ";
    if (_resname!="") {
      cmd += "\""+_resname + "\" using 1:2 title \'exact results\' with points, ";
    }
    for (unsigned int i=0; i<_datafiles.size(); i++) {
      ostringstream o;
      o << i;
      cmd += "\""+ _datafiles[i] +"\" using 1:2 title \'Route " + o.str() + "\' with linespoints";
      if (i<_datafiles.size()-1) {
	cmd += ", ";
      }
    }
    cmd += "\n";
    plotcmd(cmd);
}


void Plot::plotcmd(string cmd)
{
    ofstream script("plots/.script.gnuplot", ios::out | ios::trunc);
    if (script) 
    {
      script << cmd;
    }
    script.close();
    string cmdline = "/usr/bin/gnuplot plots/.script.gnuplot";
    system(cmdline.c_str());
}


void Plot::set_name(string fname, string extension)
{
  _name="plots/"+fname;
  _extension = extension;
}


void Plot::set_res_name(string rname)
{
  _resname = rname;
}



int Plot::exec()
{
	//make the data file for gnuplot
	ofstream file("plots/.out.gnuplot", ios::out | ios::trunc);
	if(file)
	{
	  for(unsigned int i = 0; i < _points.size(); i++)
		{
			file << _points[i].first << " " << _points[i].second << "\n";
		}
		//make the script for gnuplot
		ofstream script("plots/.script.gnuplot", ios::out | ios::trunc);
		if (script) 
		{
			script << "set terminal postscript eps enhanced color" << endl;
			script << "set output \"" << _name << ".eps\""<<endl;
			//          script<<"set xrange [0:"<<xrange<<"]"<<endl;
			//          script<<"set yrange [0:"<<yrange<<"]"<<endl;
			script << "set grid x y" << endl;
			//script << "set multiplot" << endl;
			script << "set xlabel \"" << _labels.first << "\"" << endl;
			script << "set ylabel \"" << _labels.second << "\"" << endl;
			script << "set title \"approximation of Pareto front with multi-objective metaheuristic\"" << endl;
			if (_resname!="") {
				script << "plot \""+ _resname +"\" using 1:2 notitle with point 2, \"plots/.out.gnuplot\" using 1:2 notitle with point 1";
			} else {
				script << "plot \"plots/.out.gnuplot\" using 1:2 notitle with point 1";
			}
			if (_extra_points.size()>0) {
			  script << ", \"-\" using 1:2 notitle with point 3" << endl;
			  for (unsigned int i = 0; i<_extra_points.size(); i++) {
			    cout << "adding extra point " << i << endl;
			      script << _extra_points[i].first << " " << _extra_points[i].second << endl;
			  }
			} else {
			  script << endl;
			}
// 			script << "unset multiplot" << endl;
			script << "reset" << endl;
			file.close();
			script.close();
			
			//draw the png
			string cmd = "gnuplot plots/.script.gnuplot &";
			system(cmd.c_str());
		}
	}
	return 0;
}