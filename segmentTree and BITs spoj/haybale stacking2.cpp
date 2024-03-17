#include <bits/stdc++.h>
using namespace std;
const int MAXN=1e6;
const int MAXK=25000;
int st[MAXN+5],en[MAXN+5],arr[MAXN+5];
int main(){
	// all 1 indexed
	int n,k,x,y;
	scanf("%d%d",&n,&k);
	for(int i=0;i<k;i++){
		scanf("%d%d",&x,&y);
		st[x]++;
		en[y]--;
	}
		
	
	
	int add=0;
	for(int i=1;i<=n;i++){
		add+=st[i];
		arr[i]=add;
		add+=en[i];
	}
	
	sort(arr+1,arr+1+n);
	printf("%d\n",arr[n/2+1]);
}
