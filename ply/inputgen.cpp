#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

mt19937 gen;

ll getRandomNumber(ll lower, ll upper)
{
	uniform_int_distribution<ll> dist(lower, upper);
	return dist(gen);
}

int main(int argc, char **argv)
{
	gen.seed(stoi(argv[1]));
	int n = 10;
	int h = getRandomNumber(1, 2);
	int cnt = 0;
	cout << n << " " << h << '\n';
	for (int i = 0; i < n; i++)
	{
		if (cnt == 0)
		{
			cout << '(';
			cnt++;
		}
		else if (cnt == n - i)
		{
			cout << ')';
			cnt--;
		}
		else
		{
			int dupa = getRandomNumber(0, 1);
			if (dupa == 0)
			{
				cout << '(';
				cnt++;
			}
			else
			{
				cout << ')';
				cnt--;
			}
		}
	}
	cout << '\n';
}
