const int maxn = 100005;
const int V = 100000;
int dfsRoot, rootChildren;
vector <int> dfs_num,dfs_low,dfs_parent,articulation_vertex;
int dfsNumberCounter;
vector <pair <int, int> > AdjList[maxn];

void articulationPointAndBridge(int u)
{
    dfs_low[u] = dfs_num[u] = dfsNumberCounter++; // dfs_low[u] <= dfs_num[u]
    for (int j = 0; j < (int)AdjList[u].size(); j++)
    {
        pair <int, int> v = AdjList[u][j];
        if (dfs_num[v.first] == false)   // a tree edge
        {
            dfs_parent[v.first] = u;
            if (u == dfsRoot)
                rootChildren++; // special case if u is a root
            articulationPointAndBridge(v.first);
            if (dfs_low[v.first] >= dfs_num[u]) // for articulation point
                articulation_vertex[u] = true; // store this information first
            if (dfs_low[v.first] > dfs_num[u]) // for bridge
                printf(" Edge (%d, %d) is a bridge\n", u, v.first);
            dfs_low[u] = min(dfs_low[u], dfs_low[v.first]); // update dfs_low[u]
        }
        else if (v.first != dfs_parent[u]) // a back edge and not direct cycle
            dfs_low[u] = min(dfs_low[u], dfs_num[v.first]); // update dfs_low[u]
    }
}
