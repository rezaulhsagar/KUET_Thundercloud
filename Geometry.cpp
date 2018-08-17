#include <bits/stdc++.h>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
#include <cassert>

using namespace std;
typedef long long ll;

const double pi = acos (-1.0);

typedef double T;
struct pt{
    T x, y;
    pt (){}
    pt (T _x, T _y){
        x = _x; y = _y;
    }
    pt operator + (pt p){
        return pt (x + p.x, y + p.y);
    }
    pt operator - (pt p){
        return pt (x - p.x, y - p.y);
    }
    pt operator * (T d){
        return pt (x * d, y * d);
    }
    pt operator / (T d){
        return pt (x / d, y / d);
    }
};

T sq (pt p){
    return p.x * p.x + p.y * p.y;
}

double abs (pt p){
    return sqrt (sq (p));
}

pt translate (pt v, pt p) {
    return p + v;
}

pt rot (pt p, double a){
    return pt (p.x * cos(a) - p.y * sin (a), p.x * sin (a) + p.y * cos (a));
}

pt perp (pt p){
    return pt (-p.y, p.x);
}

T dot (pt v, pt w){
    return v.x * w.x + v.y * w.y;
}

bool isPerp (pt v, pt w){
    return dot (v, w) == 0;
}

double smallAngle (pt v, pt w){
    double cosTheta = dot (v, w) / abs (v) / abs (w);
    if (cosTheta < -1) cosTheta = -1;
    if (cosTheta > 1) cosTheta = 1;
    return acos (cosTheta);
}

T cross (pt v, pt w){
    return v.x * w.y - v.y * w.x;
}

T orient (pt a, pt b, pt c){
    return cross (b - a, c - a);
}

bool inAngle (pt a, pt b, pt c, pt x){
    assert (orient (a, b, c) != 0);
    if (orient (a, b, c) < 0) swap (b, c);
    return orient (a, b, x) >= 0 and orient (a, c, x) <= 0;
}

bool isConvex (vector <pt>& p){
    bool hasPos = false, hasNeg = false;
    for (int i = 0, n = p.size(); i < n; i++){
        int o = orient (p[i], p[(i + 1) % n], p[(i + 2) % n]);
        if (o > 0) hasPos = true;
        if (o < 0) hasNeg = true;
    }
    return !(hasPos and hasNeg);
}

double areaTriangle (pt a, pt b, pt c){
    return abs (cross (b - a, c - a)) / 2.0;
}

double areaPolygon (vector <pt>& p){
    double area = 0.0;
    for (int i = 0, n = p.size(); i < n; i++){
        area += cross (p[i], p[(i + 1) % n]);
    }
    return abs (area) / 2.0;
}

struct line {
    pt v; T c;
    line (){}
    //From points P and Q
    line (pt p, pt q){
        v = (q - p); c = cross (v, p);
    }
    //From equation ax + by = c
    line (T a, T b, T c){
        v = pt (b, -a); c = c;
    }
    //From direction vector v and offset c
    line (pt v, T c){
        v = v; c = c;
    }

    //These work with T = int / double
    T side (pt p);
    double dist (pt p);
    double sqDist (pt p);
    line perpThrough (pt p);
    bool cmpProj (pt p, pt q);
    line translate (pt t);

    //These require T = double
    line shiftLeft (double dist);
    pt proj (pt p);
    pt sym (pt p);
};

T line :: side (pt p){
    return cross (v, p) - c;
}

double line :: dist (pt p){
    return abs (side (p)) / abs (v);
}

double line :: sqDist (pt p){
    return side (p) * side (p) / (double) sq (v);
}

line line :: perpThrough (pt p){
    return line (p, p + perp (v));
}

bool line :: cmpProj (pt p, pt q){
    return dot (v, p) < dot (v, q);
}

line line :: translate (pt t){
    return line (v, c + cross (v, t));
}

line line :: shiftLeft (double dist){
    return line (v, c + dist * abs (v));
}

bool inter (line l1, line l2, pt& out){
    T d = cross (l1.v, l2.v);
    if (d == 0) return false;
    out = (l2.v * l1.c - l1.v * l2.c) / d;
    return true;
}

pt circumCenter (pt a, pt b, pt c){
    b = b - a; c = c - a;
    assert (cross (b, c) != 0);
    return a + perp (b * sq (c) - c * sq (b)) / cross (b, c) / 2;
}

double circleCircleArea (Vector a, double r1, Vector b, double r2){  //sometimes long double may reduce precision loss
    double c = (a - b).dist();
    if (c >= (r1 + r2)) return 0.0; //fully outside
    if (c <= fabs (r1 - r2)){
        if (r2 < r1) return pi * r2 * r2;
        return pi * r1 * r1; //fully inside
    }
    //partially overlapped
    double ret = 0.0;
    double t1 = 2.0 * (acos ((r1 * r1 + c * c - r2 * r2) / (2.0 * r1 * c)));
    double t2 = 2.0 * (acos ((r2 * r2 + c * c - r1 * r1) / (2.0 * r2 * c)));
    ret += (0.5 * t1 * r1 * r1);
    ret += (0.5 * t2 * r2 * r2);
    ret -= (0.5 * r1 * r1 * sin (t1));
    ret -= (0.5 * r2 * r2 * sin (t2));
    return ret;
}
