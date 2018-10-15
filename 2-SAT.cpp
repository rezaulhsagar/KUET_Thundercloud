#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 21000;

struct SCC {
    vector <int> g[maxn];
    int disc[maxn], low[maxn], st[maxn], cycle[maxn], id[maxn];
    int visited[maxn];
    int tail, t, cnt;

    SCC (){
        t = tail = cnt = 0;
        memset (visited, 0, sizeof visited);
    }

    void tarjan (int u){
        disc[u] = low[u] = t++;
        st[tail++] = u;
        visited[u] = 1;
        for (int i = 0; i < (int) g[u].size(); i++){
            int v = g[u][i];
            if (visited[v] == 0){
                tarjan (v);
                low[u] = min (low[u], low[v]);
            }
            else if (visited[v] == 1){
                low[u] = min (low[u], low[v]);
            }
        }
        if (low[u] == disc[u]){
            cnt++;
            while (1){
                int v = st[tail - 1];
                tail--;
                visited[v] = 2;
                cycle[v] = u;
                id[v] = cnt;
                if (u == v) break;
            }
            id[u] = cnt;
        }
    }

    void findSCC (int n){
        for (int i = 1; i <= n; i++){
            if (visited[i] == 0)
                tarjan (i);
        }
    }
};

struct TwoSat{
    int n;
    SCC scc;
    vector <int> res;
    inline int Not (int a){
        if (a > n) return a - n;
        return n + a;
    }

    void mustTrue (int a){
        scc.g[Not (a)].push_back (a);
    }

    void xorClause (int a, int b){
        scc.g[a].push_back (Not (b));
        scc.g[Not (a)].push_back (b);
        scc.g[b].push_back (Not (a));
        scc.g[Not (b)].push_back (a);
    }

    void orClause (int a, int b){
        scc.g[Not (a)].push_back (b);
        scc.g[Not (b)].push_back (a);
    }

    void andClause (int a, int b){
        mustTrue (a);
        mustTrue (b);
    }

    bool possible (){
        scc.findSCC (n + n);
        for (int i = 1; i <= n; i++){
            if (scc.cycle[i] == scc.cycle[Not (i)])
                return false;
        }
        return true;
    }

    void findSAT (){
        for (int i = 1; i <= n; i++){
            if (scc.id[i] < scc.id[Not (i)]){
                res.push_back (i);
            }
        }
    }
};
