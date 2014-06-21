// --------------------------------
// projects/Voting/Voting.h
// Copyright (C) 2014
// Jeremy Thompson
// Daniel Durbin
// --------------------------------


#ifndef Voting_h
#define Voting_h

// --------
// includes
// --------
#include <cassert>  // assert
#include <iostream> // endl, istream, ostream
#include <utility>  // make_pair, pair
#include <algorithm>
#include <string>
#include <sstream>
#include <iterator>
using namespace std;


class Ballot
{
public:
	Ballot(vector<int>& v);
	vector<int> vec;
	//~Ballot();
	vector<int> getBallot();
	int current_counted_index;
};

void run_elections(istringstream&, ostringstream&);

int read_num_candidates(istringstream&);

vector<string> read_candidates(istringstream& in, int num_candidates);

vector<Ballot> get_ballot_list(istringstream& in);

void print_ballot_list(vector<Ballot> ballot_list);

void print_candidate_list(vector<string> candidate_list);

#endif // Voting_h