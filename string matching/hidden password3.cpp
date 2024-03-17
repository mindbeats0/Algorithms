#include <bits/stdc++.h>
using namespace std;
const int MAXN=2e5;
char buff[MAXN+5];
string T;
int n;
int SA[MAXN+5],tempSA[MAXN+5];
int RA[MAXN+5],tempRA[MAXN+5];
int c[MAXN+5];

void countingSort(int k){
	int maxi=max(n,300);

	memset(c,0,sizeof c);
	for(int i=0;i<n;i++)//loop on all suffixes
		c[i+k<n?RA[i+k]:0]++;

	int sum;
	for(int i=sum=0;i<maxi;i++){
		int t=c[i];
		c[i] = sum;
		sum += t;
	}

	for(int i=0;i<n;i++){
		int rnk = SA[i]+k<n?RA[SA[i]+k]:0;
		tempSA[c[rnk]] = SA[i];
		c[rnk]++;
	}
	for(int i=0;i<n;i++)
		SA[i] = tempSA[i];
}
void buildSA(){

	for(int i=0;i<n;i++)RA[i]=T[i];
	for(int i=0;i<n;i++)SA[i]=i;// put in SA all suffixes (unordered)

	for(int k=1;k<n;k<<=1){ //k: half of my current range

		// sort all suffixes of length 2k (SA array): first according to second half, then according to first half, USING RA
		countingSort(k);
		countingSort(0);


		// now SA sorted with length 2k
		// and RA sorted with length k

		int r=0;
		tempRA[SA[0]]=r;
		// update RA of length 2k ( using sorted SA of length 2k, and RA of length k )
		for(int i=1;i<n;i++) // loop on the sorted SA
			tempRA[SA[i]] = (RA[SA[i]]==RA[SA[i-1]] && RA[SA[i]+k]==RA[SA[i-1]+k])?r:++r;

		for(int i=0;i<n;i++)
			RA[i]=tempRA[i];

		if(RA[SA[n-1]] == n-1)break; // nice optimization trick
	}
}

int main(){
	int tc;
	scanf("%d",&tc);
	while(tc--){
		scanf("%d%s",&n,buff);
		T=buff;

		T=T+T+"}";
		n=n*2+1;

		buildSA();

		int idx;
		for(int i=0;i<n;i++){
			if(SA[i]<n/2){
				idx=SA[i];
				break;
			}
		}


		printf("%d\n",idx);




	}
}
/*
1
20 riverriverriverriver
*/
