//https://codeforces.com/contest/552/problem/D
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define num first
#define den second


int px[2010],py[2010];

int gcd(int a,int b){
    if(a<b)swap(a,b);
    if(!b)return a;
    return gcd(b,a%b);
}

pair<int,int> calc(int i,int j){

    int num=py[j]-py[i];
    int den=px[j]-px[i];

    int g=gcd(abs(num),abs(den));
    num/=g; den/=g;
    if(num==0)den=1;
    else if(den==0)num=1;
    else if(num*den>0){num=abs(num); den=abs(den);}
    else {num=abs(num)*-1; den=abs(den);}

    return make_pair(num,den);
}
int main(){

    int n;cin>>n;
    for(int i=0;i<n;i++)cin>>px[i]>>py[i];

    ll res=0;
    map<pair<int,int>, int  >freq;
    map<pair<int,int>, int  >::iterator it;
    for(int i=0;i<n-2;i++){
         int p=(n-i-1);
         ll cur=p*(p-1)/2;

        freq.clear();
        for(int j=i+1;j<n;j++){
            freq[calc(i,j)]++;
        }

        for(it=freq.begin();it!=freq.end();it++){
            if(it->second==1)continue;
            int t=it->second;
             cur-=t*(t-1)/2;
        }
        res+=cur;

    }
    cout<<res<<"\n";
}
 