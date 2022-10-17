#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<ll, int> ii;

vector<vector<ii>> Adj;
vector<bool> isWioska;
vector<int> p;
vector<ii> t;
vector<ll> subtree_size;
vector<ll> dist;
vector<int> idx;
set<int> dupadupa;
ll free_idx = 0ll;
//vector<bool> vis;


void dfs1(int v, ll& path)
{
	idx[v] = free_idx;
	if (p[v] == 0) dupadupa.insert(free_idx);
	free_idx++;
	dist[v] = path;
	for (ii u : Adj[v])
	{
		if (u.second != p[v])
		{
			p[u.second] = v;
			path += u.first;
			dfs1(u.second, path);
			path -=u.first;
			subtree_size[idx[v]] += subtree_size[idx[u.second]] + 1;
		}
	}
}

void update(int pos, int tl, int tr, ll v, int dupa)
{
	if (tl == tr)
	{
		t[v].first = dist[dupa];
		t[v].second = 1;
	}
	else
	{
		int tm = (tl + tr) /2;
		if (pos <= tm) update(pos, tl, tm, 2*v, dupa);
		else update(pos, tm + 1, tr, 2 * v + 1, dupa);
		t[v].first = t[2*v].first + t[2*v+1].first;
		t[v].second = t[2*v].second + t[2*v+1].second;
	}
}

ii sum(int l, int r, int tl, int tr, ll v)
{
	if (tr < l || r < tl) return {0ll, 0};
	else if (l <= tl && tr <= r) return t[v];
	else
	{
		int tm = (tl + tr)/2;
		ii res1 = sum(l, r, tl, tm, 2*v);
		ii res2 = sum(l, r, tm + 1, tr, 2 * v + 1);
		ii res = {res1.first + res2.first, res1.second + res2.second};
		return res;
	}
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ll n, k;
    cin >> n >> k;
    Adj.resize(n);
    p.assign(n, -1);
    isWioska.assign(n, false);
    t.assign(4 * (n + 5) + 10, {0ll, 0});
    idx.resize(n);
    subtree_size.assign(n, 0);
    dist.assign(n, 0);
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
    ll path = 0ll;
    //dfs rekurencyjnie sie wysrywa xD
    stack<ii> dfs;
    vector<bool> vis(n, false);
    dfs.push({0ll, 0});
    while (!dfs.empty())
    {
	    ii v = dfs.top();
	    if (vis[v.second])
	    {
		    path -= v.first;
		    for (ii u : Adj[v.second])
		    {
			if (u.second != p[v.second])
				subtree_size[idx[v.second]] += subtree_size[idx[u.second]] + 1;
		    }
		    dfs.pop();
		    continue;
	    }
	    path += v.first;
	    dist[v.second] = path;
	    vis[v.second] = true;
	    idx[v.second] = free_idx;
	    if (p[v.second] == 0) dupadupa.insert(free_idx);
	    free_idx++;
	    for (ii u : Adj[v.second])
	    {
		    if (!vis[u.second])
		    {
			    p[u.second] = v.second;
			    dfs.push(u);
		    }
	    }
    }
    ll res = 0ll;
    update(0, 0, n -1, 1, 0);
    for (int i = 0; i < k; i++)
    {
	    int a;
	    cin >> a;
	    a--;
	    ll dupa = 0ll;
	    ii lower_wioski = sum(idx[a], idx[a] + subtree_size[idx[a]], 0, n - 1, 1);
	    dupa += lower_wioski.first;
	    dupa -= dist[a] * lower_wioski.second;
	    auto one_off_root_it = (dupadupa.upper_bound(idx[a]));
	    one_off_root_it--;
	    int one_off_root = *one_off_root_it;
	    ii upper_wioski = sum(one_off_root, one_off_root + subtree_size[one_off_root], 0, n - 1, 1);
	    upper_wioski.first -= lower_wioski.first;
	    upper_wioski.second -= lower_wioski.second;
	    dupa += (upper_wioski.second * dist[a] - upper_wioski.first);
	    upper_wioski.first += lower_wioski.first;
	    upper_wioski.second += lower_wioski.second;
	    ii all_wioski = sum(0, n - 1, 0, n - 1, 1);
	    all_wioski.first -= upper_wioski.first;
	    all_wioski.second -= upper_wioski.second;
	    dupa += all_wioski.first;
	    dupa += dist[a] * all_wioski.second;
	    res += dupa * 2;
	    update(idx[a], 0, n -1, 1, a);
	    cout << res << '\n';
    }
}