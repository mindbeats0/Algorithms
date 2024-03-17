#include<bits/stdc++.h>
using namespace std;
#define sz(a) ((int)(a).size())
struct Point{
    int x,y;
    const bool operator == (const Point &other)const{
        return x==other.x && y==other.y;
    }
    const bool operator < (const Point &other)const{
        return x < other.x || x == other.x  && y<other.y;
    }
}PIVOT;

long long dist2(Point p1,Point p2){
    long long X=p1.x-p2.x,Y=p1.y-p2.y;
    return X*X + Y*Y;
}
long long cross(Point p1,Point p2,Point p3){ // Ax * By - Ay * Bx
    return (long long)(p2.x-p1.x)*(p3.y-p1.y) -  (long long)(p2.y-p1.y)*(p3.x-p1.x);
}
bool angleCmp(const Point&a,const Point&b){
    long long _cross=cross(PIVOT,a,b);
    if(_cross==0)return dist2(PIVOT,a)<dist2(PIVOT,b);
    else return _cross>0; // counter clockwise
}

vector<Point> convexHull(vector<Point> p){
    sort(p.begin(),p.end());
    p.resize(unique(p.begin(),p.end())-p.begin());

    if((int)p.size()<=3)return p;

    Point pivot=p[0]; int idx=0;
    for(int i=1;i<(int)p.size();i++)
        if(p[i].y<pivot.y || p[i].y==pivot.y &&  p[i].x<pivot.x )
            pivot=p[i],idx=i;
    swap(p[0],p[idx]);

    PIVOT=pivot;
    sort(++p.begin(),p.end(),angleCmp);


    p.push_back(p[0]);
    vector<Point>ret;
    ret.push_back(p[0]);
    ret.push_back(p[1]);

    for(int i=2;i<(int)p.size();i++){
         while(sz(ret)>=2 && cross(ret[sz(ret)-2],ret[sz(ret)-1],p[i])<0 )ret.pop_back();
         ret.push_back(p[i]);
    }
    ret.pop_back();
    return ret;

}

int main(){

}
