#include <bits/stdc++.h>

#define INF 1000000
#define MOD 1000000007
#define pause system("pause")
#define clock 1.0 * clock() / CLOCKS_PER_SEC
#define filein freopen ("in.txt", "r", stdin)
#define fileout freopen ("out.txt", "w", stdout)

void setBit(int& N, int p){N|=(1<<p);}
void resetBit(int& N, int p){N&=~(1<<p);}
bool checkBit(int& N, int p){return N&(1<<p);}

template<class T>
inline void input(T &x) {
    register char c = getchar();x = 0;
    int neg = 0;
    for(; ((c<48 || c>57) && c != '-'); c = getchar());
    if(c=='-'){neg = 1;c = getchar();}
    for(; c>47 && c<58 ; c = getchar()){x = (x<<1) + (x<<3) + c - 48;}
    if(neg) x = -x;
}

//more faster
template <class T>
inline bool input (T &ret){
    char c; int sgn;
    if (c = getchar(), c == EOF) return 0;
    while (c != '-' && (c < '0' || c > '9')) c = getchar();
    sgn = (c == '-') ? -1 : 1, ret = (c == '-') ? 0 : (c - '0');
    while (c = getchar(), c >= '0' && c <= '9') ret = ret * 10 + (c - '0');
    ret *= sgn;
    return 1;
}

const int dr[]={0,-1,0,1,-1,-1,1,1};
const int dc[]={1,0,-1,0,1,-1,-1,1};
