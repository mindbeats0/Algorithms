// Mostafa Saad
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll extended_euclid(ll a, ll b, ll &x, ll &y){
    if(b==0){
        x=1,y=0;
        return a;
    }
    // swap a,b and x,y
    ll g = extended_euclid(b,a%b,y,x);
    y -= (a/b)*x;
    return g;
}

int main(){

}

