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
	vector<int> getBallotVector();
	int current_counted_index;
	int selected_candidate();
};

Ballot::Ballot(vector<int>& v)
{
	vec = v;
	current_counted_index = 0;
}

vector<int> Ballot::getBallotVector(){return vec;}
int Ballot::selected_candidate(){return vec[current_counted_index];}



class Bag
{
public:
	Bag();
	vector<int> v; //list of the indexes of Ballots from ballot_list
	int size;
	int get(int i);
	void add(int i);
	int length();
	void cleanup();
};

Bag::Bag(){size = 0;}

int Bag::get(int i){return v[i];}

int Bag::length(){return size;}

void Bag::add(int i)
{
	v.push_back(i);
	size++;
}

void Bag::cleanup(){v.clear(); size = 0;}


// ----------------------------------
// evaluates the ballots for a winner
// ----------------------------------

vector<int> evaluate(vector<Ballot> ballot_list, int num_candidates)
{
	//commonly used variable declaration
	vector<int> winners;
	vector<int> candidates;
	vector<int> losers;
	int size_of_ballot_list = ballot_list.size();
	int size_of_losers;
	int size_of_candidates;
	int tie_value;
	int tie_remainder;
	bool good_tie;
	vector<Bag> all_ballots;
	int majority;

	//variable initialization for those that need it
	majority = ceil(size_of_ballot_list/2) + 1;
	size_of_losers = 0;
	for(int i = 0; i <= num_candidates; i++)
	{
		candidates.push_back(0); 
		losers.push_back(0);
		Bag b;
		all_ballots.push_back(b);
	}

	size_of_candidates = candidates.size();

	//puts all the ballots in ballot_list into bags that can be analyzed in the function
	for(int i = 0; i < size_of_ballot_list; i++)
	{
		all_ballots[ballot_list[i].selected_candidate()].add(i);
	}


	//this while loop controls all the rounds
	while(true)
	{
		//declaration of variables used in the while loop
		int highest_vote_index = -1;
		tie_remainder = size_of_ballot_list % (num_candidates - size_of_losers);
		good_tie = true;

		//loop that counts the number of ballots for each candidate
		for(int i = 1; i < (int)all_ballots.size(); i++){candidates[i] = all_ballots[i].length();}
		
		//finds the/a candidate with the most votes
		for(int i = 1; i < size_of_candidates; i++)
		{
			if(candidates[i] > candidates[highest_vote_index]){highest_vote_index = i;}
		}

		//checks to see if we have a clear winner
		if(candidates[highest_vote_index] >= majority)
		{
			winners.push_back(highest_vote_index);
			return winners;
		}

		//else, might have a tie
		//see if it's possible to have a tie
		if(tie_remainder == 0)
		{
			tie_value = size_of_ballot_list / (num_candidates - size_of_losers);
			for(int i = 1; i < size_of_candidates; i++)
			{
				if(candidates[i] == tie_value || losers[i] == (int)i)
					continue;
				else
					good_tie = false;
			}
			if(good_tie)
			{
				for(int i = 1; i < size_of_candidates; i++)
				{
					if(losers[i] == (int)i)
						continue;
					else
						winners.push_back(i);
				}
				return winners;
			}
		}

		//else we need to kick the looser and change the vote

		//first, find the minimum value
		int min_value = 10000000;
		for(int i = 1; i < size_of_candidates; i++)
		{
			if(losers[i] == i){continue;}
			else{if(candidates[i] < min_value){min_value = candidates[i];}}
		}

		for(int i = 1; i < size_of_candidates; i++)
		{	
			if(candidates[i] == min_value)
			{
				losers[i] = i;
				size_of_losers++;
			}
		}

		//losers have been found and incremented. time to advance the vote
		for(int i = 1; i < (int)all_ballots.size(); i++)
		{
			if(losers[i] == i) //indicates this is a losing candidate
			{
				Bag &bg = all_ballots[i]; //gets tbe bag of the indexes of the ballots to change
				for(int j = 0; j < bg.length(); j++)
				{
					Ballot &b = ballot_list[bg.get(j)]; //gets the ballot from ballot_list at index from the bag
					bool check = true;
					while(check)
					{
						//checks that the current candidate is in losers
						for(int k = 1; k < (int)losers.size(); k++)
						{
							if(losers[k] == b.selected_candidate())
							{
								b.current_counted_index++;
								check = true;
								break;
							}

							if(k == (int)(losers.size() -1))
							{	check = false;
								break;
							}
						}
					}
					int ind = bg.get(j);
					all_ballots[b.selected_candidate()].add(ind); //adds the new index of the ballot to the new bag for its selected candidate
				}
				all_ballots[i].cleanup();
			}
		}
		candidates.clear();
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

// g++-4.7 -fprofile-arcs -ftest-coverage -pedantic -std=c++11 -ggdb3 -Wall UVaVoting.c++ -o UVaVoting
