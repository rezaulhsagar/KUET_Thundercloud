#include <bits/stdc++.h>
using namespace std;

typedef long long int lli;

#define FILE_IN freopen("in.txt","r",stdin);
#define FILE_OUT freopen("out.txt","w",stdout);
#define FILE_IO FILE_IN;FILE_OUT;
#define FAST_IO ios::sync_with_stdio(false);cin.tie(NULL);

vector <lli> adj_list[100000 + 10];
vector <lli> adj_list_reversed[100000 + 10];
lli cost[100000 + 10];
bool visited1[100000 + 10];
bool visited2[100000 + 10];
lli begin_time[100000 + 10];
lli finish_time[100000 + 10];
vector <lli> scc[100000 + 10];

#define MOD 1000000007
vector <pair <lli,lli> > v;

lli t;


void dfs1(lli src){
   if(visited1[src])
      return;

   begin_time[src] = ++t;
   visited1[src] = true;
   for(lli i = 0; i < adj_list[src].size(); i++)
      dfs1(adj_list[src][i]);

   finish_time[src] = ++t;
}

void dfs2(lli src,lli p){
   if(visited2[src])
      return;

   visited2[src] = true;
   scc[p].push_back(src);

   for(lli i = 0; i < adj_list_reversed[src].size(); i++){
      dfs2(adj_list_reversed[src][i],p);
   }
}

int main(){
   lli n,a,b,m;
   scanf("%lld",&n);

   for(lli i_n = 1; i_n <= n; i_n++){
      scanf("%lld",&cost[i_n]);
   }

   scanf("%lld",&m);

   for(lli i_m = 0; i_m < m; i_m++){
      scanf("%lld %lld",&a,&b);

      adj_list[a].push_back(b);
      adj_list_reversed[b].push_back(a);

   }

   for(lli i_n = 1; i_n <= n; i_n++){
      if(visited1[i_n] == false)
         dfs1(i_n);
   }

   for(lli i_n = 1; i_n <= n; i_n++){
      v.push_back(make_pair(finish_time[i_n],i_n));
   }

   sort(v.begin(),v.end());

   lli number = 1;

   for(lli i_n = v.size() - 1; i_n >= 0; i_n--){
      if(visited2[v[i_n].second] == false){
         dfs2(v[i_n].second,number++);
      }
   }
}
