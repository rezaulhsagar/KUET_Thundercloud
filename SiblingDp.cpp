#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll mx=105;
const ll inf=1000000000000000000;
const ll mod=10000000007;

ll n,k;
ll dp[mx][mx];
vector<pair<ll,ll> > adj2[mx];
vector<pair<ll,ll> > adj[mx];

ll dfs(ll par,ll idx,ll remk){
    if(remk<0)return inf;
    if(adj[par].size()<idx+1)return 0;
    ll u=adj[par][idx].first;
    if(dp[u][remk]!=-1)return dp[u][remk];

    ll ret=inf;
    ll under=0,sibling=0;

    ///creating new group
    if(par!=0){
        under=1+dfs(u,0,k);
        sibling=dfs(par,idx+1,remk);
        ret=min(ret,under+sibling);
    }


    ///divide the current group
    ll temp=remk-adj[par][idx].second;
    for(ll childk=temp;childk>=0;childk--){
        ll siblingk=temp-childk;
        under=0;
        sibling=0;
        under=dfs(u,0,childk);
        sibling=dfs(par,idx+1,siblingk);
        ret=min(ret,under+sibling);
    }

    return dp[u][remk] = ret;

}


void make(ll u,ll par){
    for(ll i=0;i<(ll)adj2[u].size();i++){
        ll v=adj2[u][i].first;
        if(v==par)continue;
        adj[u].push_back(make_pair(adj2[u][i].first,adj2[u][i].second));
        make(v,u);
    }
}

inline void clean(){
    for(ll i=0;i<mx;i++){
        adj[i].clear();
        adj2[i].clear();
    }
    memset(dp,-1,sizeof dp);
}

int main(){
    //freopen("input.txt","r",stdin);

    ll t;
    scanf("%lld",&t);
    for(ll ts=1;ts<=t;ts++){
        clean();
        scanf("%lld %lld",&n,&k);
        ll u,v,c;
        for(ll i=0;i<n-1;i++){
            scanf("%lld %lld %lld",&u,&v,&c);
            adj2[u].push_back(make_pair(v,c));
            adj2[v].push_back(make_pair(u,c));
        }
        adj[0].push_back(make_pair(1,0));
        make(1,0);
        ll ans=1+dfs(0,0,k);

        printf("Case %lld: %lld\n",ts,ans);
    }
    return 0;
}

