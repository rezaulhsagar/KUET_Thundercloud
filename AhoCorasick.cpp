//http://www.lightoj.com/volume_showproblem.php?problem=1427
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mx=100005;

//const int Node=250005;
const int Node=5000;

vector<ll> levelnd;

struct Trie
{
    int root,curNodeId;
    struct node
    {
        int val;
        int endcnt;
        int child[27];
        bool endmark;
        vector<int> endlist;
        void clear(){
            memset(child,0,sizeof child);
            val=endcnt=0;
            endlist.clear();
            endmark=false;
        }
    }trie[Node];

    void clear(){
        trie[root].clear();
        root=curNodeId=0;
    }

    void addTrie(string str,int id){
        int len=str.length();
        int cur=root;
        for(ll i=0;i<len;i++){
            int c = str[i]-'a';
            if(trie[cur].child[c]==0){
                curNodeId++;
                trie[curNodeId].clear();
                trie[curNodeId].val=c;
                trie[cur].child[c]=curNodeId;
            }
            cur=trie[cur].child[c];
        }
        trie[cur].endlist.push_back(id);
        trie[cur].endmark=true;
    }
    bool searchTrie (string str){
        int len=str.length();
        int cur=root;
        for (int i = 0; i < len; i++){
            int c = str[i] - 'a';
            if(trie[cur].child[c] == 0)return false;
            cur=trie[cur].child[c];
        }
        return trie[cur].endmark;
    }

};

struct  AhoCorasick
{
    Trie tr;
    int fail[Node];
    int par[Node];

    void clear(){
        tr.clear();
        memset(fail,0,sizeof fail);
        memset(par,0,sizeof par);
    }

    void Calculate_failure(){
        queue<int> q;
        q.push(tr.root);
        while(!q.empty()){
            ll u=q.front();q.pop();
            levelnd.push_back(u);
            for(ll i=0;i<26;i++){
                ll v=tr.trie[u].child[i];
                if(v!=0){
                    q.push(v);
                    par[v]=u;
                }
            }

            if(u==tr.root){
                fail[u]=0;
                par[u]=0;
                continue;
            }

            int p=par[u];
            int val=tr.trie[u].val;
            int f=fail[p];
            while(f!=0 and tr.trie[f].child[val]==0){
                f=fail[f];
            }
            fail[u]=tr.trie[f].child[val];
            if(u==fail[u])fail[u]=0;

        }
    }

    int GoTo(int nd,int c){
        if(tr.trie[nd].child[c]!=0){
            return tr.trie[nd].child[c];
        }

        int f=fail[nd];
        while(f!=0 and tr.trie[f].child[c]==0) f=fail[f];
        return tr.trie[f].child[c];
    }

    void findMatching(string str){
        int cur=tr.root;
        int len=str.length();
        for(ll i=0;i<len;i++){
            int c=str[i]-'a';
            cur=GoTo(cur,c);
            tr.trie[cur].endcnt++;
        }
    }


};
int n;
string T;
int ans[Node];

int main(){
    //freopen("input.txt","r",stdin);
    int t;
    scanf("%d",&t);
    AhoCorasick ahocorasick;
    for(int ts=1;ts<=t;ts++){
        printf("Case %d:\n",ts);
        scanf("%d",&n);
        ahocorasick.clear();
        levelnd.clear();
        memset(ans,0,sizeof ans);
        cin>>T;
        string temp;
        for(int i=1;i<=n;i++){
            cin>>temp;
            ahocorasick.tr.addTrie(temp,i);
        }
        ahocorasick.Calculate_failure();
        ahocorasick.findMatching(T);
        for(int i=(int)levelnd.size()-1;i>=0;i--){
            int u=levelnd[i];

            int f=ahocorasick.fail[u];
            ahocorasick.tr.trie[f].endcnt+=ahocorasick.tr.trie[u].endcnt;
            for(int j=0;j<(int)ahocorasick.tr.trie[u].endlist.size();j++){
                int qid=ahocorasick.tr.trie[u].endlist[j];
                ans[qid]+=ahocorasick.tr.trie[u].endcnt;
            }
        }
        for(int i=1;i<=n;i++){
            printf("%d\n",ans[i]);
        }
    }
    return 0;
}
