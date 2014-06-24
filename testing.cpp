#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main(int argc, char const *argv[])
{
	int i = 0;
	int j = 3;
	int result = i + j;
	vector<int> v = {1, 2, 3, 4, 5};
	while(i + j < 10)
	{
		i++;
	}
	cout << result << endl;
	vector<int>::iterator it;
	it = find (v.begin(), v.end(), 6);
	cout << *it << endl;


	return 0;
}