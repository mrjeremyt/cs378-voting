#include <cassert>  // assert
#include <iostream> // endl, istream, ostream
#include <utility>  // make_pair, pair
#include <math.h>

int main(int argc, char const *argv[])
{
	using namespace std;
	int a = 5;
	int ballots = 21;
	cout<<(ceil(ballots)/ceil(a))<<endl;
	if (ballots % a > 0)
		cout<<ballots/a + 1<<endl;
	return 0;
}