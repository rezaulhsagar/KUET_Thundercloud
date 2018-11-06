#include <bits/stdc++.h>
#define mx 30010
using namespace std;

typedef long long int ll;

ll genieCnt[mx];
vector <ll> adjList[mx];
ll sparseTable[mx][16];
ll parent[mx];
ll disc[mx],finish[mx];
ll levelNode[mx];
pair <ll,ll> start_finish[mx];
ll arr[2*mx];
ll tree[4*2*mx];
ll n;
ll _time;

void dfs(ll src,ll _p,ll ht){
	disc[src] = ++_time;
	arr[_time] = genieCnt[src];
	levelNode[src] = ht;

	for(ll i = 0; i < adjList[src].size(); i++){
		ll v = adjList[src][i];
		if(v != _p){
			parent[v] = src;
			dfs(v,src,ht+1);
		}
	}

	finish[src] = ++_time;
	arr[_time] = -genieCnt[src];
	start_finish[src] = make_pair(disc[src],finish[src]);
}

void build(ll node, ll left, ll right){
	if(left == right){
		tree[node] = arr[left];
		return;
	}

	ll mid = (left + right)/2;
	build(2*node,left,mid);
	build(2*node+1,mid+1,right);

	tree[node] = tree[2*node] + tree[2*node+1];
}

ll query(ll node, ll left, ll right, ll qleft, ll qright){
	if(qleft > right || qright < left)	return 0;

	if(left >= qleft && right <= qright)	return tree[node];

	ll mid = (left + right) / 2;

	ll a = query(2*node,left,mid,qleft,qright);
	ll b = query(2*node+1,mid+1,right,qleft,qright);

	return a + b;
}

ll printQuery(ll nodeA, ll nodeB){
	ll lca;
	ll node1 = nodeA,node2 = nodeB;

	if(levelNode[nodeB] < levelNode[nodeA])
		swap(nodeA,nodeB);


	for(ll i = 15; i >= 0; i--){
		if(levelNode[nodeB] - (1 << i) >= levelNode[nodeA]){
			nodeB = sparseTable[nodeB][i];
		}
	}

	if(nodeA == nodeB)	lca = nodeA;
	else{
	for(ll i = 15; i >=0; i--){
		if(sparseTable[nodeA][i] != sparseTable[nodeB][i]){
			nodeA = sparseTable[nodeA][i];
			nodeB = sparseTable[nodeB][i];
		}
	}

	lca = sparseTable[nodeA][0];
	}
	//cout << "lca: " << lca << endl;
	ll ans = query(1,1,2*n,start_finish[lca].first,start_finish[node1].first);
	ll ans2 = query(1,1,2*n,start_finish[lca].first,start_finish[node2].first);

	return ans + ans2 - query(1,1,2*n,start_finish[lca].first,start_finish[lca].first);
}

void update(ll node, ll left, ll right, ll idx, ll val){
	if(left == right){
		tree[node] = val;
		return;
	}

	ll mid = (left + right)/2;

	if(idx >= left && idx <= mid)
		update(2*node,left,mid,idx,val);
	else
		update(2*node+1,mid+1,right,idx,val);

	tree[node] = tree[2*node] + tree[2*node+1];
}


void reset(){
	for(ll i = 0; i < mx; i++){
		parent[i] = 0;
		genieCnt[i] = 0;
		adjList[i].clear();

		disc[i] = 0;
		finish[i] = 0;
		levelNode[i] = 0;
		start_finish[i] = make_pair(0,0);
		arr[i] = 0;
		
		for(ll j = 0; j < 16; j++)	
			sparseTable[i][j] = 0;
	}
	n = 0;
	_time = 0;
	memset(tree,0,sizeof tree);
}

int main(){
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	ll test;

	scanf("%lld",&test);

	for(ll i_t = 0; i_t < test; i_t++){
		reset();
		
		scanf("%lld",&n);

		for(ll i = 0; i < n; i++){
			scanf("%lld",genieCnt+i);
		}

		for(ll i = 0; i < n-1; i++){
			ll a,b;
			scanf("%lld %lld",&a,&b);
			adjList[a].push_back(b);
			adjList[b].push_back(a);
		}

		parent[0] = -1;
		dfs(0,-1,1);

		for(ll i = 0; i < n; i++)
			sparseTable[i][0] = parent[i];

		
		for(ll i = 1; i < 16; i++){
			for(ll j = 0; j < n; j++){
				ll par = sparseTable[j][i-1];
				if(par == -1){
					sparseTable[j][i] = -1;
				}
				else{
					sparseTable[j][i] = sparseTable[par][i-1];
				}
			}
		}

		build(1,1,2*n);

		ll q;

		scanf("%lld",&q);
		printf("Case %lld:\n",i_t+1);
		for(ll i = 0; i < q; i++){
			ll cmd,l,r;

			scanf("%lld %lld %lld",&cmd,&l,&r);
			if(cmd == 0){
				ll val = printQuery(l,r);
				printf("%lld\n",val);
			}
			else{
				//printf("(%lld,%lld)\n",start_finish[l].first,start_finish[l].second);
				update(1,1,2*n,start_finish[l].first,r);
				update(1,1,2*n,start_finish[l].second,-r);
			}
		}
	}
}
