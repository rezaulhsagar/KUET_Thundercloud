const double pi = acos (-1.0);
const double eps = 1e-8;

int dblcmp (double d){
    if (fabs (d) < eps) return 0;
    return d > eps ? 1 : -1;
}

struct Vector {
    double x, y;

    Vector (){}
    Vector (double a, double b){
        x = a; y = b;
    }

    Vector operator + (Vector a){
        return Vector (x + a.x, y + a.y);
    }

    Vector operator - (Vector a){
        return Vector (x - a.x, y - a.y);
    }

    Vector operator * (double t){
        return Vector (x * t, y * t);
    }

    Vector operator / (double t){
        return Vector (x / t, y / t);
    }

    bool operator == (Vector a){
        return (dblcmp (a.x - x) == 0 and dblcmp (a.y - y) == 0);
    }

    double dot (Vector a){
        return (x * a.x + y * a.y);
    }

    double dist (){
        return sqrt (dot (*this));
    }
};

double triArea (Vector a, Vector b, Vector c){
    return (a.cross (b) + b.cross (c) - c.cross (a)) / 2.0;
}

double polygonArea (vector <Vector>& P){
    double ret = 0.0;
    for (int i = 0; i < (int) P.size() - 1; i++){
        ret += P[i].cross (P[i + 1]);
    }
    return ret / 2.0;
}

double circleCircleArea (Vector a, double r1, Vector b, double r2){  //not sure of this function, strong dataset like codeforces gives WA
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
