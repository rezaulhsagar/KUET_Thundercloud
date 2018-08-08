//http://codeforces.com/problemset/problem/817/E

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mx=100005;

struct Trie{
	ll ptr=0;
	struct node
	{
		ll cnt;
		ll z;
		ll o;
		node(){
			cnt=0;
			z=-1;
			o=-1;
		}
	}trie[100005*33];

	ll root=++ptr;
	bool check(ll N,ll pos){return (bool)(N&(1LL<<pos));}

	void insrt(ll x){
		ll crnt=root;
		for(ll i=30;i>=0;i--){
			ll bit=(ll)check(x,i);
			trie[crnt].cnt++;
			if(bit==1){
				if(trie[crnt].o==-1){
					trie[crnt].o=++ptr;
				}
				crnt=trie[crnt].o;
			}
			else{
				if(trie[crnt].z==-1){
					trie[crnt].z=++ptr;
				}
				crnt=trie[crnt].z;
			}
		}
		trie[crnt].cnt++;
	}
	void dlte(ll x){
		ll crnt=root;
		for(ll i=30;i>=0;i--){
			ll bit=(ll)check(x,i);
			trie[crnt].cnt--;
			if(bit==1){
				crnt=trie[crnt].o;
			}
			else{
				crnt=trie[crnt].z;
			}
		}
		trie[crnt].cnt--;
	}

	ll query(ll p,ll l){
		ll ret=0;
		ll crnt=root;
		for(ll i=30;i>=0;i--){
            if(crnt==-1)break;
			ll pbit=(ll)check(p,i);
			ll lbit=(ll)check(l,i);
			if(lbit==0){
				if(pbit==0){
					crnt=trie[crnt].z;
				}
				else{
					crnt=trie[crnt].o;
				}
			}
			else{
				if(pbit==0){
					if(trie[crnt].z!=-1)ret+=trie[trie[crnt].z].cnt;
                    crnt=trie[crnt].o;

				}
				else{
					if(trie[crnt].o!=-1)ret+=trie[trie[crnt].o].cnt;
					crnt=trie[crnt].z;
				}
			}
		}
		return ret;
	}


};



int main(){
    //freopen("input.txt","r",stdin);
	ll q;
	scanf("%lld",&q);
	Trie tr=Trie();
	while(q--){
		ll k;
		scanf("%lld",&k);
		if(k==1){
			ll x;
			scanf("%lld",&x);
			tr.insrt(x);
		}
		else if(k==2){
			ll x;
			scanf("%lld",&x);
			tr.dlte(x);
		}
		else{
			ll p,l;
			scanf("%lld %lld",&p,&l);
			ll ans=tr.query(p,l);
			printf("%lld\n",ans);
		}
	}
}
