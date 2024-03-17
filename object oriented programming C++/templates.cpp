#include <bits/stdc++.h>
using namespace std;





template <class T>
class A{
    T a,b;
    public:
    void print();
     A(T a,T b);
};

template <class T>
void A<T>::print(){cout<<a<<" "<<b<<"\n";}

template<class T>
A<T>:: A(T a,T b):a(a),b(b){
    cout<<"copy constructor\n";
}


int main(){
    A<int>x(4,5);
    x.print();
}
