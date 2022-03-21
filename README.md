#traveling_salesman
INCLUDED FILES:
	makefile
	tsp.hpp
	tsp.cpp
	main.cpp

WINDOWS COMPILATION INSTRUCTIONS:
	Add input text file in /tests directory.
	Lists city number and x, y coordinates on each line.
	Type the following into the command line:

	% g++ -o main.exe main.cpp tsp.cpp tsp.hpp
	% main <tests/test-input-x.txt>	

	Write the input filename directly on console like above.
	Only one input file can be run at a time.
	To run a different file, execute again by typing

	% main <tests/test-input-y.txt>

LINUX COMPILATION INSTRUCTIONS:
	Add input text file in /tests directory.
	Type the following into the command line:

	% make
	% main <tests/test-input-x.txt>	

EXECUTION TIME
	The algorithm should automatically time out around 5 minutes. 
	The duration of the algorithm runtime will be printed to the console.
