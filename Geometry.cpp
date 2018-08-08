#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXD = 2;
const double pi = acos (-1.0);
const double eps = 1e-8;

int dblcmp (double d){
    if (fabs (d) < eps) return 0;
    return d > eps ? 1 : -1;
}

struct Vector {
    int d;
    double val[MAXD];

    Vector (){d = 2;}


    Vector operator + (Vector b){
        Vector res;
        for (int i = 0; i < d; i++) res.val[i] = val[i] + b.val[i];
        return res;
    }

    Vector operator - (Vector b){
        Vector res;
        for (int i = 0; i < d; i++) res.val[i] = val[i] - b.val[i];
        return res;
    }

    Vector operator * (double t){
        Vector res;
        for (int i = 0; i < d; i++) res.val[i] = val[i] * t;
        return res;
    }

    Vector operator / (double t){
        Vector res;
        for (int i = 0; i < d; i++) res.val[i] = val[i] / t;
        return res;
    }

    bool operator == (Vector b){
        for (int i = 0; i < d; i++)
            if (!dblcmp (val[i] - b.val[i])) return false;
        return true;
    }

    double dot (Vector v){
        double res = 0;
        for (int i = 0; i < d; i++) res += (val[i] * v.val[i]);
        return res;
    }

    double dist (){
        return sqrt (dot (*this));
    }

};
