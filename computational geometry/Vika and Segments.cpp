//https://codeforces.com/contest/610/problem/D
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e5;
typedef long long ll;
typedef pair<int,int>pii;
#define xx first
#define state second.first
#define height second.second
struct vert{
    int x,y1,y2;
    vert(){}
    vert(int x,int y1,int y2):x(x),y1(y1),y2(y2){}

    bool operator <(const vert&other){
        if(x!=other.x)return x<other.x;
        if(y1!=other.y1)return y1<other.y1;
        return y2<other.y2;
    }
};
struct hor{
    int y,x1,x2;
    hor(){}
    hor(int y,int x1,int x2):y(y),x1(x1),x2(x2){}
    bool operator <(const hor&other){
        if(y!=other.y)return y<other.y;
        if(x1!=other.x1)return x1<other.x1;
        return x2<other.x2;
    }
};

bool cmp(vert a,vert b){
    return a.x<b.x;
}
vector<hor>H;
vector<vert>V;


vector<pair<int,pii> >x_events;
vector<int>y_events;

int bit[2*MAXN+10];
void update(int idx,int val){
    for(int x = idx;x <= 2*MAXN;x += x & -x)
        bit[x]+=val;
}

int query(int idx){
    int ret = 0;

    for(int x = idx;x > 0;x -= x & -x)
        ret += bit[x];

    return ret;
}

int main(){
    int n;
    scanf("%d",&n);

    y_events.push_back(-((int)1e9) - 10);
    for(int i=0;i<n;i++){
        int x1,y1,x2,y2;

        scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
      
        
        y_events.push_back(y1);y_events.push_back(y2);

        if(y1==y2)H.push_back(hor(y1,min(x1,x2),max(x1,x2)));
        else V.push_back(vert(x1,min(y1,y2),max(y1,y2)));
    }


    sort(y_events.begin(),y_events.end());
    y_events.resize(unique(y_events.begin(),y_events.end()) - y_events.begin());


    sort(H.begin(),H.end());
    sort(V.begin(),V.end());


    vector<hor>h;
    for(int i=0,j=1;i<H.size();){
      
        if(i==H.size()-1 || j>=H.size() || H[i].y!=H[j].y || H[i].x2 < H[j].x1){
            h.push_back(H[i]);
           i=j; j++;
        }
        else{
            H[i].x2 = max(H[i].x2,H[j].x2);
            j++;
        }
    }
    H = h;


    vector<vert>v;
    for(int i=0,j=1;i<V.size();){
        if(i==V.size()-1 || j>=V.size() || V[i].x!=V[j].x || V[i].y2 < V[j].y1){
            v.push_back(V[i]);
            i=j;j++;
        }
        else{
            V[i].y2 = max(V[i].y2,V[j].y2);
            j++;
        }
    }
    V = v;


     //for(int i=0;i<H.size();i++)cout<<H[i].y<<"  : "<<H[i].x1<<","<<H[i].x2<<endl;
     //cout<<"----\n";
     //for(int i=0;i<V.size();i++)cout<<V[i].x<<"  : "<<V[i].y1<<","<<V[i].y2<<endl;



    for(int i=0;i<H.size();i++){
        x_events.push_back(make_pair(H[i].x1,make_pair(0,H[i].y)));
        x_events.push_back(make_pair(H[i].x2,make_pair(1,H[i].y)));
    }
    sort(x_events.begin(),x_events.end());






    ll res=0;
    // count horizontal alone
    for(int i=0;i<H.size();i++)
        res += H[i].x2-H[i].x1+1;

//
    sort(V.begin(),V.end(),cmp);
    int ptr=0; // ptr for x_events


  /*  for(int i=0;i<x_events.size();i++){
        printf("%d %d %d$$$\n",x_events[i].xx,x_events[i].height,x_events[i].state);
    }*/


    for(int i=0;i<V.size();i++){

        //cout<<V[i].x<<"   "<<V[i].y1<<","<<V[i].y2<<"-------\n";

        while(ptr<x_events.size() && x_events[ptr].xx<V[i].x){

            if(x_events[ptr].state==1)
                update(lower_bound(y_events.begin(),y_events.end(),x_events[ptr].height)-y_events.begin(),-1);
            else
                update(lower_bound(y_events.begin(),y_events.end(),x_events[ptr].height)-y_events.begin(),1);
            ptr++;
        }


        while(ptr<x_events.size() && x_events[ptr].xx==V[i].x && x_events[ptr].state==0){
            update(lower_bound(y_events.begin(),y_events.end(),x_events[ptr].height)-y_events.begin(),1);
            ptr++;
        }

        int toadd = V[i].y2- V[i].y1+1;
        int rnk_y1=lower_bound(y_events.begin(),y_events.end(),V[i].y1)-y_events.begin();
        int rnk_y2=lower_bound(y_events.begin(),y_events.end(),V[i].y2)-y_events.begin();


        int tosub = query(rnk_y2) - query(rnk_y1-1);
        res += toadd - tosub;



    }

    printf("%I64d\n",res);

}