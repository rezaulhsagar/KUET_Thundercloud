///LCA on MST

const ll maxn = 100005;
const ll inf = 100000000000;
ll n, m, q;
vector <pair <ll, pair <ll, ll> > > edgelist;
vector <pair <ll, ll> > g[maxn];
ll parent[maxn];
ll sparse[maxn][18];
ll minsparse[maxn][18];
ll parentcost[maxn];
ll level[maxn];

ll findparent (ll a){
    if (parent[a] == a) return a;
    return parent[a] = findparent(parent[a]);
}

void makeset (ll a, ll b){
    ll pa = findparent(a);
    ll pb = findparent(b);
    parent[pa] = pb;
}

void dfs (ll u, ll par,ll d){
    level[u] = d;
    for (ll i = 0; i < g[u].size(); i++){
        ll k = g[u][i].first;
        if (k != par){

            parent[k] = u;
            parentcost[k] = g[u][i].second;
            dfs (k, u,d+1);
        }
    }
}

void build(){
    for(int i = 1; i <= n; i++){
        sparse[i][0] = parent[i];
        minsparse[i][0] = parentcost[i];
    }

    for(int j = 1; (1 << j) <=n; j++){
        for(int i = 1; i <=n; i++){
            if(sparse[i][j-1] != -1){
                minsparse[i][j] = min(minsparse[i][j-1],minsparse[sparse[i][j-1]][j-1]);
                sparse[i][j] = sparse[sparse[i][j-1]][j-1];
            }
        }
    }
}

ll  query(ll p, ll q){
    if(level[p] < level[q]){
        swap(p,q);
    }

    ll log = 1;
    ll ans = inf;
    while( (1 << log) <= level[p]) log++;log--;
    for(ll i = log; i >=0 ; i--){
        if(level[p] - (1LL << i) >= level[q]){
            ans = min(minsparse[p][i],ans);
            p = sparse[p][i];
        }
    }

    if(p == q) return ans;

    for(ll i = log; i >= 0; i--){
        if(sparse[p][i] != -1 && (sparse[p][i] != sparse[q][i])){
            ans = min(ans,minsparse[p][i]);
            ans = min(ans,minsparse[q][i]);
            p = sparse[p][i];
            q = sparse[q][i];
        }
    }

    return min(minsparse[p][0],min(minsparse[q][0],ans));

}
int main (){
//    filein;
    for(int i = 0; i < maxn; i++){
        for(int j = 0; j < 18; j++){
            minsparse[i][j] = inf;
            sparse[i][j] = -1;
        }
    }

    scanf("%lld %lld %lld", &n, &m, &q);
    for (ll i = 0; i < m; i++){
        ll u, v, c;
        scanf("%lld %lld %lld", &u, &v, &c);
        edgelist.push_back (make_pair (c, make_pair (u, v)));
    }
    sort (edgelist.rbegin(), edgelist.rend());
    for (ll i = 1; i <= maxn; i++)
        parent[i] = i;
    for (ll i = 0; i < edgelist.size(); i++){
        ll c = edgelist[i].first;
        ll u = edgelist[i].second.first;
        ll v = edgelist[i].second.second;
        ll pu = findparent(u);
        ll pv = findparent(v);
        if (pu != pv){
            g[u].push_back (make_pair (v, c));
            g[v].push_back (make_pair (u, c));
           //cout << u << " " << v  << " " << c << endl;
            makeset (pu, pv);
        }
    }

    parent[1] = -1;
    parentcost[1] = 0;
    dfs (1, 0,1);
    build();

    while(q--){
       ll a,b;
       scanf("%lld %lld",&a,&b);

       ll ans = query(a,b);

       printf("%lld\n",ans);
    }


    return 0;
}
