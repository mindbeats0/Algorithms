#include <iostream>
#include <bitset>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <string>
#include <string.h>
#include <cmath>
#include <memory.h>
#include <algorithm>
using namespace std;
typedef long long ll;
 
const int M=1000000007;
int n,H[100000];
int SA[100000];
int power27[100000]; // == 27^i % M
int getHash(int i,int j){
	if(!i)return H[j];
	
	ll ret = H[j] - (H[i-1]*power27[j-i+1])%M;
	ret %= M;
	ret=(ret+M)%M;
	
	return ret;
	
}
int LCP(int a,int b){
	int l=0,r=min(n-SA[a],n-SA[b])-1,mid;
	int res=r+1;
	while(l<=r){
		mid=(l+r)/2;
		if(getHash(SA[a],SA[a]+mid)!=getHash(SA[b],SA[b]+mid)){
			r=mid-1;
			res=mid;
		}else
			l=mid+1;
	}
	return res;
}
int main(){
	string s;
	for(int i=0;i<s.size();++i){
		H[i]=s[i]-'a'+1;
		if(i>0)
			H[i]=(H[i-1]*27+H[i])%M;
	}
	int x,y; // number of the suffixes
	LCP(x,y);
	return 0;
}
