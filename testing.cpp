#include <iostream>

int main(int argc, char const *argv[])
{
	int i = 0;
	int j = 3;
	int result = i + j;
	while(result < 10)
	{
		i++;
	}
	std::cout << result;
	return 0;
}