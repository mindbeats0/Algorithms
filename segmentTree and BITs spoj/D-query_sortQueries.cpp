/******************************************************************
***   Problewm      : Spoj 3267. D-query                        ***
***   Author        : Shipu Ahamed (Psycho Timekiller)          ***
***   E-mail        : shipuahamed01@gmail.com                   ***
***   University    : BUBT,Dept. of CSE                         ***
***   Team          : BUBT_Psycho                               ***
***   My Blog       : http://shipuahamed.blogspot.com           ***
***   Facebook      : http://www.facebook.com/DeesheharaShipu   ***
******************************************************************/ 
#include <bits/stdc++.h>
using namespace std;
 
#define for0(i,n) for(int i=0;i<n;i++)
#define for1(i,n) for(int i=1;i<=n;i++)
#define rfor0(i,n) for(int i=n;i>=0;i--)
#define rfor1(i,n) for(int i=n;i>=1;i--)
#define forse(i,a,b) for(int i=a;i<=b;i++)
#define ll long long
#define pi 2*acos(0.0)
#define all(v) v.begin(),v.end()
 
#define si(t) scanf("%d",&t)
#define sl(t) scanf("%lld",&t)
#define sf(t) scanf("%f",&t)
#define sdb(t) scanf("%lf",&t)
#define schar(c) scanf("%c",&c)
#define sstring(s) scanf("%s",s)
#define ssi(a,b) scanf("%d%d",&a,&b)
#define ssl(a,b) scanf("%lld%lld",&a,&b)
 
#define P(a) printf("%d",a)
#define PL(a) printf("%lldn",a)
#define PF(a) printf("%fn",a)
#define PDB(a) printf("%lfn",a)
#define PN(a) printf("%d ",a)
#define PLN(a) printf("%lld ",a)
#define PFN(a) printf("%f ",a)
#define PDBN(a) printf("%lf ",a)
 
#define CP(a) cout<<a<<endl
#define CPN(a) cout<<a<<" "
#define Case(no) printf("Case %d: ",++no)
#define nl puts("")
 
#define db(x) cout << #x << " -> " << (x) << endl;
#define db_sarr(i,a) cout<<#a<<"["<<i<<"] -> "<<a[i]<<" "<<endl;
#define db_arr(a,start,end) for(ll i=start;i<=end;i++) cout<<#a<<"["<<i<<"] -> "<<a[i]<<" "<<endl;
#define db_mat(mat,row,col) for(ll i=0;i<row;i++) {for(ll j=0;j<col;j++) cout<<mat[i][j]<<" ";cerr<<endl;}
 
#define ff first
#define se second
#define pb push_back
#define ppb pop_back
#define mkp(a,b) make_pair(a,b)
#define ST(v) sort(all(v))
#define sz(x) (int)x.size()
#define gcd(a,b) __gcd(a,b)
#define lcm(a,b) (a*(b/gcd(a,b)))
#define max3(a,b,c) max(a,max(b,c))
#define min3(a,b,c) min(a,min(b,c))
#define maxall(v) *max_element(all(v))
#define minall(v) *min_element(all(v))
#define cover(a,d) memset(a,d,sizeof(a))
#define popcount(i) __builtin_popcount(i)                         //count one
#define parity(i)   __builtin_parity(i)       //evenparity 0 and odd parity 1
#define input freopen("in.txt","r",stdin)
#define output freopen("out.txt","w",stdout)
#define un(v) ST(v), (v).earse(unique(all(v)),v.end())
#define common(a,b) ST(a), ST(b), a.erase(set_intersection(all(a),all(b),a.begin()),a.end())
#define uncommon(a,b) ST(a), ST(b), a.erase(set_symmetric_difference(all(a),all(b),a.begin()),a.end())
 
typedef  vector<int> vi;
typedef  vector<ll> vl;
typedef  vector<string> vs;
typedef  pair<int,int> pii;
typedef  vector<pii> vpii;
typedef  set<int> si;
typedef  map<int,int> mii;
typedef  map<string,int> msi;
 
////============ CONSTANT ===============////
#define MAXLL 9223372036854775807
#define MINLL 9223372036854775808
#define MAXL  2147483647
#define MINL  2147483648
#define mx7   10000007
#define mx6   1000006
#define inf   1<<30                                           //infinity value
#define eps   1e-9
#define mx    (100010)
#define mod   1000000007
////=====================================////
 
struct DQ
{
    int qs,qe,id;
}a[mx6];
 
bool cmp(DQ a,DQ b)
{
     return a.qe<b.qe;
 
}
 
int tree[4*mx6],track[mx6],res[mx6],pos[mx6],arr[mx6];
 
void update(int node,int s,int e,int i,int value)
{
    if(i>e||i<s) return;
    if(s==e)
    {
        tree[node]=value;
        return;
    }
    int n=node<<1;
    int mid=(s+e)>>1;
    update(n,s,mid,i,value);
    update(n+1,mid+1,e,i,value);
    tree[node]=tree[n]+tree[n+1];
}
 
int qu(int node,int s,int e,int qs,int qe)
{
    if(qs>e||qe<s) return 0;
    if(e<=qe && s>=qs) return tree[node];
    int n=node<<1;
    int mid=(s+e)>>1;
    return qu(n,s,mid,qs,qe) + qu(n+1,mid+1,e,qs,qe);
    
}
 
int main()
{
    int n;
    si(n);
	for(int i=1;i<=n;i++)
		si(arr[i]);
	int q;
	si(q);
	for(int i=1;i<=q;i++)
	{
		int x,y;
		ssi(x,y);
		a[i].qs=x;
		a[i].qe=y;
		a[i].id=i;
	}
	sort(a+1,a+q+1,cmp);
        
	int j=1;
	for(int i=1;i<=q;i++)
	{
		while(j<=a[i].qe)
		{		
			 if(pos[arr[j]])
				update(1,1,n,pos[arr[j]],0);
		   
			 update(1,1,n,j,1);
			 pos[arr[j]]=j;
			 j++;
		 }
		 res[a[i].id]=qu( 1 , 1 , n, a[i].qs , a[i].qe );
		 
	}
    for(int i=1;i<=q;i++)
	  printf("%d\n",res[i]);
    return 0;
}
