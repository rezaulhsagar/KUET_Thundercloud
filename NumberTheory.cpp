#include <bits/stdc++.h >
#define ll long long int
#define MAX 10000109
#define MOD 1000000007

using namespace std;

typedef pair < ll, ll > pii;
const double eps = 1e-9;
bool isPrime[MAX + 5];
ll DivisorSum[MAX + 5];
ll DivisorNo[MAX + 5];
ll modInverse[MAX + 5];
ll SmallestPrime[MAX + 5];
ll PrimeFactor[MAX + 5];
ll Phi[MAX + 5];
ll lp[MAX + 5];
vector <ll> pr, prime;

void seive_N_logN(ll N){
    ///calculate prime upto N in NlogN time
    memset(isPrime, true, sizeof isPrime);
    prime.clear();  isPrime[1] = false; isPrime[0] = false;
    for (ll i = 4; i <= N; i = i + 2)   isPrime[i] = false;

    for (ll i = 3; i * i <= N; i = i + 2)
        if (isPrime[i])
            for (ll j = i * i; j <= N; j += i)
                isPrime[j] = false;

    for (ll i = 1; i < N; i++)
        if (isPrime[i])
            prime.push_back(i);
}

int status[(MAX / 32) + 2];

bool Check(int N, int pos){     return (bool)(N & (1 << pos));  }

int Set(int N, int pos){    return N = N | (1 << pos);  }

void bit_sieve(ll N){
    int sqrtN, i, j;
    sqrtN = (sqrt(N));
    for (i = 3; i <= sqrtN; i += 2)
        if (Check(status[i >> 5], i & 31) == 0)
            for (j = i * i; j <= N; j += (i << 1))
                status[j >> 5] = Set(status[j >> 5], j & 31);
    prime.push_back(2);
    for (i = 3; i <= N; i += 2)
        if (Check(status[i >> 5], i & 31) == 0)
            prime.push_back(i);
}

ll SegmentedSieve(ll low, ll high){
    ///Segmented Seive Gives Number of Primes in a Range
    ll i, j, start, ans;
    ans = 0;
    i = 0;
    memset(isPrime, true, sizeof isPrime);
    if (low % 2 == 1) ///For Odd number
        i++;
    for (i; i <= high - low; i = i + 2) isPrime[i] = false;

    for (i = 3; i <= sqrt(high) + 1; i = i + 2) {
        start = max((ll) ceil(low / i), (ll) 1);
        if (start == 1) start++;
        start = start * i;
        if (start < low)    start += i;

        for (j = start - low; j <= high - low; j = j + i)
            isPrime[j] = false;
    }
    if (low == 1) {///If low==1 then 1 is not Prime but 2 is Prime
        isPrime[0] = false;
        isPrime[1] = true;
    }
    if (low == 2) /// If low==2 then 2 is Prime
        isPrime[0] = true;

    for (i = 0; i <= high - low; i++) {///Checking Prime
        if (isPrime[i])
            ans++;
    }
    return ans;
}

///primality test start

ll mulmod(ll a, ll b, ll mo){
    ll q = ((long double) a * (long double) b / (long double) mo);
    ll res = a * b - mo * q;
    return ((res % mo) + mo) % mo;
}


ll bigmod(ll a, ll b, ll c){
    ll res = 1;
    a = a % c;
    while (b > 0){
        if (b % 2 == 1)    res = mulmod(res, a, c);
        a = mulmod(a, a, c);
        b = b / 2;
    }
    return res;
}

bool miller(ll a, ll d, ll p){
    ll x = bigmod(a, d, p);
    if (x == 1 || x == p - 1)   return true;
    while (d != p - 1)  {
        x = mulmod(x, x, p);
        d *= 2;
        if (x == 1) return false;
        if (x == p - 1) return true;
    }
    return false;
}

bool isPrimes(ll p){
    if (p < 2)  return false;
    if (p == 2) return true;
    if (p != 2 && p % 2 == 0)   return false;
    ll d = p - 1;
    while (d % 2 == 0)  d = d / 2;
    for (ll i = 1; i < 20; i++){
        ll a = abs(rand() % (p - 2)) + 2;
        if (!miller(a, d, p))   return false;
    }
    return true;
}

///primality test end

ll SumOfDivisor_UpTo_N(ll N){
    ///calculate SumOfDivisor upto N in Sqrt(N) time
    ll i, j, ans;
    ans = 0;
    for (i = 1; i * i <= N; i++){
        j = N / i;
        /// (Summation Upto J) - (Summmation Upto I-1)
        ans += (((j * (j + 1)) / 2) - (((i - 1) * i) / 2));
        ///  Summation of all i that is not used in previous equation
        ans += ((j - i) * i);
    }
    return ans;
}

ll Sum_Of_No_Of_Divisor_upto_N(ll N){ ///up to n
    ll res = 0;
    ll u = sqrt(N);
    for (ll i = 1; i <= u; i++){
        res += (N / i) - i; //Step 1
    }
    res *= 2; //Step 2
    res += u; //Step 3
    return res;
}

void Phi_O_N(ll N){
    ///calculate coprime upto N in N time
    Phi[1] = 1;
    memset(lp, 0, sizeof lp);
    pr.clear();
    for (ll i = 2; i <= N; ++i){
        if (lp[i] == 0){
            lp[i] = i;
            Phi[i] = i - 1;
            pr.push_back(i);
        }
        else{
            ///Calculating phi
            if (lp[i] == lp[i / lp[i]])
                Phi[i] = Phi[i / lp[i]] * lp[i];
            else
                Phi[i] = Phi[i / lp[i]] * (lp[i] - 1);
        }
        for (ll j = 0; j < (ll) pr.size() && pr[j] <= lp[i] && i * pr[j] <= N; ++j)
            lp[i * pr[j]] = pr[j];
    }
}

void ModularInverse_O_N(ll N){
    ///Modular_Multiplicative_Inverse upto N in O(N)
    ///    a * (m / a) + m % a = m
    ///   (a * (m / a) + m % a) mod m = m mod m, or
    ///   (a * (m / a) + m % a) mod m = 0, or
    ///   (- (m % a)) mod m = (a * (m / a)) mod m.
    ///    Dividing both sides by (a * (m % a)), we get
    ///    � inverse(a) mod m = ((m/a) * inverse(m % a)) mod m
    ///    inverse(a) mod m = (- (m/a) * inverse(m % a)) mod m

    modInverse[1] = 1; /// this is you know 1 * 1 mod m = 1
    ll m = MOD;
    for (ll i = 2; i <= N; i++)
        modInverse[i] = (-(m / i) * modInverse[m % i]) % m + m;
}

void SmallestPrimeFactor(ll N){
    ///calculate SmallestPrime upto N in NlogN time
    memset(SmallestPrime, 0, sizeof SmallestPrime);
    for (ll i = 2; i < N; i += 2)
        SmallestPrime[i] = 2; ///even numbers have smallest prime factor 2
    for (ll i = 3; i < N; i += 2){
        if (!SmallestPrime[i]){
            SmallestPrime[i] = i;
            for (ll j = i;(j * i) < N; j += 2){ ///j++ produce even number
                if (!SmallestPrime[j * i])  SmallestPrime[j * i] = i;
            }
        }
    }
}

void NumberOfPrimeFactor(ll x){
    ///first call SmallestPrimeFactor
    ll y;
    y = x;
    memset(PrimeFactor, 0, sizeof PrimeFactor);
    while (x != 1){
        ll p = SmallestPrime[x];
        while (x % p == 0)  x /= p;
        PrimeFactor[y]++;
    }
}

ll gcd;

pii ExtendedEuclid(ll a, ll b){ /// returns x, y | ax + by = gcd(a,b)
    if (a == 0){
        gcd = b;
        return pii(1, 0);
    }
    else{
        pii d = ExtendedEuclid(b, a % b);
        return pii(d.second, d.first - d.second * (a / b));
    }
}

pii __ExtendedEuclid(ll a, ll b){
    ll x0 = 1, y0 = 0;
    ll x1 = 0, y1 = 1;
    while (b != 0){
        ll q = a / b;
        ll m = a - q * b;
        ll x = x0 - q * x1, y = y0 - q * y1;
        a = b;
        b = m;
        x0 = x1, y0 = y1;
        x1 = x, y1 = y;
    }
    return{
        x0,
        y0
    };
}

ll No_Of_Digits_In_N_Fact_In_Base_B(ll N, ll B){

    ///The number of digits in N factorial is :
    ///floor (ln(n!)/ln(B) + 1)

    ll i;
    double ans = 0;
    for (i = 1; i <= N; i++)
        ans += log(i);
    ans = ans / log(B);
    ans = ans + 1;
    return (ll) ans;

    ///*****Another Way
    ///    for(i=1; i<=N; i++)
    ///        ans+= (log10(i)/log10(B));
    ///    ans=ans+1;
    ///    return (ll)ans;
}

ll No_Of_Trailing_Zeroes_In_N_Fact_In_Base_B(ll N, ll B){
    ///We can break the Base B as a product of primes :
    /// B = a^p1 * b^p2 * c^p3 * ...
    ///Then the number of trailing zeroes in N factorial in Base B is given by the formulae
    ///min{1/p1(n/a + n/(a*a) + �.), 1/p2(n/b + n/(b*b) + ..), �.}.

    ll i, j, num, ans, total, m;
    ans = pow(10, 10);
    for (i = 0; prime[i] * prime[i] <= B; i++){
        m = prime[i];
        if (B % m == 0){
            num = 0;
            while (B % m == 0){
                B = B / m;
                num++;
            }
            j = 1;
            total = 0;
            while (floor(N / ceil(pow(m, j))) > 0){
                total += N / ceil(pow(m, j)); ///No. of total i in N!
                j++;
            }
            total = total / num;

            ans = min(ans, total);
        }
    }
    if (B > 1){ ///for last prime
        j = 1;
        total = 0;
        while (N / ceil(pow(B, j)) > 0){
            total += N / ceil(pow(B, j));
            j++;
        }
    }
    ans = min(ans, total);
    return ans;
}

ll leadingDigitFact(ll n, ll k){
    /// Find the first K digits of N!
    double fact = 0;
    for (ll i = 1; i <= n; i++){
        fact += log10(i); /// Find log(N!)
    }

    ///Find the floating part of log(N!) of fact
    double q = fact - floor(fact + eps);
    double B = pow(10, q);

    ///Shift decimal point k-1 times
    for (ll i = 0; i < k - 1; i++){
        B *= 10;
    }
    ///Don't forget to floor it
    return floor(B + eps);
}

ll ncr[1005][1005];

ll NCR(){
    for (ll i = 0; i < 1003; i++)
        ncr[i][0] = 1;
    for (ll i = 1; i < 1003; i++)
        for (ll j = 1; j < 1003; j++)
            ncr[i][j] = ncr[i - 1][j] + ncr[i - 1][j - 1];
            //ncr[i][j] %=mod;
}

//star and bars theorem
//divide n stars into k partitions, where
//each partition is positive
nCr (n - 1, k - 1);
//non negative
nCr (n + k - 1, k - 1);

//Mobius
const int N = 10000000;
vector <int> primes;
int mu[N + 7], sq = sqrt(N);
void mobius (){
    for (int i = 1; i <= N; i++){
        mu[i] = 1;
    }
    for (int i = 0; i < (int) primes.size() and primes[i] <= sq; i++){
        int x = primes[i] * primes[i];
        for (int j = x; j <= N; j += x){
            mu[j] = 0;
        }
    }
    for (int i = 0; i < (int) primes.size(); i++){
        for (int j = primes[i]; j <= N; j += primes[i]){
            mu[j] *= -1;
        }
    }
}


int main(){
    ll t, T, n, b;
    scanf("%lld", & T);
    seive_N_logN(1000 + 4);
    NCR();
    for (t = 1; t <= T; t++){
        scanf("%lld", & n);
        cout << isPrimes(n) << endl;
    }
    return 0;
}
