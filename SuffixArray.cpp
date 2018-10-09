#include <bits/stdc++.h>
using namespace std;

const int maxn = 100005;
char T[maxn];
int n;
int ra[maxn], tra[maxn];
int sa[maxn], tsa[maxn];
int c[maxn], phi[maxn];
int lcp[maxn], plcp[maxn];

void reset (){
    for (int i = 0; i < maxn; i++){
        ra[i] = tra[i] = sa[i] = tsa[i] = c[i] = phi[i] = lcp[i] = plcp[i] = 0;
    }
}

void countingSort (int k){
    int i, sum, maxi = max (300, n);
    memset (c, 0, sizeof c);
    for (i = 0; i < n; i++)
        c[i + k < n ? ra[i + k] : 0]++;
    for (i = sum = 0; i < maxi; i++){
        int t = c[i]; c[i] = sum; sum += t;
    }
    for (i = 0; i < n; i++)
        tsa[c[sa[i] + k < n ? ra[sa[i] + k] : 0]++] = sa[i];
    for (i = 0; i < n; i++)
        sa[i] = tsa[i];
}

void buildSA (){
    int i, k, r;
    for (i = 0; i < n; i++) ra[i] = T[i];
    for (i = 0; i < n; i++) sa[i] = i;
    for (k = 1; k < n; k <<= 1){
        countingSort(k);
        countingSort(0);
        tra[sa[0]] = r = 0;
        for (i = 1; i < n; i++){
            tra[sa[i]] = (ra[sa[i]] == ra[sa[i - 1]] and ra[sa[i] + k] == ra[sa[i - 1] + k]) ? r : ++r;
        }
        for (i = 0; i < n; i++)
            ra[i] = tra[i];
        if (ra[sa[n - 1]] == n - 1) break;
    }
}

void buildLCP (){
    int i, L;
    phi[sa[0]] = -1;
    for (i = 1; i < n; i++)
        phi[sa[i]] = sa[i - 1];
    for (i = L = 0; i < n; i++){
        if (phi[i] == -1){
            plcp[i] = 0;
            continue;
        }
        while (T[i + L] == T[phi[i] + L])
            L++;
        plcp[i] = L;
        L = max (L - 1, 0);
    }
    for (i = 0; i < n; i++)
        lcp[i] = plcp[sa[i]];
}
