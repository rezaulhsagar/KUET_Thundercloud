#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
const int mx=100005;
const int mod=1000000007;

int n,k;

int ara[205];
int dp[205][205][1005];

int func(int idx,int g,int tk){
    if(g<0) return 0;
    if(tk<0)return 0;
    if(idx==n+1){
        if(tk>=0 and g==0)return 1;
        else return 0;
    }
    if(dp[idx][g][tk]!=-1)return dp[idx][g][tk];
    ll ret=0;
    ///open a group
    ret+=func(idx+1,g+1,tk-g*(ara[idx]-ara[idx-1]));
    ret%=mod;
    ///close a group
    ret+=(((ll)g*(ll)func(idx+1,g-1,tk-g*(ara[idx]-ara[idx-1])))%mod);
    ret%=mod;
    ///enter a current group
    ret+=(((ll)g*(ll)func(idx+1,g,tk-g*(ara[idx]-ara[idx-1])))%mod);
    ret%=mod;
    ///open a group and close
    ret+=func(idx+1,g,tk-g*(ara[idx]-ara[idx-1]));
    ret%=mod;

    return dp[idx][g][tk]=(int)ret;
}

int main(){
    //freopen("input.txt","r",stdin);
    memset(dp,-1,sizeof dp);
    scanf("%d %d",&n,&k);
    for(int i=1;i<=n;i++){
        scanf("%d",&ara[i]);
    }
    sort(ara+1,ara+n+1);
    ara[0]=ara[1];
    int ans=func(1,0,k);
    printf("%d\n",ans);
    return 0;
}
