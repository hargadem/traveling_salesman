/***********************************************
 *	Class definitions for travelling salesman
 *	Maire Hargaden
 *	CS 420 
 *	Winter 2019
 * *******************************************/


#ifndef TSP_HPP
#define TSP_HPP
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class TSP
{
	private:
		vector<int> tour;
		vector<vector<int> > edges;
		vector<pair<int, int> > coords;
		vector<int> names;
		vector<vector<int> > edgeLengths;
		bool isTour();
		void move(int);
		void reverseTour(int, int);
		int dist(int, int);

	public:
		int size;
		TSP(vector<pair<int,int> > &coords, vector<int> &names);
		int getTourDist();
		void improveTour();
		void printTour();
		void printTourNames();
		void writeTour(string);

};

#endif
