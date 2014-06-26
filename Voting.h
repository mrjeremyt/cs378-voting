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
#include <algorithm>
#include <string>
#include <sstream>
#include <iterator>
#include <vector>
using namespace std;

class Ballot;
class Bag;


void run_elections(istream&, ostream&);

int read_num_candidates(istream&);

vector<string> read_candidates(istream& in, int num_candidates);

vector<Ballot> get_ballot_list(istream& in);

void print_ballot_list(vector<Ballot> ballot_list);

void print_candidate_list(vector<string> candidate_list);

vector<int> evaluate(vector<Ballot> ballot_list, int num_candidates);

bool check_losers(vector<int> losers, Ballot &b, vector<vector<Ballot>>);

#endif // Voting_h