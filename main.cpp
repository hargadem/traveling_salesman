/********************************************************
 * Driver function for Travelling Salesman Problem
 * Maire Hargaden
 * CS 420
 * Winter 2019
 * *****************************************************/

#include <iostream>
#include "tsp.hpp"
#include <fstream>
#include <string>
using namespace std;

//accept problem instance from cmd line
//takes filename from cmd line
int main(int argc, char** argv)
{

	vector<int> indices;
	vector<pair<int,int> > coordinates;

	string filename;
	if (argc != 2)
	{	
		cout << "wrong number of arguments" << endl;
		return 1;
	}

	filename = argv[1];	//assign filename
	cout << "filename: " << filename << endl;

	//try to open file
	ifstream file(filename.c_str());
	if(!file.is_open())
	{
		cout << "file is NOT open" << endl;
		return 1;
	}		

	
	//count no of lines
	string line;
	int numLines;
	while(getline(file, line))
		numLines++;	
	cout << "there are " << numLines << " cities" << endl;

	//return to top of file
	file.clear();
	file.seekg(0, ios::beg);

	//push index to names vector
	//push coordinates to coords vector
	int index; 
	int xCoord;
	int yCoord;
	while (file >> index)
	{
		indices.push_back(index);
		file >> xCoord;
		file >> yCoord;
		coordinates.push_back(make_pair(xCoord,yCoord));
	}

	//initialize TSP problem
	TSP prob(coordinates, indices);

	//improves on initial pseudorandom tour
	prob.improveTour();

	//print end distance
	cout << "Tour length = " << prob.getTourDist() << endl;

	//write to output file
	string outName;
	outName = argv[1];
	outName += ".tour";
	prob.writeTour(outName);

	return 0;
}
