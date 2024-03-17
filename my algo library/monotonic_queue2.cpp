#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

#define endline "\n"
#define MAX 100005
#define mp(x,y) make_pair((x),(y))

struct stack_max{
    stack<pii> st;
    void push(int x){
        if(st.size())
            st.push(mp(x,max(x,st.top().second)));
        else
            st.push(mp(x,x));
    }
    void pop(){
        st.pop();
    }
    int top(){
        if(st.size())
            return st.top().first;
        return 0;
    }


    int getmax(){
        if(st.size())
            return st.top().second;
        return 0;
    }
    int size(){
        return st.size();
    }
};

struct queue_max
{
    stack_max in,out;

    void push(int x){
        in.push(x);
    }
    void pop(){
        if(out.empty())
            while(in.size())
                out.push(in.top()),in.pop();
        out.pop();
    }

    int getmax(){
        return max(in.getmax(),out.getmax());
    }
    int size(){
        return in.size()+out.size();
    }

};
int main(){

}
