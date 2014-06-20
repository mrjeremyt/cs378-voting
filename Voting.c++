// --------------------------------
// projects/Voting/Voting.c++
// Copyright (C) 2014
// Jeremy Thompson
// Daniel Durbin
// --------------------------------

// --------
// includes
// --------

#include <cassert>  // assert
#include <iostream> // endl, istream, ostream
#include <utility>  // make_pair, pair
#include <algorithm>
#include <string>


#include "Voting.h"
using namespace std;

class Ballot
{
public:
	Ballot(vector<int>& v);
	vector<int> vec;
	~Ballot();
	vector<int> get_ballot(){return vec;}
	int current_counted_index;
};

Ballot::Ballot(vector<int>& v)
{
	vec = v;
}

vector<vector<int>> get_ballot_list(istream& in)
{
	string str;
	while(getline(in, str) != 0)
	{
		
	}
}


void read_candidates(std::istream& in, int num_candidates, vector<string>& candidates)
{
	while(num_candidates > 0)
	{
		string a;
		getline(in, a);
		if (a.length() == 0)
			continue;
		else
		{
			candidates.push_back(a);
			num_candidates--;
		}
	}
}

int read_num_candidates(istream& in)
{
	int i = 0;
	cin >> i;
	return i;
}


void run_elections(std::istream& in, std::ostream& out)
{
	vector<string> candidates;
	candidates.reserve(20);
	int num_candidates = read_num_candidates(in);
	read_candidates(cin, num_candidates, candidates);
	vector<vector<int>> ballot_list = get_ballot_list(in);
	cout << candidates.front() << endl;

}

