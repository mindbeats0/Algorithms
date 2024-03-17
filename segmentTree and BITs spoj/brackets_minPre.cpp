/******************************************************************
***   Problewm      : Spoj  61. Brackets                        ***
***   Author        : Shipu Ahamed (Psycho Timekiller)          ***
***   E-mail        : shipuahamed01@gmail.com                   ***
***   University    : BUBT,Dept. of CSE                         ***
***   Team          : BUBT_Psycho                               ***
***   My Blog       : http://shipuahamed.blogspot.com           ***
***   Facebook      : http://www.facebook.com/DeesheharaShipu   ***
******************************************************************/
#include <list>
#include <set>
#include <map>
#include <ctime>
#include <stack>
#include <queue>
#include <cmath>
#include <deque>
#include <limits>
#include <string>
#include <cctype>
#include <cstdio>
#include <vector>
#include <bitset>
#include <numeric>
#include <cassert>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <utility>
#include <complex>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <algorithm>
using namespace std;
 
#define sc scanf
#define pf printf
#define ll long long
#define pi 2*acos(0.0)
#define ull unsigned long long
#define all(v) v.begin(),v.end()
 
#define sii(t) scanf("%d",&t)
#define sll(t) scanf("%lld",&t)
#define ssii(a,b) scanf("%d%d",&a,&b)
#define ssll(a,b) scanf("%lld%lld",&a,&b)
#define Case(no) printf("Test %d:n",++no)
#define nl puts("")
#define P(a) printf("%dn",a)
#define PL(a) printf("%lldn",a)
#define PN(a) printf("%d ",a)
#define PLN(a) printf("%lld ",a)
 
 
#define ff first
#define se second
#define pb push_back
#define ST(v) sort(all(v))
#define gcd(a,b) __gcd(a,b)
#define lcm(a,b) (a*(b/gcd(a,b)))
#define max3(a,b,c) max(a,max(b,c))
#define min3(a,b,c) min(a,min(b,c))
#define maxall(v) *max_element(all(v))
#define minall(v) *min_element(all(v))
#define cover(a,d) memset(a,d,sizeof(a))
#define popcount(i) __builtin_popcount(i)                       //count one
#define input freopen("in.txt","r",stdin)
#define output freopen("out.txt","w",stdout)
#define un(v) ST(v), (v).earse(unique(all(v)),v.end())
#define common(a,b) ST(a), ST(b), a.erase(set_intersection(all(a),all(b),a.begin()),a.end())
#define uncommon(a,b) ST(a), ST(b), a.erase(set_symmetric_difference(all(a),all(b),a.begin()),a.end())
 
////============ CONSTANT ===============////
#define mx  (30010)
#define Max 1000000                                           //infinity value
#define eps 1e-9
#define mod 10007
////=====================================////
int sum[mx*4],a[mx*4];
void update(int node,int s,int e,int i,int value)
{
    if(i>e||i<s) return;
    if(s==e)
    {
        sum[node]=value;
        a[node]=value;
        return;
    }
    int n=node<<1;
    int mid=(s+e)>>1;
    update(n,s,mid,i,value);
    update(n+1,mid+1,e,i,value);
    sum[node]=sum[n]+sum[n+1];
    a[node]=min(a[n],sum[n]+a[n+1]);


 //   printf("%d  %d %d\n",s,e,a[n]);
}
int main()
{
    int n,no=0;
    while(sii(n)==1)
    {
        char s[mx];
        scanf("%s",s);
        Case(no);
        for(int i=1;i<=n;i++)
        {
            if(s[i-1]=='(')
                update(1,1,n,i,1);
            else
                update(1,1,n,i,-1);
        }
        int p;
        sii(p);
        while(p--)
        {
            int qu;
            sii(qu);
            if(qu==0)
            {
                if(sum[1]==0 && a[1]==0)
                    puts("YES");
                else
                    puts("NO");
            }
            else
            {
                if(s[qu-1]=='(')
                {
                    s[qu-1]=')';
                    update(1,1,n,qu,-1);
                }
                else if(s[qu-1]==')')
                {
                    s[qu-1]='(';
                    update(1,1,n,qu,1);
                }
            }
        }
    }
    return 0;
}
