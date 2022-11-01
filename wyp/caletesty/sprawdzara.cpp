#include <bits/stdc++.h>

using namespace std;

int main(int argc, char** argv)
{
	int first = stoi(argv[1]);
	int last = stoi(argv[2]);
	for (int i = first; i < last; i++)
	{
		cout << "Test " << i << ": ";
		stringstream ss;
		ss << "./wzo < in/" << i << ".in > output1.txt";
		system(ss.str().c_str());
		ss.str("");
		ss << "diff -wq output1.txt out/" << i << ".out > diff.txt";
		system(ss.str().c_str());
		if (filesystem::is_empty("diff.txt"))
		{
			cout << "OK\n";
		}
		else
		{
			cout << "ZLE\n";
			return 2137;
		}
	}
}