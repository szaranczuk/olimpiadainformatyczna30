#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	ll n, H;
	cin >> n >> H;
	string in;
	cin >> in;
	bool dupsko = false;
	ll depth = 0;
	ll maxdepth = 0;
	ll plus = 0ll;
	ll ans = 0ll;
	for (int i = 0; i < n; i++)
	{
		if (in[i] == '(') depth++;
		else depth--;
		if (depth > H) 
		{
			ans++;
			depth -= 2;
		}
		else if (depth < 0)
		{
			ans++;
			depth += 2;
		}
	}
	cout << ans << '\n';
}