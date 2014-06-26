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

// #include <cassert>  // assert
#include <iostream> // endl, istream, ostream
// #include <utility>  // make_pair, pair
// //#include <algorithm>
#include <string>
#include <sstream>
// #include <iterator>

#include "gtest/gtest.h"

#include "Voting.h"

class Ballot
{
public:
    Ballot(vector<int>& v);
    vector<int> vec;
    //~Ballot();
    vector<int> getBallot();
    int current_counted_index;
};

using namespace std;

// -------------------
// read_num_candidates
// -------------------
TEST(Voting, read_num_candidates_1)
{
    istringstream r("1\n");
	const int c = read_num_candidates(r);
	ASSERT_EQ(1,c);
}
TEST(Voting, read_num_candidates_2)
{
    istringstream r("20\n");   
	const int c = read_num_candidates(r);
	ASSERT_EQ(20,c);	
}
TEST(Voting, read_num_candidates_3)
{
    istringstream r("9001\n");
	const int c = read_num_candidates(r);
	ASSERT_EQ(9001,c);	
}
TEST(Voting, read_num_candidates_4)
{
    istringstream r("12342134\n");
    const int c = read_num_candidates(r);
    ASSERT_EQ(12342134,c);  
}



// -------------------
// read_candidates
// -------------------
TEST(Voting, read_candidates_1)
{
    std::istringstream r("Bill Gates\nWolverine\nDoctor Who\n");
	const std::vector<string> v = read_candidates(r,3);
    string zero = "0";
    string bill = "Bill Gates";
    string claws = "Wolverine";
    string who = "Doctor Who";
    std::vector<string> test;
    test.push_back(zero);
    test.push_back(bill);
    test.push_back(claws);
    test.push_back(who);
	ASSERT_EQ(test,v);		
}

TEST(Voting, read_candidates_2)
{
    std::istringstream r("Spock\n");
    const std::vector<string> v = read_candidates(r,1);
    string zero = "0";
    string spock = "Spock";
    std::vector<string> test;
    test.push_back(zero);
    test.push_back(spock);
    ASSERT_EQ(test,v);      
}

TEST(Voting, read_candidates_3)
{
    std::istringstream r("Albus Percival Wulfric Brian Dumbledore\nCharles 'Chewie' Chewbacca (Furball)\nAragorn, Son of Arathor aka: Elessar Telcontar, Estel, Strider, and Wingfoot\nAquaman\n");
    const std::vector<string> v = read_candidates(r,4);
    string zero = "0";
    string dumbledore = "Albus Percival Wulfric Brian Dumbledore";
    string chewie = "Charles 'Chewie' Chewbacca (Furball)";
    string aragorn = "Aragorn, Son of Arathor aka: Elessar Telcontar, Estel, Strider, and Wingfoot";
    string Aquaman = "Aquaman";
    std::vector<string> test;
    test.push_back(zero);
    test.push_back(dumbledore);
    test.push_back(chewie);
    test.push_back(aragorn);
    test.push_back(Aquaman);
    ASSERT_EQ(test,v);      
}

TEST(Voting, read_candidates_4)
{
    std::istringstream r("Charles 'Chewie' Chewbacca (Furball)\nAquaman\n");
    const std::vector<string> v = read_candidates(r,2);
    string zero = "0";
    string chewie = "Charles 'Chewie' Chewbacca (Furball)";
    string Aquaman = "Aquaman";
    std::vector<string> test;
    test.push_back(zero);
    test.push_back(chewie);
    test.push_back(Aquaman);
    ASSERT_EQ(test,v);      
}

// -------------------
// get_ballot_list
// -------------------

TEST(Voting, get_ballot_list_1)
{
    std::istringstream r("1 3 2 4\n");
    std::vector<Ballot> v = get_ballot_list(r);
    std::vector<int> v1;
    v1.push_back(1);
    v1.push_back(3);
    v1.push_back(2);
    v1.push_back(4);
    std::vector<int> returned = v[0].getBallot();
    ASSERT_EQ(v1, returned);
}

TEST(Voting, get_ballot_list_2)
{
    std::istringstream r("1 3 2 4\n1 2 4 3\n");
    std::vector<Ballot> v = get_ballot_list(r);
    std::vector<int> v1;
    v1.push_back(1);
    v1.push_back(3);
    v1.push_back(2);
    v1.push_back(4);
    std::vector<int> v2;
    v2.push_back(1);
    v2.push_back(2);
    v2.push_back(4);
    v2.push_back(3);
    std::vector<int> returned_1 = v[0].getBallot();
    std::vector<int> returned_2 = v[1].getBallot();
    ASSERT_EQ(v1, returned_1);
    ASSERT_EQ(v2, returned_2);
}

TEST(Voting, get_ballot_list_3)
{
    std::istringstream r("1 3 2 4\n1 2 4 3\n3 2 4 1\n");
    std::vector<Ballot> v = get_ballot_list(r);
    std::vector<int> v1;
    v1.push_back(1);
    v1.push_back(3);
    v1.push_back(2);
    v1.push_back(4);
    std::vector<int> v2;
    v2.push_back(1);
    v2.push_back(2);
    v2.push_back(4);
    v2.push_back(3);
    std::vector<int> v3;
    v3.push_back(3);
    v3.push_back(2);
    v3.push_back(4);
    v3.push_back(1);
    std::vector<int> returned_1 = v[0].getBallot();
    std::vector<int> returned_2 = v[1].getBallot();
    std::vector<int> returned_3 = v[2].getBallot();
    ASSERT_EQ(v1, returned_1);
    ASSERT_EQ(v2, returned_2);
    ASSERT_EQ(v3, returned_3);
}

TEST(Voting, get_ballot_list_4)
{
    std::istringstream r("1 3 2 4 5\n1 5 2 4 3\n5 3 2 4 1\n");
    std::vector<Ballot> v = get_ballot_list(r);
    std::vector<int> v1;
    v1.push_back(1);
    v1.push_back(3);
    v1.push_back(2);
    v1.push_back(4);
    v1.push_back(5);
    std::vector<int> v2;
    v2.push_back(1);
    v2.push_back(5);
    v2.push_back(2);
    v2.push_back(4);
    v2.push_back(3);
    std::vector<int> v3;
    v3.push_back(5);
    v3.push_back(3);
    v3.push_back(2);
    v3.push_back(4);
    v3.push_back(1);
    std::vector<int> returned_1 = v[0].getBallot();
    std::vector<int> returned_2 = v[1].getBallot();
    std::vector<int> returned_3 = v[2].getBallot();
    ASSERT_EQ(v1, returned_1);
    ASSERT_EQ(v2, returned_2);
    ASSERT_EQ(v3, returned_3);
}

TEST(Voting, evaluate_1)
{//test for the kick then tie
    std::istringstream r("1 3 2\n2 1 3\n3 2 1\n3 1 2\n2 1 3\n2 3 1\n");
    std::vector<Ballot> v = get_ballot_list(r);
    std::vector<int> answer = evaluate(v, 3);
    std::vector<int> test = {2, 3};
    ASSERT_EQ(test, answer);
}

TEST(Voting, evaluate_2)
{//straight tie
    std::istringstream r("1 2 3\n1 2 3\n2 1 3\n2 1 3\n3 2 1\n3 2 1\n");
    std::vector<Ballot> v = get_ballot_list(r);
    std::vector<int> answer = evaluate(v, 3);
    std::vector<int> test = {1, 2, 3};
    ASSERT_EQ(test, answer);
}

TEST(Voting, evaluate_3)
{//blog election
    std::istringstream r("1 2 3 4 5\n2 3 1 4 5\n2 1 3 4 5\n4 5 3 1 2\n5 4 3 2 1\n1 3 2 4 5\n");
    std::vector<Ballot> v = get_ballot_list(r);
    std::vector<int> answer = evaluate(v, 5);
    std::vector<int> test = {1, 2};
    ASSERT_EQ(test, answer);
}

TEST(Voting, evaluate_4)
{//simple majority election
    std::istringstream r("1 2\n2 1\n2 1\n1 2\n2 1\n2 1\n");
    std::vector<Ballot> v = get_ballot_list(r);
    std::vector<int> answer = evaluate(v, 3);
    std::vector<int> test = {2};
    ASSERT_EQ(test, answer);
}