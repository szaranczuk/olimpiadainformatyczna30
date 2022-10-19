#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<ll, int> ii;
typedef tuple<int, int, int> iii;

ll n, k;
ll ans;
int free_idx = 0;
int block_count = 0;
vector<int> idx;             //in-order flattened tree
vector<int> rev_idx;         //reverse of idx
vector<int> vis;             //for dfs
vector<ii> p;                //for dfs
vector<vector<ii>> Adj;      //original adj list
vector<vector<ii>> blockAdj; //adj list between vertices in one block
vector<vector<iii>> treeAdj; //adj list between blocks, values are [weight, block_to, vertex_from, vertex_to]
vector<int> blockid;         //blockid[v] - id of block which contains v
vector<ii> root_of_block;    //see solution description
vector<ll> subtree_size;
vector<unordered_map<int, ll>> dist;      //dist[v][u] - distance from v to u if v and u are in the same group, undefined otherwise
vector<unordered_map<int, ll>> block_sum; //block_sum[block][v] is sum of paths from v to every castle in block
vector<bool> isWioska;                    //isWioska[v] true if there is a castle in v
vector<int> wioska_count;                 //number of castles in group
vector<int> vertices_without_group;       //used to group vertices
vector<vector<int>> blocks;               //vertices in one block
ll path = 0ll;

const ll B = 2;

void dfs1(int v)
{
    vis[v] = true;
    idx[v] = free_idx;
    //dist[v] = path;
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
    for (ii u_p : Adj[v])
    {
        int u = u_p.second;
        if (!vis[u] && blockid[u] == blockid[v])
        {
            blockAdj[v].push_back(u_p);
            blockAdj[u].push_back({u_p.first, v});
            initblockdfs(u);
        }
        else if (u == root_of_block[blockid[v]].second)
        {
            blockAdj[v].push_back({u_p.first, n + blockid[v]});
            blockAdj[n + blockid[v]].push_back({u_p.first, v});
        }
    }
}

/*void inittreedfs(int v)
{
    vis[v] = true;
    for (ii u_p : Adj[v])
    {
        int u = u_p.second;
        if (!vis[u] && blockid[u] != blockid[v])
        {
            ll w;
            if (u == root_of_block[v].second)
            {
                w = 0ll;
            }
            else
            {
                w = u_p.first;
            }
            treeAdj[blockid[v]].push_back({w, blockid[u], v, u});
            treeAdj[blockid[u]].push_back({w, blockid[v], u, v});
            inittreedfs(u);
        }
    }
}*/

void blockdfs(int v, int s, int dupa)
{
    if (v == s)
    {
        block_sum[blockid[s]][s] = 0;
    }
    dist[s][v] = path;
    vis[v] = dupa;
    if (isWioska[v])
    {
        block_sum[blockid[s]][s] += path;
    }
    for (ii u_p : blockAdj[v])
    {
        int u = u_p.second;
        if (vis[u] != dupa)
        {
            path += u_p.first;
            blockdfs(u, s, dupa);
            path -= u_p.first;
        }
    }
}

void treedfs(int v)
{
    vis[v] = true;
    for (auto u_p : treeAdj[v])
    {
        if (!vis[get<0>(u_p)])
        {
            int from = get<1>(u_p);
            int to = get<2>(u_p);
            path += block_sum[blockid[from]][from];
            ans += 2 * (wioska_count[blockid[to]] * path + block_sum[blockid[to]][to]);
            treedfs(blockid[to]);
            path -= block_sum[blockid[from]][from];
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    //input reading
    cin >> n >> k;
    Adj.resize(n);
    vis.assign(n, false);
    p.assign(n, {-1, -1});
    subtree_size.assign(n, 0);
    idx.resize(n);
    rev_idx.resize(n);
    dist.resize(2*n);
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

    //Iterative dfs to group vertices up. Recursive dfs leads to stack overflow on 1MB stack
    stack<ii> dfs;
    dfs.push({0ll, 0});
    root_of_block.resize(n);
    blockid.resize(2*n);
    while (!dfs.empty())
    {
        ii v = dfs.top();
        if (vis[v.second])
        {
            vertices_without_group.push_back(v.second);
            ii par = p[v.second];
            if (par.second != -1 && vertices_without_group.size() >= B)
            {
                root_of_block[block_count] = par;
                for (int u : vertices_without_group)
                {
                    blockid[u] = block_count;
                }
                block_count++;
                vertices_without_group.clear();
            }
            path -= v.first;
            for (ii u : Adj[v.second])
            {
                if (u.second != p[v.second].second)
                    subtree_size[idx[v.second]] += subtree_size[idx[u.second]] + 1;
            }
            dfs.pop();
            continue;
        }
        path += v.first;
        //dist[v.second] = path;
        vis[v.second] = true;
        idx[v.second] = free_idx;
        free_idx++;
        for (ii u : Adj[v.second])
        {
            if (!vis[u.second])
            {
                p[u.second] = v;
                dfs.push(u);
            }
        }
    }
    for (int u : vertices_without_group)
    {
        blockid[u] = block_count;
    }
    for (int i = 0; i < root_of_block.size(); i++)
    {
        ii root = root_of_block[i];
        treeAdj[i].push_back({blockid[root.second], n + i, root.second});
        treeAdj[blockid[root.second]].push_back({i, root.second, n + i});
    }
    for (int i = 0; i <= block_count; i++) blockid[n + i] = i;
    blockAdj.resize(n + block_count + 1);
    vis.clear();
    vis.assign(n, false);
    for (int i = 0; i < n; i++)
    {
        if (!vis[i])
        {
            initblockdfs(i);
        }
    }
    blocks.resize(block_count + 1);
    for (int i = 0; i <= n + block_count; i++)
    {
        blocks[blockid[i]].push_back(i);
    }
    wioska_count.assign(block_count + 1, 0);
    wioska_count[blockid[0]]++;
    isWioska.assign(n, false);
    isWioska[0] = true;
    vis.clear();
    vis.assign(2 * n, -1);
    block_sum.resize(n);
    for (int i = 0; i < n; i++)
    {
        blockdfs(i, i, i);
    }
    vis.clear();
    vis.assign(2 * n, -1);
    while (k--)
    {
        int a;
        cin >> a;
        a--;
        isWioska[a] = true;
        wioska_count[blockid[a]]++;
        for (int v : blocks[blockid[a]])
        {
            for (int v : blocks[blockid[a]]) vis[v] = -1;
            blockdfs(v, v, a);
        }
        ans = 2*block_sum[blockid[a]][a];
        for (int i = 0; i <= block_count; i++)
            vis[i] = false;
        treedfs(blockid[a]);
        cout << ans << '\n';
    }
    return 0;
}