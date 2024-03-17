#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int>pii;
#define mp make_pair
#define INF 1<<30
struct stack_max{
    stack<pii>st;

    void push(int x){
        if(st.empty())st.push(mp(x,x));
        else st.push(mp(x,max(x,st.top().second)));
    }
    void pop(){
        if(!st.empty())st.pop();
    }

    int getmax(){
        if(!st.empty())return st.top().second;
        return -INF;
    }
    int size(){
        return (int)st.size();
    }
};

struct queue_max{
    stack<int>in; int max1;

    stack_max out;

    void push(int x){
        if(in.empty())max1=x;
        else max1=max(max1,x);
        in.push(x);
    }
    void pop(){
        if(!out.size()){
             while(!in.empty())out.push(in.top()),in.pop();
             max1=-INF;
        }
        out.pop();
    }
    int getmax(){
        if(in.empty())max1=-INF;
        return max(out.getmax(),max1);
    }
    int size(){
        return (int)in.size()+(int)out.size();
    }

};

int main(){}
