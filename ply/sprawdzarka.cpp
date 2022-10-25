#include <bits/stdc++.h>

using namespace std;

int main(int argc, char** argv)
{
	int n = stoi(argv[4]);
	int i;
	if (argc == 6)
		i = stoi(argv[5]);
	else
		i = 0;
	for (; i < n; i++)
	{
		cout << "Test " << i << ": ";
		string inputgen(argv[1]);
		stringstream ss;
		ss << i;
		inputgen += " ";
		inputgen += ss.str();
		inputgen += " > input.txt";
		system(inputgen.c_str());
		string wzorcuwa(argv[2]);
		wzorcuwa += " < input.txt > output1.txt";
		system(wzorcuwa.c_str());
		string brut(argv[3]);
		brut += " < input.txt > output2.txt";
		system(brut.c_str());
		system("diff -q output1.txt output2.txt > diff.txt");
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