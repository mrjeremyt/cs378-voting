// --------------------------------
// projects/Voting/RunVoting.c++
// Copyright (C) 2014
// Jeremy Thompson
// Daniel Durbin
// --------------------------------

/*
To compile the program:
    % g++-4.7 -fprofile-arcs -ftest-coverage -pedantic -std=c++11 -Wall Voting.c++ RunVoting.c++ -o RunVoting

To run the program:
    % valgrind RunVoting < testVoting.txt

To obtain coverage of the run:
    % gcov-4.7 -b Voting.c++ RunVoting.c++

To configure Doxygen:
    % doxygen -g
    That creates the file "Doxyfile".
    Make the following edits:
    EXTRACT_ALL            = YES
    EXTRACT_PRIVATE        = YES
    EXTRACT_STATIC         = YES
    GENERATE_LATEX         = NO

To document the program:
    % doxygen Doxyfile
*/

// --------
// includes
// --------
#include <iostream> // cin, cout

#include "Voting.h"





int main()
{
	using namespace std;
	int num_elections;
	cin >> num_elections;
	while (num_elections > 0)
	{
		run_elections(cin,cout);
		num_elections--;
	}
	return 0;
}