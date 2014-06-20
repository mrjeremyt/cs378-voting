// --------------------------------
// projects/Voting/TestVoting.c++
// Copyright (C) 2014
// Jeremy Thompson
// Daniel Durbin
// --------------------------------

/*
Google Test Libraries:
    % ls -al /usr/include/gtest/
    ...
    gtest.h
    ...

    % locate libgtest.a
    /usr/lib/libgtest.a

    % locate libpthread.a
    /usr/lib/x86_64-linux-gnu/libpthread.a
    /usr/lib32/libpthread.a

    % locate libgtest_main.a
    /usr/lib/libgtest_main.a

To compile the test:
    % g++-4.7 -fprofile-arcs -ftest-coverage -pedantic -std=c++11 -Wall Voting.c++ TestVoting.c++ -o TestVoting -lgtest -lgtest_main -lpthread

To run the test:
    % valgrind TestVoting

To obtain coverage of the test:
    % gcov-4.7 -b Voting.c++ TestVoting.c++
*/

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==
#include <utility>  // make_pair, pair

#include "gtest/gtest.h"

#include "Voting.h"

// -------------------
// read_num_elections
// -------------------
TEST(Voting, read_num_elections_1)
{
	const int c = read_num_candidates(1);
	ASSERT_EQ(1,c);
}
TEST(Voting, read_num_elections_2)
{
    std::istringstream r("20\n");   
	const int c = read_num_candidates(r);
	ASSERT_EQ(20,c);	
}
TEST(Voting, read_num_elections_3)
{
	const int c = read_num_candidates(9001);
	ASSERT_EQ(9001,c);	
}

// -------------------
// read_num_candidates
// -------------------
/*TEST(Voting, read_num_candidates_1)
{
    std::istringstream r("Bill Gates\nWolverine\nDoctor Who\n");
	const int c = read_candidates(r,3);
	ASSERT_EQ(20,c);		
}

TEST(Voting, read_candidates)
{
	std::istringstream r("Bill Gates\nWolverine\nDoctor Who\n");
	//Need to return a data structure and evaluate.
}*/