#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<ll, int> ii;

vector<vector<ii>> Adj;
vector<ll> ans;
vector<bool> isWioska;
vector<int> p;
//vector<bool> vis;

void dfs(int v, ll path)
{
    if (isWioska[v])
    {
        ans[v] = path;
    }
    for (ii u : Adj[v])
    {
        if (u.second != p[v])
        {
            p[u.second] = v;
            dfs(u.second, path + u.first);
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
    ans.assign(n, 0ll);
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
    dfs(0, 0ll);
    ll res = 0ll;
    int cnt = k + 1;
    stack<ll> out;
    for (int i = 0; i < n; i++) res += ans[i];
    while (!q.empty())
    {
        int v = q.top();
        q.pop();
        out.push(cnt * res);
        cnt--;
    }
    while (!out.empty())
    {
        cout << out.top() << '\n';
        out.pop();
    }
}