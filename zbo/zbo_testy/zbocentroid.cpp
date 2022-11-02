#include <bits/stdc++.h>

using namespace std;

//implementacja ukradziona z https://medium.com/carpanese/an-illustrated-introduction-to-centroid-decomposition-8c1989d53308

typedef long long ll;
typedef pair<ll, int> ii;
typedef pair<int, bool> ib;

vector<vector<ii>> Adj;

ll chuj = 0ll;
ll chuj2 = 0ll;

struct CentroidDecomposition
{
	const int K = 25;
	int n;
	vector<set<ii>> original_tree;
	vector<map<int, bool>> tree;
	vector<ii> val;
	vector<int> parent; 
	vector<int> sub;
	vector<ii> euler;
	vector<vector<ii>> st;
	vector<int> first;
	vector<ll> root_dist;
	vector<ll> parent_contr;
	ll ans;
	int fastlog(int x)
	{
		return x ? __builtin_clz(1) - __builtin_clz(x) : -1;
	}
	void compute_dist(int v, int p, ll path)
	{
		root_dist[v] = path;
		for (ii u : original_tree[v])
		{
			if (u.second != p) compute_dist(u.second, v, path + u.first);
		}
	}
	int dfs(int v, int p)
	{
		sub[v] = 1;
		for (ib u_p : tree[v])
		{
			if (!u_p.second) continue;
			int u = u_p.first;
			if (u != p) sub[v] += dfs(u, v);
		}
		return sub[v];
	}
	int dfs(int v, int p, int n)
	{
		for (ib u_p : tree[v])
		{
			if (!u_p.second) continue;
			int u = u_p.first;
			if (u != p && sub[u] > n / 2) return dfs(u, v, n);
		}
		return v;
	}
	void build(int v, int p)
	{
		int n = dfs(v, p);
		int centroid = dfs(v, p, n);
		parent[centroid] = p;
		for (auto it = tree[centroid].begin(); it != tree[centroid].end(); ++it)
		{
			if (!it->second) continue;
			it->second = false;
			tree[it->first][centroid] = false;
			build(it->first, centroid);
		}
	}
	void findeuler(int v, int p, int h)
	{
		euler.push_back({h, v});
		first[v] = euler.size() - 1;
		for (ii u : original_tree[v])
		{
			if (u.second != p)
			{
				findeuler(u.second, v, h + 1);
				euler.push_back({h, v});
			}
		}
	}
	void compute_sparse_table()
	{
		euler.reserve(3 * n);
		first.resize(n);
		st.resize(K);
		findeuler(0, -1, 0);
		for (int i = 0; i < K; i++)
		{
			st[i].resize(euler.size());
		}
		st[0] = euler;
		for (int i = 1; i < K; i++)
		{
			for (int j = 0; j + (1 << i) <= euler.size(); j++)
			{
				st[i][j] = min(st[i -1][j], st[i-1][j + (1 << (i - 1))]);
			}
		}
	}
	CentroidDecomposition(vector<set<ii>> &_tree) : original_tree(_tree)
	{
		ans = 0ll;
		n = _tree.size();
		tree.resize(n);
		root_dist.assign(n, 0);
		parent.resize(n);
		sub.resize(n);
		parent_contr.assign(n, 0);
		for (int i = 0; i < n; i++)
		{
			for (ii u : _tree[i])
			{
				tree[i].insert({u.second, true});
			}
		}
		build(0, -1);
		compute_dist(0, -1, 0ll);
		//auto start = chrono::high_resolution_clock::now();
		compute_sparse_table();
		/*auto end = chrono::high_resolution_clock::now();
		auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
		auto dupa = duration.count();*/
		val.assign(n, {0ll, 0});
		int chuj = 5 +5;
	}
	int lca(int a, int b)
	{
		int ind1 = first[a];
		int ind2 = first[b];
		if (ind1 > ind2) swap(ind1, ind2);
		int isize = fastlog(ind2 - ind1 + 1);
		ii res = min(st[isize][ind1], st[isize][ind2 - (1 << isize) + 1]);
		return res.second;
	}
	inline ll dist(int a, int b)
	{
		return root_dist[a] + root_dist[b] - 2*root_dist[lca(a, b)];
	}
	void update(int v)
	{
		int u = parent[v];
		int prev = v;
		ans += val[v].first;
		ll currpath = 0ll;
		int cnt = 0;
		//auto start1 = chrono::high_resolution_clock::now();
		while (u != -1)
		{
			cnt++;
			//auto start2 = chrono::high_resolution_clock::now();
			ll d = dist(v, u);
			//auto end2 = chrono::high_resolution_clock::now();
			//chuj2 += chrono::duration_cast<chrono::nanoseconds>(end2 - start2).count();
			ans += val[u].first - parent_contr[prev] + d*(val[u].second - val[prev].second);
			prev = u;
			u = parent[u];
		}
		//auto end1 = chrono::high_resolution_clock::now();
		//chuj += chrono::duration_cast<chrono::nanoseconds>(end1 - start1).count();
		if (cnt >= 20)
		{
			int chuj = 5 + 5;
		}
		u = v;
		while (u != -1)
		{
			val[u].first += dist(v, u);
			if (parent[u] != -1)
				parent_contr[u] += dist(v, parent[u]);
			val[u].second++;
			u = parent[u];
		}
	}
	ll query() 
	{
		return 2*ans;
	}
};

int main()
{
	//auto start = chrono::high_resolution_clock::now();
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n, k;
	cin >> n >> k;
	vector<set<ii>> tree(n);
	for (int i = 0; i < n - 1; i++)
	{
		int a, b, c;
		cin >> a >> b >> c;
		a--;
		b--;
		tree[a].insert({c, b});
		tree[b].insert({c, a});
	}
	CentroidDecomposition krzysztofolejniktopierdolonyidiota(tree);
	//auto end = chrono::high_resolution_clock::now();
	//auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
	//auto dupa = duration.count();
	krzysztofolejniktopierdolonyidiota.update(0);
	while (k--)
	{
		int v;
		cin >> v;
		v--;
		krzysztofolejniktopierdolonyidiota.update(v);
		cout << krzysztofolejniktopierdolonyidiota.query() << '\n';
	}
	//end = chrono::high_resolution_clock::now();
	//duration = chrono::duration_cast<chrono::milliseconds>(end - start);
	//dupa = duration.count();
	return 0;
}