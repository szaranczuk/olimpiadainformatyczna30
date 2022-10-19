#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<ll, int> ii;
typedef tuple<ll, int, int, int> liii;

int free_idx = 0;
vector<int> idx; //in-order flattened tree
vector<int> rev_idx; //reverse of idx
vector<bool> vis; //for dfs
vector<vector<ii>> Adj; //original adj list
vector<vector<ii>> blockAdj; //adj list between vertices in one block
vector<vector<liii>> treeAdj; //adj list between blocks
unordered_map<int, int> block_idx; //map blocks to {0, 1, 2, 3...}
vector<ll> dist; //distance from v to 0
vector<ll> subtree_size;
vector<unordered_map<int, ll>> block_sum; //block_sum[block][v] is sum of paths from v to every castle in block
vector<int> root; //this is in in-order, potentially bugged as fuck
vector<int> blocks; //unique roots
ll path = 0ll;

const ll B = 2;

void dfs1(int v)
{
    vis[v] = true;
    idx[v] = free_idx;
    dist[v] = path;
    rev_idx[free_idx] = v;
    free_idx++;
    for (unsigned i = 0; i < Adj[v].size(); i++)
    {
        if (!vis[Adj[v][i].second])
        {
            path += Adj[v][i].first;
            dfs1(Adj[v][i].second);
            path -= Adj[v][i].first;
            subtree_size[v] += 1 + subtree_size[Adj[v][i].second];
        }
    }
}

void initblockdfs(int v)
{
    vis[v] = true;
    for (unsigned i = 0; i < Adj[v].size(); i++)
    {
        if (!vis[Adj[v][i].second] && root[Adj[v][i].second] == root[v])
        {
            blockAdj[v].push_back(Adj[v][i]);
            initblockdfs(Adj[v][i].second);
        }
    }
}

void inittreedfs(int v, int block)
{
    vis[v] = true;
    for (unsigned i = 0; i < Adj[v].size(); i++)
    {
        if (!vis[Adj[v][i].second] && root[Adj[v][i].second] != root[v])
        {
            treeAdj[block].push_back({Adj[v][i].first, block_idx[root[Adj[v][i].second]], v, Adj[v][i].second});
            inittreedfs(Adj[v][i].second, block_idx[root[Adj[v][i].second]]);
        }
    }
}

void blockdfs(int v, int s, int block)
{
    vis[v] = true;
    block_sum[block][s] += path;
    for (unsigned i = 0; i < blockAdj[v].size(); i++)
    {
        if (!vis[blockAdj[v][i].second])
        {
            path += Adj[v][i].first;
            dfs1(Adj[v][i].second);
            path -= Adj[v][i].first;
            subtree_size[v] += 1 + subtree_size[Adj[v][i].second];
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
    vis.assign(n, false);
    subtree_size.assign(n, 0);
    idx.resize(n);
    rev_idx.resize(n);
    dist.assign(n, 0);
    blockAdj.resize(n);
    treeAdj.resize(n);
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
    dfs1(0);
    root.resize(n);
    blocks.reserve(n);
    int i = 0;
    while (i < n)
    {
        int cnt = 0;
        blocks.push_back(i);
        while (cnt <= min(subtree_size[rev_idx[i]], B))
        {
            root[i + cnt] = i;
            cnt++;
        }
        i += cnt;
    }
    for (int i = 0; i < blocks.size(); i++)
    {
        block_idx[blocks[i]] = i;
    }
    vis.clear();
    vis.assign(n, false);
    for (int i = 0; i < n; i++)
    {
        if (!vis[i])
        {
            initblockdfs(i);
        }
    }
    vis.clear();
    vis.assign(n, false);
    for (int i = 0; i < n; i++)
    {
        if (!vis[i])
        {
            inittreedfs(i, block_idx[root[i]]);
        }
    }
    return 0;
}