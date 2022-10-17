#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

mt19937 gen;

ll getRandomNumber(ll lower, ll upper)
{
	uniform_int_distribution<ll> dist(lower, upper);
	return dist(gen);
}

int main(int argc, char** argv)
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	gen.seed(stoi(argv[1]));
	int n = 7;
	int k = 4;
	cout << n << " " << k << '\n';
	vector<int> cnt(n);
	queue<int> q;
	for (int i = 0; i < n - 2; i++)
	{
		int val = getRandomNumber(0, n - 1);
		q.push(val);
		cnt[val]++;
	}
	while (!q.empty())
	{
		int v = q.front();
		q.pop();
		int i = 0;
		for (; i < n; i++)
		{
			if (cnt[i] == 0) break;
		}
		cout << i + 1 << " " << v + 1 << " " << getRandomNumber(1, 10) << '\n';
		cnt[i]--;
		cnt[v]--;
	}
	int j = 0;
	for (int i = 0; i < n; i++)
	{
		if (cnt[i] == 0 && j == 0)
		{
			cout << i + 1 << " ";
			j++;
		}
		else if (cnt[i] == 0 && j == 1)
		{
			cout << i + 1 << " " << getRandomNumber(1, 10) << '\n';
			break;
		}
	}
	for (int i = 2; i <= k + 1; i++) cout << i << '\n';
}