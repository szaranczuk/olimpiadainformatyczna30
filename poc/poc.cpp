#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> ii;

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	ll n, m, k;
	cin >> n >> m >> k;
	vector<ll> in(n);
	for (int i = 0; i < n; i++)
		cin >> in[i];
	for (int i = 0; i < n; i++)
		in[i]--;
	vector<ll> wzo(m);
	for (int i = 0; i < m; i++)
		cin >> wzo[i];
	for (int i = 0; i < m; i++)
		wzo[i]--;
	vector<int> prev(n, -1);
	vector<int> cnt(n, -1);
	vector<int> last(k, -1);
	
	//liczenie nexta
	for (int i = 0; i < n; i++)
	{
		if (last[in[i]] == -1)
		{
			last[in[i]] = i;
			cnt[i] = 1;
		}
		else
		{
			prev[i] = last[in[i]];
			cnt[i] = cnt[last[in[i]]] + 1;
			last[in[i]] = i;
		}
	}

	//pierwsze wystapienie wzorca
	int cnt2 = 0;
	vector<int> first(m);
	vector<int> lastdupa(m);
	vector<bool> ans(n, false);
	for (int i = 0; i < n; i++)
	{
		if (in[i] == wzo[cnt2]) 
		{
			first[cnt2] = i;
			ans[i] = true;
			cnt2++;
		}
		if (cnt2 == m) break;
	}
	int bound = n + 1;
	vector<bool> vis(k, false);
	for (int i = m - 1; i >= 0; i--)
	{
		while (last[wzo[i]] >= bound)
		{
			last[wzo[i]] = prev[last[wzo[i]]];
		}
		ans[last[wzo[i]]] = true;
		bound = last[wzo[i]];
		lastdupa[i] = bound;
	}
	for (int i = m - 1; i >= 0; i--)
	{
		while (lastdupa[i] >= first[i])
		{
			ans[lastdupa[i]] = true;
			lastdupa[i] = prev[lastdupa[i]];
		}
	}
	for (int i = 0; i < n; i++)
	{
		if (ans[i]) cout << "1 ";
		else cout << "0 ";
	}
	cout << '\n';
	return 0;
}