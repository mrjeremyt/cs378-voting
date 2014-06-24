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
void check_losers(vector<vector<Ballot>> &all_ballots, int index, vector<int> losers)
{
	// cout << "index: " << index << endl;
	vector<Ballot> v = all_ballots[index];
	for(unsigned int i = 0; i < v.size(); i++)
	{
		Ballot b = v[i];
		vector<int> sheet = b.getBallot();
		bool check = true;
		while(check)
		{
			vector<int>::iterator it;
			it = find (losers.begin(), losers.end(), sheet[b.current_counted_index]);
			if(*it == 0 || *it > (int)losers.size())
			{
				check = false;
			}
			else
			{
				// cout << "advancing counter" << endl;
				// cout<< "iterator: " << *it << endl;
				b.current_counted_index++;
				check = true;
			}
		}
		// cout << "current vote: " << sheet[b.current_counted_index] << endl;
		all_ballots[sheet[b.current_counted_index]].push_back(b);
	}
	all_ballots[index].clear();
}

// ----------------------------------
// evaluates the ballots for a winner
// ----------------------------------

vector<int> evaluate(vector<Ballot> ballot_list, int num_candidates)
{
	int size_of_ballot_list = ballot_list.size();

	//setup the bag that holds all the bags
	vector<vector<Ballot>> all_ballots;
	for(int i = 0; i <= num_candidates; i++)
	{
		vector<Ballot> v;
		all_ballots.push_back(v);
	}

	//go through all the ballots and sort them into the bags
	for(int i = 0; i < size_of_ballot_list; i++)
	{
		Ballot b = ballot_list[i];
		vector<int> ballot = b.getBallot();
		int bag_num = ballot[b.current_counted_index];
		all_ballots[bag_num].push_back(ballot);
	}

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
		for(unsigned int i = 1; i < all_ballots.size(); i++) //Counts votes for each ballot.
		{
			vector<Ballot> bag = all_ballots[i];
			candidates[i] = bag.size();
			// cout << "bag size: " << bag.size() << endl;
		}
		int highest_votes = -1;
		for(unsigned int i = 1; i < candidates.size(); i++)
		{
			if(candidates[i] > candidates[highest_votes])
				highest_votes = i;
		}
		// cout << "majority: " << majority << endl;
		// cout << "highest_votes: " << candidates[highest_votes] << endl;

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
				if (candidates[i] == tie_value || losers[i] == (int)i)
					continue;
				else
					good_tie = false;
			}	
			if(good_tie){
				for(unsigned int i = 1; i < candidates.size(); i++)
				{
					if(losers[i] == (int)i)
						continue;
					else 
						winners.push_back(i);
				}
				return winners;
			}
		}
		int min_value = 100000000;
		int temp = 0;
		for(unsigned int i = 1; i < candidates.size(); i++)//calculates the min value of the remaining valid candidates
		{
			if(losers[i] == (int)i){continue;}
			else
			{
				temp = candidates[i];
				if(temp < min_value){min_value = temp;}
			}
		}
		// cout << "min_value: " << min_value << endl;
		for(unsigned int i = 1; i < candidates.size(); i++)
		{
			if(candidates[i] == min_value) //This is finding the loser.
			{
				losers[i] = i;
				size_of_losers++;
			}
		}
		// cout << "size_of_losers: " << size_of_losers << endl;
		//moves the current counted index forward for the losing candidates and moves its ballot to its new bag
		for(unsigned int i = 1; i < all_ballots.size(); i++) 
		{
			// cout << "loser for loop" << endl;
			if(losers[i] == (int)i){check_losers(all_ballots, i, losers);}
		}
		candidates.clear();
		for(int i = 0; i < num_candidates+1; i++){candidates.push_back(0);} //Placing 0s until we count ballots.
		// cout << "end of while" << endl;
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



int main()
{
	using namespace std;
	int num_elections;
	cin >> num_elections;
	while (num_elections > 0)
	{
		run_elections(cin,cout);
        if(num_elections > 1)
            cout << "\n" << endl;
		num_elections--;
	}
    cout << "\n";
	return 0;
}