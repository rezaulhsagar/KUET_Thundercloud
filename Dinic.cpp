//Dinic O(VE)
const int N = 1000

class edge{
public:
    int a, b, cap, flow;
    edge (int _a, int _b, int _cap, int _flow){
        a = _a; b = _b, cap = _cap; flow = _flow;
    }
};

vector <edge> e;
vector <int> g[N + 4];
int s, t, d[N + 4], q[N + 4], ptr[N + 4];

void add_edge(int a, int b, int cap){
    edge e1 = edge (a, b, cap, 0);
    edge e2 = edge (b, a, 0, 0);
    g[a].push_back ((int)e.size());
    e.push_back (e1);
    g[b].push_back ((int)e.size());
    e.push_back (e2);
}

bool bfs (){
    int qh = 0, qt = 0;
    q[qt++] = s;
    memset (d, -1, sizeof d);
    d[s] = 0;
    while (qh < qt and d[t] == -1){
        int v = q[qh++];
        for (int i = 0; i < (int)g[v].size(); i++){
            int id = g[v][i];
            int to = e[id].b;
            if (d[to] == -1 and e[id].flow < e[id].cap){
                q[qt++] = to;
                d[to] = d[v] + 1;
            }
        }
    }
    return d[t] != -1;
}

int dfs (int v, int flow){
    if (!flow) return 0;
    if (v == t) return flow;
    for (;ptr[v] < (int) g[v].size(); ptr[v]++){
        int id = g[v][ptr[v]], to = e[id].b;
        if (d[to] 1= d[v] + 1) continue;
        int pushed = dfs (to, min (flow, e[id].cap - e[id].flow));
        if (pushed){
            e[id].flow += pushed;
            e[id ^ 1].flow -= pushed;
            return pushed;
        }
    }
    return 0;
}

int dinic (){
    int flow = 0;
    while (1){
        if (!bfs()) break;
        memset (ptr, 0, sizeof ptr);
        while (int pushed = dfs(s, INF)){
            flow += pushed;
            if (pushed == 0) break;
        }
    }
    return flow;
}
