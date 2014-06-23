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
	int majority = (ceil(ballot_list.size()) / 2) + 1;
	vector<int> winners; //List of winners, based on cand. index.
	vector<int> candidates; //Stores tally of each candidate based on cand. index.
	for(int i = 0; i < num_candidates+1; i++) //Placing 0s until we count ballots.
		{candidates.push_back(0);}
	
	vector<int> losers;
	losers.push_back(0);
	int size_of_losers = 1;
	int while_check = (num_candidates - (size_of_losers - 1));
	while(while_check >= 2)
	{
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
			if(candidates[i] > candidates[highest_votes])
				highest_votes = i;
		}

		cout << "majority: " << majority << endl;
		cout << "winner: " << candidates[highest_votes] << endl;
		if(candidates[highest_votes] >= majority) //Winner
		{
			winners.push_back(highest_votes);
			return winners;	
		}

		cout << "while_check: " << while_check << endl;
		if(while_check == 2)
		{
			for(unsigned int i = 0; i < candidates.size(); i++)
			{
				for(unsigned int j = 0; j < losers.size(); j++)
				{
					if(losers[j] == 1)
						if(j != i)
							winners.push_back(i);
				}
			}
			for(auto elem: winners){cout << winners[elem];}
			return winners;
		}

		int min_value =  *(min_element(candidates.begin()+1, candidates.end()));
		for(unsigned int i = 1; i < candidates.size(); i++)
		{
			cout << "setting loser" << endl;
			cout << "loser size: " << losers.size() << endl;
			if(candidates[i] == min_value)
			{
				losers[i] = 1;
				size_of_losers++;
			}
			cout << "loser size: " << losers.size() << endl;
		}
		for(unsigned int i = 0; i < ballot_list.size(); i++)
		{
			cout << "in the loosers kick" << endl;
			Ballot b = ballot_list[i];
			bool increased_index = true;
			while (increased_index)
			{
				increased_index = check_losers(losers,b, size_of_losers);
			}

		}
	}

}

bool check_losers(vector<int> losers, Ballot &b, int size_of_losers)
{
	vector<int> v = b.getBallot();
	for(unsigned int i = 1; i < size_of_losers; i++)
	{
		if (losers[i] == 1){
			if (v[b.current_counted_index] == (int)i){
				b.current_counted_index++;
				return true;}
			}

	}
	return false;
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

