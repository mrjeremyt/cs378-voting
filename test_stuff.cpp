#include <cassert>  // assert
#include <iostream> // endl, istream, ostream
#include <utility>  // make_pair, pair
#include <algorithm>
#include <string>
#include <sstream>
#include <iterator>
#include <array>
#include <vector>

int main(int argc, char const *argv[])
{
	using namespace std;
	int num_candidates = 4;
	vector<int> losers;
	losers.push_back(0);
	int size_of_losers = 0;
	int while_check = (num_candidates - (size_of_losers));
	cout << while_check << endl;
	while ((num_candidates - size_of_losers) >= 2)
	{
		// size_of_losers++;
		cout << while_check << endl;
		// while_check = num_candidates - size_of_losers;
	}
	// int a = 5;
	// int ballots = 21;
	// cout<<ceil(ceil(ballots)/ceil(a))<<endl;
	// if (ballots % a > 0)
	// 	cout<<ballots/a + 1<<endl;
	return 0;
}