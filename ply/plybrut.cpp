#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> ii;

map<vector<bool>, ll> dist;
ll ans = 0ll;
int H;

void bfs(vector<bool> u)
{
	queue<vector<bool>> q;
	q.push(u);
	dist[u] = 0;
	while (!q.empty())
	{
		vector<bool> v = q.front();
		q.pop();
		bool sol = true;
		int cnt = 0;
		int maxcnt = 0;
		for (int i = 0; i < v.size(); i++)
		{
			if (v[i])
				cnt++;
			else
				cnt--;
			if (cnt < 0)
			{
				sol = false;
				break;
			}
			maxcnt = max(maxcnt, cnt);
		}
		if (sol && maxcnt <= H)
		{
			ans = dist[v];
			return;
		}
		for (int i = 0; i < v.size(); i++)
		{
			vector<bool> dupa = v;
			dupa[i] = !dupa[i];
			if (dist.find(dupa) == dist.end())
			{
				q.push(dupa);
				dist[dupa] = dist[v] + 1;
			}
		}
	}
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n;
	cin >> n >> H;
	string in;
	cin >> in;
	vector<bool> inb(n);
	for (int i = 0; i < n; i++)
	{
		if (in[i] == '(') inb[i] = true;
		else inb[i] = false;
	}
	bfs(inb);
	cout << ans << '\n';
}