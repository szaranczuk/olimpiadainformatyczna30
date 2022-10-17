#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<ll, int> ii;

vector<vector<ii>> Adj;
vector<ll> wioska_cost;
vector<ll> wioska_count;
vector<bool> isWioska;
vector<int> p;
//vector<bool> vis;

void dfs1(int v, ll path)
{
    for (ii u : Adj[v])
    {
        if (u.second != p[v])
        {
            p[u.second] = v;
            dfs1(u.second, path + u.first);
            wioska_count[v] += wioska_count[u.second];
        }
    }
    if (isWioska[v])
    {
        wioska_cost[0] += path;
        wioska_count[v]++;
    }
}

void dfs2(int v, ll upper_wioski)
{
    for (ii u : Adj[v])
    {
        if (u.second != p[v])
        {
            wioska_cost[u.second] = wioska_cost[v];
            wioska_cost[u.second] -= u.first * wioska_count[u.second];
            wioska_cost[u.second] += u.first * (wioska_count[v] - wioska_count[u.second] + upper_wioski);
            dfs2(u.second, upper_wioski + wioska_count[v] - wioska_count[u.second]);
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ll n, k;
    cin >> n >> k;
    Adj.resize(n);
    wioska_cost.assign(n, 0ll);
    wioska_count.assign(n, 0ll);
    p.assign(n, -1);
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
    stack<ll> q;
    for (int i = 0; i < k; i++)
    {
        int a;
        cin >> a;
        a--;
        isWioska[a] = true;
        q.push(a);
    }
    dfs1(0, 0ll);
    dfs2(0, 0ll);
    ll res = 0ll;
    for (int i = 0; i < n; i++)
    {
        if (isWioska[i])
            res += wioska_cost[i];
    }
    int cnt = k + 1;
    stack<ll> out;
    ll odejmnik = 0ll;
    while (!q.empty())
    {
        int v = q.top();
        q.pop();
        out.push(res);
        res -= 2 * wioska_cost[v];
        res += odejmnik;
        odejmnik += wioska_cost[v];
    }
    while (!out.empty())
    {
        cout << out.top() << '\n';
        out.pop();
    }
}