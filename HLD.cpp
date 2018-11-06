///node count: 0 to n - 1
#include<bits/stdc++.h>
using namespace std;

const int maxn = 500050;

int n, ptr, chainno;
vector <int> adj[maxn];
int level[maxn];
int sparse[maxn][20];
int subsize[maxn];
int chainid[maxn];
int chainhead[maxn];
int base[maxn];
int posbase[maxn];
int tree[maxn*6];
int lazy[maxn*6];

void clean(){
    for(int i = 0; i < maxn; i++){
        adj[i].clear();
        chainid[i] = -1;
        chainhead[i] = -1;
        base[i] = 0;
        level[i] = -1;
        posbase[i] = -1;
        subsize[i] = 0;
    }
    memset(sparse, -1, sizeof sparse);
    memset(tree, 0, sizeof tree);
    ptr = 1;
    chainno = 1;
}

void dfs(int u, int p, int depth){
    sparse[u][0] = p;
    level[u] = depth;
    subsize[u] = 1;
    for(int i = 0; i < adj[u].size(); i++){
        int v = adj[u][i];
        if(v == p) continue;
        dfs(v, u, depth + 1);
        subsize[u] += subsize[v];
    }
}

void lca_init(){
    for(int j = 1; (1<<j) < n; j++){
        for(int i = 0; i < n; i++){
            if(sparse[i][j - 1] != -1) sparse[i][j] = sparse[sparse[i][j-1]][j-1];
        }
    }
}

int query_lca(int p, int q){
    if(level[p] < level[q]) swap(p,q);
    int log = 0;
    while((1<<log) <= level[p]) log++;
    log--;
    for(int i = log; i >= 0; i--){
        if(level[p] - (1<<i) >= level[q]){
            p = sparse[p][i];
        }
    }
    if(p == q) return p;
    for(int i = log; i >= 0; i--){
        if(sparse[p][i] != -1 and sparse[p][i] != sparse[q][i]){
            p = sparse[p][i];
            q = sparse[q][i];
        }
    }
    return sparse[p][0];
}


void hld(int cur, int p, int cst){
    if(chainhead[chainno] == -1)
        chainhead[chainno] = cur;
    chainid[cur] = chainno;
    posbase[cur] = ptr;
    base[ptr++] = cst;

    int sc = -1;
    int mx = -10000000000;

    for(int i = 0; i < adj[cur].size(); i++){
        int v = adj[cur][i];
        if(v == p) continue;
        if(sc == -1 or subsize[sc] < subsize[v]){
            sc = v;
            mx = 0;/// here goes cost,for this problem it is 0. i.e. cost[cur][i];
        }
    }

    if(sc != -1) hld(sc, cur, mx);

    for(int i = 0; i < adj[cur].size(); i++){
        int v = adj[cur][i];
        if(v == p or v == sc) continue;
        chainno++;
        int cst = 0; /// same
        hld(v, cur, cst);
    }
}


void build(int nd, int b, int e){
    if(b == e){
        tree[nd] = base[b];
        lazy[nd] = 0;
        return;
    }
    int lnd = nd * 2;
    int rnd = lnd + 1;
    int mid = (b + e) / 2;
    build(lnd, b, mid);
    build(rnd, mid + 1, e);
    tree[nd] = 0;
    lazy[nd] = 0;
}

inline void push_down(int nd, int b, int e){
    tree[nd] += (e - b + 1) * lazy[nd];
    if(b != e){
        lazy[nd*2] += lazy[nd];
        lazy[nd*2 + 1] += lazy[nd];
    }
    lazy[nd] = 0;
}

int query_tree(int nd, int b, int e, int i, int j){
    if(lazy[nd] != 0) push_down(nd, b, e);
    if(i > e or j < b) return 0;
    if(i <= b and e <= j) return tree[nd];
    int lnd = nd * 2;
    int rnd = lnd + 1;
    int mid = (b + e) / 2;
    int ret1 = query_tree(lnd, b, mid, i, j);
    int ret2 = query_tree(rnd, mid + 1, e, i, j);
    return ret1 + ret2;
}

int query_up(int u, int v){
    int vchain = chainid[v];
    int uchain;
    int ret = 0;
    while(1){
        uchain = chainid[u];
        if(uchain == vchain){
            ///if (v == u) break;
            ret += query_tree(1, 1, ptr, posbase[v], posbase[u]);
            break;
        }
        ret += query_tree(1, 1, ptr, posbase[chainhead[uchain]], posbase[u]);
        u = chainhead[uchain];
        u = sparse[u][0];
    }
    return ret;
}

int query(int u,int v){
    int lca = query_lca(u,v);
    int ret1 = query_up(u,lca);
    int ret2 = query_up(v,lca);
    int ret3 = query_up(lca,lca);
    return ret1 + ret2 - ret3;
}

void update_tree(int nd, int b, int e, int i, int j, int c){
    if(lazy[nd] != 0) push_down(nd, b, e);
    if(i > e or j < b) return;
    if(i <= b and e <= j){
        lazy[nd] +=c;
        push_down(nd, b, e);
        return ;
    }
    int lnd = nd * 2;
    int rnd = lnd + 1;
    int mid = (b + e) / 2;
    update_tree(lnd, b, mid, i, j, c);
    update_tree(rnd, mid + 1, e, i, j, c);
}

void update_up(int u, int v, int c){
    int vchain = chainid[v];
    int uchain;
    while(1){
        uchain = chainid[u];
        if(uchain == vchain){
            ///if (u == v) break;
            update_tree(1, 1, ptr, posbase[v], posbase[u], c);
            break;
        }
        update_tree(1, 1, ptr, posbase[chainhead[uchain]], posbase[u], c);
        u = chainhead[uchain];
        u = sparse[u][0];
    }
}
void update(int u, int v, int c){
    int lca = query_lca(u, v);
    update_up(v, lca, c);
    update_up(u, lca, c);
    update_up(lca, lca, -c);
}

int main(){
//    freopen("input.txt","r",stdin);

    int t, u, v, c;
    scanf("%d", &t);
    for(int ts = 1; ts <= t; ts++){
        clean();
        scanf("%d", &n);
        for(int i = 0; i < n-1; i++){
            scanf("%d %d", &u, &v);
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        dfs(0,-1,1);
        lca_init();
        hld(0,-1,0);
        build(1, 1, ptr);
        int q;
        scanf("%d", &q);
        while(q--){
            scanf("%d %d %d", &u, &v, &c);
            update(u, v, c);
        }
        printf("Case #%d:\n",ts);
        for(int i = 0; i < n; i++){
            printf("%d\n",query(i,i));
        }
    }
}
