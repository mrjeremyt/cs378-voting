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








void read_candidates(int num_candidates)
{
	while(num_candidates > 0)
	{
		string a;
		cin >> a;
		cout << a << endl;
		num_candidates--;
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
	int num_candidates = read_num_candidates(in);
	read_candidates(num_candidates);


}

