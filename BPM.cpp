ll n,m;
vector<ll> g[55];
ll lt[55];
ll rt[55];
bool visited[55];


bool dfs(ll u){
    if(visited[u]) return false;
    visited[u]=true;
    for(ll i=0;i<g[u].size();i++){
        ll v=g[u][i];
        if(rt[v]==-1){
            rt[v]=u;
            lt[u]=v;
            return true;
        }
    }
    for(ll i=0;i<g[u].size();i++){
        ll v=g[u][i];
        if(dfs(rt[v])){
            rt[v]=u;
            lt[u]=v;
            return true;
        }
    }
    return false;
}

ll match(){
    memset(lt,-1,sizeof lt);
    memset(rt,-1,sizeof rt);
    bool done=false;
    while(!done){
        done=true;
        memset(visited,false,sizeof visited);
        for(ll i=1;i<=n;i++){
            if(lt[i]==-1 and dfs(i)){
                done=false;
            }
        }
    }

    ll ret=0;
    for(ll i=1;i<=n;i++) ret+=(int)lt[i]!=-1;
    return ret;
}
