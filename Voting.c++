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
#include <algorithm>
#include <string>
#include <sstream>
#include <iterator>
#include <vector>


#include "Voting.h"
using namespace std;

// -------------------------
// Balllot class definitions
// -------------------------

class Ballot
{
public:
	Ballot(vector<int>& v);
	vector<int> vec;
	//~Ballot();
	vector<int> getBallot();
	int current_counted_index;
};

Ballot::Ballot(vector<int>& v)
{
	vec = v;
	current_counted_index = 0;
}

vector<int> Ballot::getBallot(){return vec;}

//---------------------------
// helper method for evaluate
//---------------------------

/* This checks the ballot position to make sure it doesn't point to a loser. Advances
current_counted_index of the ballot if it does.*/
bool check_losers(vector<int> losers, Ballot &b)
{
	vector<int> v = b.getBallot();
	for(unsigned int i = 1; i < losers.size(); i++)
	{
		// cout << "Loser in check_losers: "<< losers[i] << endl;
		if (losers[i] == 1)
		{
			if (v[b.current_counted_index] == (int)i){
			b.current_counted_index++;
			return true;}
		}
	}
	return false;
}

// ----------------------------------
// evaluates the ballots for a winner
// ----------------------------------

vector<int> evaluate(vector<Ballot> ballot_list, int num_candidates)
{
	int size_of_ballot_list = ballot_list.size();
	int majority = ceil(size_of_ballot_list / 2) + 1;
	vector<int> winners; //List of winners, based on cand. index.
	vector<int> candidates; //Stores tally of each candidate based on cand. index.
	for(int i = 0; i < num_candidates+1; i++){candidates.push_back(0);} //Placing 0s until we count ballots.
	vector<int> losers;
	losers.reserve(20);
	for(int i = 0; i < num_candidates+1; i++){losers.push_back(0);} //Placing 0s until we count ballots.
	int size_of_losers = 0;
	int tie_value = size_of_ballot_list / (num_candidates - size_of_losers);
	int tie_remainder = size_of_ballot_list % (num_candidates - size_of_losers);
	bool good_tie = true;
	while(true)
	{
		for(int i = 0; i < size_of_ballot_list; i++) //Countes votes for each ballot.
		{
			Ballot b = ballot_list[i];
			vector<int> v = b.getBallot();
			int cand = v[b.current_counted_index];
			candidates[cand] += 1;
		}
		int highest_votes = -1;
		for(unsigned int i = 1; i < candidates.size(); i++)
		{
			if(candidates[i] > candidates[highest_votes])
				highest_votes = i;
		}
		if(candidates[highest_votes] >= majority) //Winner
		{
			winners.push_back(highest_votes);
			return winners;	
		}
		//Calculate tie, if all have tie value, return all as winners.
		tie_remainder = size_of_ballot_list % (num_candidates - size_of_losers);
		good_tie = true;
		if (tie_remainder == 0){
			tie_value = size_of_ballot_list / (num_candidates - size_of_losers);
			for(unsigned int i = 1; i < candidates.size(); i++)
			{
				if (candidates[i] == tie_value || losers[i] == 1)
					continue;
				else
					good_tie = false;
			}	
			if(good_tie){
				for(unsigned int i = 1; i < candidates.size(); i++)
				{
					if(losers[i] == 1)
						continue;
					else 
						winners.push_back(i);
				}
				return winners;
			}
		}
		int min_value =  100000000;
		int temp = 0;
		for(unsigned int i = 1; i < candidates.size(); i++)//calculates the min value of the remaining valid candidates
		{
			if(losers[i] == 1){continue;}
			else
			{
				temp = candidates[i];
				if(temp < min_value){min_value = temp;}
			}
		}
		for(unsigned int i = 1; i < candidates.size(); i++)
		{
			if(candidates[i] == min_value) //This is finding the loser.
			{
				losers[i] = 1;
				size_of_losers++;
			}
		}
		for(int i = 0; i < size_of_ballot_list; i++) //moves the current counted index forward if it's a losing candidate
		{
			Ballot &b = ballot_list[i];
			bool increased_index = true;
			while (increased_index){increased_index = check_losers(losers,b);}
		}
		candidates.clear();
		for(int i = 0; i < num_candidates+1; i++){candidates.push_back(0);} //Placing 0s until we count ballots.
	}

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
	// print_ballot_list(ballot_list);
	if(winner.size() == 1)
		out << candidates[winner[0]];
	else
	{
		for(unsigned int i = 0; i < winner.size(); i++)
		{
			out << candidates[winner[i]];
			if(i < (winner.size() - 1))
				out << endl;
		}
	}
}