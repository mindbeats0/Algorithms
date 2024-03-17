#include <bits/stdc++.h>
using namespace std;
#define eps 1e-9
#define PI acos(-1)
struct point{
    double x,y;
    point(){x=y=0.0;}
    point(double x,double y):x(x),y(y){}
    bool operator == (point other)const{
        return (fabs(x-other.x)<eps && fabs(y-other.y)<eps);
    }
};
point pivot(0,0);

double dist(point p1,point p2){
    return hypot(p1.x-p2.x,p1.y-p2.y);
}



struct vec{
     double x,y;
     vec(double x,double y):x(x),y(y){}
};
vec toVec(point a,point b){
    return vec(b.x-a.x,b.y-a.y);
}
double dot(vec a,vec b){return (a.x*b.x+a.y*b.y);}
double norm_sq(vec v){return v.x*v.x+v.y*v.y;}
double cross(vec a,vec b){return a.x*b.y - a.y*b.x;}

bool ccw(point p,point q,point r){
    return cross(toVec(p,q),toVec(p,r))>0;
}


bool collinear(point p,point q,point r){
    return fabs(cross(toVec(p,q),toVec(p,r)))<eps;
}
double angle(point a,point o,point b){
    vec oa=toVec(o,a),ob=toVec(o,b);
    return acos(dot(oa,ob)/sqrt(norm_sq(oa)*norm_sq(ob)));
}
bool angleCmp(point a,point b){
    if(collinear(pivot,a,b))
        return dist(pivot,a)<dist(pivot,b);
    double d1x=a.x-pivot.x,d1y=a.y-pivot.y;
    double d2x=b.x-pivot.x,d2y=b.y-pivot.y;
    return (atan2(d1y,d1x)-atan2(d2y,d2x))<0;
}

bool inPolygon(point pt,const vector<point>&P){
    if( (int)P.size()==0)return false;
    double sum=0;
    for(int i=0;i<(int)P.size()-1;i++){
        sum+=angle(P[i],pt,P[i+1]);
    }
    return fabs(fabs(sum)-2*PI)<eps;
}

vector<point> CH(vector<point>P){
    int i,j,n=(int)P.size();
    if(n<=3){
        if(!(P[0]==P[n-1]))P.push_back(P[0]);
        return P;
    }
    int P0=0;
    for(int i=1;i<n;i++)
        if(P[i].y<P[P0].y || ( P[i].y==P[P0].y && P[i].x>P[P0].x ) )
            P0=i;
    point temp=P[0];P[0]=P[P0];P[P0]=temp;

    pivot=P[0];
    sort(++P.begin(),P.end(),angleCmp);

    vector<point>S;
    S.push_back(P[n-1]);S.push_back(P[0]);S.push_back(P[1]);
    i=2;
    while(i<n){
        j=(int)S.size()-1;
        if(ccw(S[j-1],S[j],P[i]))S.push_back(P[i++]);
        else S.pop_back();
    }
    return S;
}
int main(){
}
