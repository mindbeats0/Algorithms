//https://codeforces.com/contest/280/problem/A
#include<bits/stdc++.h>
using namespace std;
typedef complex<double>point;
#define sz(a) ((int)(a).size())
#define polar(r,t)((r)*exp(point(0,(t))))
#define rotate(v,t)(polar(v,t))
#define vec(a,b) ((b)-(a))
#define cross(a,b) ((conj(a)*(b)).imag())
#define EPS 1e-9
#define PI acos(-1)
 
bool intersect(const point&a,const point&b, const point&p, const point&q, point&ret ){
    double d1 = cross(p-a, b-a);
    double d2 = cross(q-a, b-a);
 
    ret = (d1*q - d2*p) / (d1-d2);
    if(fabs(d1-d2) > EPS)
        return 1;
    return 0;
}
 
void polygonCut(const vector<point>&p,const point&a,const point&b, vector<point>& res){
    res.clear();
    for(int i=0;i<sz(p);i++){
        int j = (i+1)%sz(p);
        bool in1 = cross(vec(a,b),vec(a,p[i])) > EPS;
        bool in2 = cross(vec(a,b),vec(a,p[j])) > EPS;
 
        if(in1)res.push_back(p[i]);
        if(in1^in2){
            point r;
            intersect(a,b,p[i],p[j],r);
            res.push_back(r);
        }
    }
}
void PolygonIntersect(const vector<point>&p,const vector<point>&q, vector<point>& res){
    res=q;
    for(int i=0;i<sz(p);i++){
        int j = (i+1)%sz(p);
        vector<point>temp;
        polygonCut(res,p[i],p[j],temp);
        res = temp;
        if(res.empty())return ;
    }
}
 
double polygonArea(const vector<point>&p){
    double res=0;
    for(int i=0;i<sz(p);i++){
        int j = (i+1)%sz(p);
        res += cross(p[i],p[j]);
    }
    return fabs(res) / 2;
}
int main(){
     double w,h,alpha;
     cin>>w>>h>>alpha;
 
    vector<point>p1;
    p1.push_back(point(w/2,-h/2));
    p1.push_back(point(w/2,h/2));
    p1.push_back(point(-w/2,h/2));
    p1.push_back(point(-w/2,-h/2));
 
 
 
 
 
    vector<point>p2;
    for(int i=0;i<4;i++){
            p2.push_back(rotate(p1[i],alpha*PI/180));
    }
 
    vector<point>res;
    PolygonIntersect(p1,p2,res);
 
    cout << (fixed)<<setprecision(9)<<polygonArea(res) << endl;
 
}