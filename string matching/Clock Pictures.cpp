#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN = 2e5;
const ll d = 360000;
const ll M1 = 1e9 + 7;
const ll M2 = 1e9 + 9;

#define mp make_pair
#define fst first 
#define snd second
int a[MAXN+5],b[MAXN+5],pat[MAXN+5],T[2*MAXN+5],n,N;
pair<ll,ll> H;
bool solve(){
    N=2*n;
    
    ll pw1=1,pw2=1;
    for(int i=0;i<n-1;i++){
        pw1 = (pw1*d)%M1;
        pw2 = (pw2*d)%M2;
    }
    // construct H[] array for clock1
    H = mp(pat[0],pat[0]);
    for(int i=1;i<n;i++)
        H = mp( (H.fst*d + pat[i])%M1 , (H.snd*d + pat[i])%M2 );
    
    
    // match clock1 in clock2
    bool ans=false;
    pair<ll,ll> h=mp(0,0);
    int i=0;
    while(i<n){
        h = mp ((h.fst*d + T[i])%M1 , (h.snd*d + T[i])%M2);
        i++;
    }
    
    if(h==H)ans=true;
    
    for(i=n;i<N && !ans;i++){    
        h.fst = ((h.fst - T[i-n]*pw1%M1)+M1)%M1;
        h.fst = (h.fst*d + T[i])%M1;
        
        h.snd = ((h.snd - T[i-n]*pw2%M2)+M2)%M2;
        h.snd = (h.snd*d + T[i])%M2;
        
        /*cout<<H[n-1].fst<<" "<<H[i].snd<<endl;
        cout<<h.fst<<" "<<h.snd<<endl;
        cout<<"---------\n";*/
        
        if(h==H)ans=true;
    }
    
    return ans;    
}
int main(){
    while(scanf("%d",&n)!=EOF){
        for(int i=0;i<n;i++)
            scanf("%d",&a[i]);
        for(int i=0;i<n;i++)
            scanf("%d",&b[i]);
        sort(a,a+n);
        sort(b,b+n);
        
        pat[0] = a[0]-a[n-1] + 360000;
        for(int i=1;i<n;i++)pat[i] = a[i]-a[i-1];
        
        T[0] = b[0]-b[n-1] + 360000;
        for(int i=1;i<n;i++)T[i] = b[i]-b[i-1];
        
        
        for(int i=0;i<n;i++)
            T[i+n]=T[i];
        
        string yes = "possible";
        string no = "impossible";
         
        printf("%s\n",solve()?yes.c_str():no.c_str());
    }
}
