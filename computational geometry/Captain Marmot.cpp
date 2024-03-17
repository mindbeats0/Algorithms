//https://codeforces.com/contest/474/problem/C
#include<bits/stdc++.h>
using namespace std;

#define PI acos(-1)
#define eps 1e-9

struct point{
    double x,y;
    point(){}
    point(double x,double y):x(x),y(y){}
    const bool operator < (const point&other)const{
         if(abs(y-other.y)>eps)return y<other.y;
        if(abs(x-other.x)>eps)return x>other.x;
        return false;
    }

};


struct vec{
    double x,y;
    vec(double _x,double _y):x(_x),y(_y){}
};
inline vec toVec(point a,point b){
    return vec(b.x-a.x,b.y-a.y);
}
double dist(point p1,point p2){
    return hypot(p1.x-p2.x,p1.y-p2.y);
}
inline double cross(vec a ,vec b){return a.x*b.y - a.y*b.x;}
inline bool ccw(point p,point q,point r){
    return cross(toVec(p,q),toVec(p,r))>0;
}
bool collinear(point p,point q,point r){
    return fabs(cross(toVec(p,q),toVec(p,r)))<eps;
}



point rotate(point p,double rad){
    return point(p.x*cos(rad)-p.y*sin(rad),p.x*sin(rad)+p.y*cos(rad));
}

point rot(double x,double  y,double  a,double  b,int cnt){
    x-=a;
    y-=b;
    point ret=rotate(point(x,y),PI/2*cnt);
    ret.x+=a;
    ret.y+=b;
    return ret;

}
inline bool eq(double a,double b){return abs(a-b)<eps;}
point pivot;
bool angleCmp(point a,point b){
    double d1x=a.x-pivot.x,d1y=a.y-pivot.y;
    double d2x=b.x-pivot.x,d2y=b.y-pivot.y;

    if(eq(atan2(d1y,d1x),atan2(d2y,d2x)))
            return dist(pivot,a)<dist(pivot,b);

    return atan2(d1y,d1x)<atan2(d2y,d2x);
}

bool square(vector<point>&p){
    sort(p.begin(),p.end());
    pivot=p[0];
    sort(++p.begin(),p.end(),angleCmp);
    /* for(int i=0;i<4;i++){
            cout<<p[i].x<<" "<<p[i].y<<endl;
        }*/
    double dist1=dist(p[0],p[1]);
    double dist2=dist(p[1],p[2]);
    double dist3=dist(p[2],p[3]);
    double dist4=dist(p[3],p[0]);
    double dist5=dist(p[0],p[2]);

    if(dist1>eps && eq(dist1,dist2) && eq(dist2,dist3) && eq(dist3,dist4) && eq(dist5,hypot(dist1,dist2))){


        return true;
    }

      /*  cout<<dist1<<" "<<dist2<<" "<<dist3<<" "<<dist4<<" "<<dist5<<" "<<endl;
        cout<<"-----\n";*/
    return false;

}


inline void rot2(int &x, int &y, int a, int b) {
	int dx = x - a;
	int dy = y - b;

	int nx = a - dy;
	int ny = b + dx;
	x = nx;
	y = ny;
}



int x[4],y[4],a[4],b[4];
vector<point>all;
int main(){

    int n;
    cin>>n;
    for(int q=0;q<n;q++){


        for(int i=0;i<4;i++)
            cin>>x[i]>>y[i]>>a[i]>>b[i];



         int res=100,X,Y;
         for(int i=0;i<4;i++)
            for(int j=0;j<4;j++)
                for(int k=0;k<4;k++)
                     for(int l=0;l<4;l++){

                          int cur=i+j+k+l; all.clear();

                          X=x[0];Y=y[0]; for(int cc=0;cc<i;cc++)rot2(X,Y,a[0],b[0]);
                          all.push_back(point((double)X,(double)Y));

                            X=x[1];Y=y[1]; for(int cc=0;cc<j;cc++)rot2(X,Y,a[1],b[1]);
                          all.push_back(point((double)X,(double)Y));

                            X=x[2];Y=y[2]; for(int cc=0;cc<k;cc++)rot2(X,Y,a[2],b[2]);
                          all.push_back(point((double)X,(double)Y));

                            X=x[3];Y=y[3]; for(int cc=0;cc<l;cc++)rot2(X,Y,a[3],b[3]);
                          all.push_back(point((double)X,(double)Y));


                          if(square(all)){res=min(res,cur);/*return 0;*/}

                     }
             //cout<<"******* ";
             if(res==100)cout<<"-1\n";
             else cout<<res<<"\n";

    }

}
 