//https://codeforces.com/contest/581/problem/D
#include <bits/stdc++.h>
using namespace std;
 
struct dim {
    int len,wid;
    dim(){}
    dim(int len,int wid):len(len),wid(wid){}
};
 
vector<dim>v(3);
 
char symb[3]={'A','B','C'};
 
 
bool fit1(int side){
    if(v[0].len == v[1].len  && v[1].len == v[2].len && v[0].len==side
    && v[0].wid + v[1].wid  + v[2].wid == side){
 
          cout<<side<<"\n";
 
         for(int i=0;i<v[0].wid;i++){
            for(int j=0;j<v[0].len;j++)cout<<"A";
            cout<<"\n";
         }
         for(int i=0;i<v[1].wid;i++){
            for(int j=0;j<v[1].len;j++)cout<<"B";
            cout<<"\n";
         }
         for(int i=0;i<v[2].wid;i++){
            for(int j=0;j<v[2].len;j++)cout<<"C";
            cout<<"\n";
         }
         return true;
    }
    return false;
}
 
 
bool fit2(int X,int Y,int idx1,int idx2){
 
 
    int col1=-1,col2=-1;
    if(v[idx1].len ==Y && v[idx2].len ==Y  && v[idx1].wid + v[idx2].wid==X ){
        col1=v[idx1].wid,col2=v[idx2].wid;
    }
    else if(v[idx1].len ==Y && v[idx2].wid ==Y  && v[idx1].wid + v[idx2].len==X){
        col1=v[idx1].wid,col2=v[idx2].len;
    }
 
 
    else if(v[idx1].wid ==Y && v[idx2].len ==Y && v[idx1].len + v[idx2].wid==X ){
        col1=v[idx1].len,col2=v[idx2].wid;
    }
    else if(v[idx1].wid ==Y && v[idx2].wid ==Y  && v[idx1].len + v[idx2].len==X){
        col1=v[idx1].len,col2=v[idx2].len;
    }
 
    if(col1==-1 && col2==-1)return false;
 
      cout<<X<<"\n";
      for(int i=0;i<Y;i++){
            for(int j=0;j<col1;j++)cout<<symb[idx1];
            for(int j=0;j<col2;j++)cout<<symb[idx2];
            cout<<"\n";
        }
 
       return true;
 
}
 
int main(){
 
 
   for(int i=0;i<3;i++){
        cin>>v[i].len>>v[i].wid;
        if(v[i].len<v[i].wid)swap(v[i].len,v[i].wid);
   }
 
 
   for(int i=1;i<=200;i++){
        if(fit1(i))return 0;
 
        if(v[0].len == i && v[0].wid < i && fit2(i,i-v[0].wid,1,2)){
 
            for(int a=0;a<v[0].wid;a++){
                for(int b=0;b<i;b++)cout<<symb[0];
                cout<<"\n";
            }
            return 0;
        }
        if(v[1].len == i && v[1].wid < i && fit2(i,i-v[1].wid,0,2)){
 
            for(int a=0;a<v[1].wid;a++){
                for(int b=0;b<i;b++)cout<<symb[1];
                cout<<"\n";
            }
            return 0;
        }
        if(v[2].len == i && v[2].wid < i && fit2(i,i-v[2].wid,0,1)){
 
            for(int a=0;a<v[2].wid;a++){
                for(int b=0;b<i;b++)cout<<symb[2];
                cout<<"\n";
            }
            return 0;
        }
   }
 
   cout<<"-1\n";
   return 0;
 
}