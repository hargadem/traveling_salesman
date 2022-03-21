/***********************************************
 * Function definitions for travelling salesman
 * Maire Hargaden
 * CS 420
 * Winter 2019
 * *********************************************/

#include "tsp.hpp"	
#include <iostream>
#include <cmath>
#include <vector>
#include <bits/stdc++.h>
#include <set>
#include <ctime>
using namespace std;

//sorts a pair of ints
pair<int,int> sortPair(int x, int y)
{
	if (x < y)
		return make_pair(x, y);
	else
		return make_pair(y,x);
}

//intializer
TSP::TSP(vector<pair<int, int> > &coords, vector<int> &names)
{
	this->coords = coords;
	this->names = names;
	size = names.size();

	//initialize tour
	tour = vector<int>(size,0);
	
	//intial pseudorandom tour T
	for (int i=0; i < size; i++)
	{
		tour[i] = (i+1) % size;
	}

	//initialize edge length matrix
	edgeLengths = vector<vector<int> >(size, vector<int>(size,0));

	//computes edge lengths
	int curEdge;
	for(int i=0; i < size; i++)
	{
		for(int j=0; j < size; j++)
		{
			//compute dist
			curEdge = dist(i,j);
		//	cout << curEdge << "; ";
			edgeLengths[i][j] = curEdge;
			edgeLengths[j][i] = curEdge;
		}
	}
}

int TSP::getTourDist()
{
	int dist = 0;

	for (int i=0; i < size; i++)
	{
		dist += edgeLengths[i][tour[i]];
	}

	return dist;
}

//improve tour
void TSP::improveTour()
{
	clock_t start;
	double duration;
	double current;

	start = clock();

	int diff;
	int oldDist = 0;
	int newDist = 0;

	for(int k = 0; k < 10; k++)	
	{
		//checks timeout condition
		current = (clock() - start)/(double) CLOCKS_PER_SEC;
		if (current > 300)		//300 sec = 5 min
		{
			cout << "Timed out at " << current;
			cout << " after " << k << " iterations" << endl;
			goto end;
		}

		for (int i=0; i < size; i++)
		{
			//checks timeout condition
			current = (clock() - start)/(double) CLOCKS_PER_SEC;
			if (current > 300)
				break;
	
			move(i);
		}

		newDist = getTourDist();
		diff = oldDist - newDist;

		if (k != 0)
		{
			assert(diff >= 0);
			if (diff == 0)
			{
				cout << "converged after " << k << " iterations" << endl;
				break;
			}
		}
		oldDist = newDist;
	} 

end:

	duration = (clock() - start)/(double) CLOCKS_PER_SEC;
	cout << "duration = " << duration << endl;
}

//print tour
void TSP::printTour()
{
	int index = 0;

	do
	{
		cout << index << " ; " ;
		index = tour[index];
	} while (index != 0);
	cout << endl;
	cout << "Tour length = " << getTourDist() << endl;
}

//print tour names

bool TSP::isTour()
{
	int counter = 1;
	int start = tour[0];
	while (start != 0)
	{
		start = tour[start];
		counter++;
	}

	return (counter == size);
}

//swaps x_i, y_i according to heuristic
void TSP::move(int start)
{
	set<pair<int,int> > broken, joined;
	vector<int> bestTour = tour; 
	int gBest = 0; 		//G*
	int gSum = 0; 		//G_i = partial sum of g_i's
	int gLocal;			//g_i
	int prevNext = start;		//previous node
	int from = tour[prevNext];	//current node
	int next;					//next node
	int nextFrom;				//next next node
	int lastNext;			//last possible next node
	pair<int,int> edgeBreak;	
	int yBest;
	int breakLength;	//broken edge length
	int gBestLocal;		//local optimum
	int startDist = getTourDist();
	int finishDist;

	do
	{
		//suppose no next exists
		next = -1;
	
		edgeBreak = sortPair(from, prevNext);	//x_i

		breakLength = edgeLengths[edgeBreak.first][edgeBreak.second];

		//checks condition 4c:
		//x_i cannot be a link previously joined
		//i.e. some y_j, j < i
		if (joined.count(edgeBreak) > 0) break;
		
		//y_i = (from, next)
		for(int i = tour[from]; next == -1 && i != start; i = tour[i])
		{
			//calculate local gain
			gLocal = breakLength - edgeLengths[from][i];	
			
			//checking invalidity conditions for y_i
			if(!(
				//condition 4c pt 2
				//y_i cannot be previously broken
				broken.count(sortPair(from, i)) == 0 &&

				//condition 4d
				//gain criterion
				gSum + gLocal > 0 &&

				//condition 4e
				//x_{i+1} has never been joined before
				joined.count(sortPair(lastNext, i)) == 0 &&

				//not already joined to start
				tour[i] != 0 &&

				//not already joined to from
				i != tour[from]

				))	{
				//valid y_i
				lastNext = i;
				continue;
			}

			//y_i = (from, i)
			next = i;
			
			//move on to next

		}

		//check next y_i exists
		if (next != -1)
		{
			//add x_i to broken
			broken.insert(edgeBreak);

			//add y_i to joined
			joined.insert(sortPair(from, next));


			//condition 4(f)
			//check if joining t_2i, t_1 improves gain
			yBest = edgeLengths[from][start];

			//tour length if we exchange broken edge x_i
			//and optimum yBest (t_2i, t_0)
			gBestLocal = gSum + (breakLength - yBest);

			if (gBestLocal > gBest)
			{
				gBest = gBestLocal;
				bestTour = tour;

				bestTour[start] = from;

			}

			gSum += breakLength - edgeLengths[from][next];
			reverseTour(from, lastNext);

			//new t_2i+1
			nextFrom = lastNext;

			//make y_i
			tour[from] = next;

			prevNext = next;
			from = nextFrom;

		}

	} while (next != -1);
	
	

	//join up ends
	tour = bestTour;
	finishDist = getTourDist();
	
	assert(finishDist <= startDist);
	assert(isTour());
}


//reverses tour begin start and end points
void TSP::reverseTour(int start, int finish)
{
	int current = start;
	int next = tour[start];
	int ahead;

	do
	{
		ahead = tour[next];
		tour[next] = current;

		current = next;
		next = ahead;
	} while (current != finish);
}


//calculates Euclidean distance between two cities
int TSP::dist(int city1, int city2)
{
	int x1 = coords[city1].first;
	int y1 = coords[city1].second;

	int x2 = coords[city2].first;
	int y2 = coords[city2].second;

	float radicand = pow(abs(x1-x2),2) + pow(abs(y1-y2), 2);
	float dist = sqrt(radicand);
	int result = round(dist);
	return result;
}

//writes tour to .txt file
void TSP::writeTour(string filename)
{
	ofstream output; 
	output.open(filename.c_str());
	
	//write length of tour
	output << getTourDist() << endl;

	//write cities in order visited
	int city = 0;
	do
	{
		output << city << endl;
		city = tour[city];
		
	} while (city != 0);
}
