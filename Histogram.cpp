#include<bits/stdc++.h>
using namespace std;
typedef long long ll ;

ll ara[30005];
ll n;

ll histogram(){
  ll area=0;
  stack<int> st;
  ll i;
  for(i=0;i<n;i++){
    if(st.empty() || ara[st.top()]<=ara[i]) st.push(i);
    else{
    while(!st.empty() && ara[st.top()]>ara[i]){
      ll t=st.top();
      st.pop();
      ll tmarea=ara[t]*(st.empty() ? i: i-st.top()-1);
      area=max(area,tmarea);
    }
    st.push(i);
  }

  }
  while(!st.empty()){
    ll t=st.top();
    st.pop();
    ll tmarea=ara[t]*(st.empty()? i: i-st.top()-1);
    area=max(area,tmarea);
  }
  return area;
}

int main()
{
  //freopen("input.txt","r",stdin);
  ll t;
  scanf("%lld",&t);
  for(ll ts=1;ts<=t;ts++){

    scanf("%lld",&n);
    for(int i=0;i<n;i++) scanf("%lld",&ara[i]);
    printf("Case %lld: %lld\n",ts,histogram());
  }
}
