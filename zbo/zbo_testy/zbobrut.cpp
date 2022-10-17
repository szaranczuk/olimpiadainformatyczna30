#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<ll, int> ii;

vector<vector<ii>> Adj;
vector<bool> isWioska;
vector<bool> vis;
//vector<bool> vis;


ll dfs1(int v, ll path)
{
	ll res = 0ll;
	vis[v] = true;
	for (ii u : Adj[v])
	{
		if (!vis[u.second])
		{
			res += dfs1(u.second, path + u.first);
			if (isWioska[u.second]) res += path + u.first;
		}
	}
	return res;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ll n, k;
    cin >> n >> k;
    Adj.resize(n);
    isWioska.assign(n, false);
    isWioska[0] = true;
    for (int i = 0; i < n - 1; i++)
    {
        int a, b;
        ll w;
        cin >> a >> b >> w;
        a--;
        b--;
        Adj[a].push_back({w, b});
        Adj[b].push_back({w, a});
    }
    ll res = 0ll;
    while (k--)
    {
	    int a;
	    cin >> a;
	    a--;
	    vis.clear();
	    vis.assign(n, false);
	    res += 2 * dfs1(a, 0ll);
	    cout << res << '\n';
	    isWioska[a] = true;
    }
}