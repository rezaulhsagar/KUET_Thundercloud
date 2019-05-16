#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>

#define filein freopen ("in.txt", "r", stdin)
#define fileout freopen ("out.txt", "w", stdout)
#define dbg(x) cerr << #x << ": " << x << endl

using namespace std;
typedef long long ll;

const int maxn = 150;
const long double eps = 1e-4;

struct fr{
    ll a, b;
    fr(){}
    fr(ll x){
        a = x; b = 1;
    }
    fr (ll x, ll y){
        a = x; b = y;
    }
    fr operator - (){
        return fr (-a, b);
    }
    fr operator - (fr other){
        ll up = a * other.b - b * other.a;
        ll down = b * other.b;
        ll g = __gcd (up, down);
        return fr (up / g, down / g);
    }
    fr operator * (fr other){
        ll up = a * other.a;
        ll down = b * other.b;
        ll g = __gcd (up, down);
        return fr (up / g, down / g);
    }
    fr operator / (fr other){
        ll g = __gcd (a, other.a);
        a /= g; other.a /= g;
        g = __gcd (b, other.b);
        b /= g; other.b /= g;
        a *= other.a; b *= other.a;
        g = __gcd (a, b);
        return fr (a / g, b / g);
    }
    bool operator == (fr other){
        if (a < 0) a = -a, b = -b;
        if (other.a < 0) other.a = -other.a, other.b = -other.b;
        return (a == other.a and b == other.b);
    }
};
