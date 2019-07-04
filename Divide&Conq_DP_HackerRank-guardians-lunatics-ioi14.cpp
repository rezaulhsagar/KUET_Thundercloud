#include <bits/stdc++.h>
#define SEG_TREE int lnd = nd * 2, rnd = lnd + 1, mid = (b + e) / 2
#define filein freopen ("input.txt", "r", stdin)
#define fileout freopen ("output.txt", "w", stdout)
#define D(x) cerr << #x << ": " << x << endl

using namespace std;
typedef long long ll;

const int maxn = 0;


ll G, L;
ll dp[8001][801];
ll C[8001];
ll cum[8001];

inline ll cost(ll l, ll r){
    l--;
    return (cum[r] - cum[l]) * (r - l);
}

void func(ll g, ll st, ll ed, ll r1, ll r2){

    if(st > ed) return;

    ll mid = (st + ed) / 2;
    dp[mid][g] = 1000000000000000000;
    ll pos = -1;

    for(int i = r1; i <= r2; i++){
        ll tcost = cost(i, mid) + dp[i - 1][g - 1];
        if(tcost < dp[mid][g]){
            dp[mid][g] = tcost;
            pos = i;
        }
    }

    func(g, st, mid - 1, r1, pos);
    func(g, mid + 1, ed, pos, r2);
}


int main(){
//    filein;
    scanf("%lld %lld", &L, &G);

    G = min(G, L);

    for(int i = 1; i <= L; i++) scanf("%lld", C + i);
    for(int i = 1; i <= L; i++) cum[i] = cum[i - 1] + C[i];

    for(int i = 1; i <= L; i++) dp[i][1] = cost(1, i);
    for(int i = 2; i <= G; i++){
        func(i, 1, L, 1, L);
    }

    printf("%lld\n", dp[L][G]);

    return 0;
}
