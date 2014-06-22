// --------------------------------
// projects/Voting/Voting.c++
// Copyright (C) 2014
// Jeremy Thompson
// Daniel Durbin
// --------------------------------

// --------
// includes
// --------

// #include <cassert>  // assert
// #include <iostream> // endl, istream, ostream
// #include <utility>  // make_pair, pair
// #include <algorithm>
// #include <string>
// #include <sstream>
// #include <iterator>


#include "Voting.h"
using namespace std;

// -------------------------
// Balllot class definitions
// -------------------------

Ballot::Ballot(vector<int>& v)
{
	vec = v;
	current_counted_index = 0;
}

vector<int> Ballot::getBallot(){return vec;}


// ----------------------------------
// evaluates the ballots for a winner
// ----------------------------------


vector<int> evaluate(vector<Ballot> ballot_list, int num_candidates)
{
	int majority = (ceil(ballot_list.size())/ceil(num_candidates)) + 1;
	vector<int> winners; //List of winners, based on cand. index.
	vector<int> candidates; //Stores tally of each candidate based on cand. index.
	for(int i = 0; i < num_candidates+1; i++) //Placing 0s until we count ballots.
		{candidates.push_back(0);}
	for(unsigned int i = 0; i < ballot_list.size(); i++) //Countes votes for each ballot.
	{
		Ballot b = ballot_list[i];
		vector<int> v = b.getBallot();
		int cand = v[b.current_counted_index];
		candidates[cand] += 1;
	}

	int highest_votes = -1;
	for(unsigned int i = 1; i < candidates.size(); i++)
	{
		if(candidates[i] > highest_votes) 
			highest_votes = i;
	}
	int min_value =  *(min_element(candidates.begin()+1, candidates.end()));
	winners.push_back(highest_votes);
	return winners;

}

// -------------------------------
// parses and collects the ballots
// -------------------------------

vector<Ballot> get_ballot_list(istream& in)
{
	vector<Ballot> result;
	string str;
	while(getline(in, str) != 0)
	{
		if(str.empty())
			break;
		string token;
		vector<int> choices;
		vector<string> tokens;
		istringstream iss(str);
		while(iss >> token)
			{ 
				int n;
				istringstream (token) >> n;
				choices.push_back(n); 
			}
		Ballot b (choices);
		result.push_back(b);
	}
	return result;
}

void print_ballot_list(vector<Ballot> ballot_list)
{
	for(unsigned int i = 0; i < ballot_list.size(); i++)
	{
		Ballot b = ballot_list[i];
		vector<int> v = b.getBallot();
		for(unsigned int j = 0; j < v.size(); j++)
		{
			cout << v[j];
		}
		cout << endl;
	}
}

void print_candidate_list(vector<string> candidate_list)
{
	for(unsigned int i = 0; i < candidate_list.size(); i++)
	{
		cout << candidate_list[i] << endl;
	}

}

// ------------------------------
// puts candidates in a container
// ------------------------------

vector<string> read_candidates(istream& in, int num_candidates)
{
	vector<string> candidates;
	candidates.push_back("0");
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
	return candidates;
}

int read_num_candidates(istream& in)
{
	int i = 0;
	in >> i;
	return i;
}

// ----------------------------------
// functions that runs each elections
// ----------------------------------

void run_elections(istream& in, ostream& out)
{
	vector<string> candidates;
	candidates.reserve(20);
	int num_candidates = read_num_candidates(in);
	candidates = read_candidates(in, num_candidates);
	vector<Ballot> ballot_list = get_ballot_list(in);
	vector<int> winner = evaluate(ballot_list, num_candidates);
	// print_candidate_list(candidates);
	//print_ballot_list(ballot_list);
	out << candidates[winner[0]];


}

