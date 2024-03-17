#include <bits/stdc++.h>
using namespace std;
const int MAXN=2e5;
char buff[MAXN+5];
string T;
int n,N;
int SA[MAXN+5],tempSA[MAXN+5];
int RA[MAXN+5],tempRA[MAXN+5];
int c[MAXN+5];

void countingSort(int k){
	int maxi=max(N,300);
	
	memset(c,0,sizeof c);
	for(int i=0;i<N;i++)//loop on all suffixes
		c[i+k<N?RA[i+k]:0]++;
		
	int sum;
	for(int i=sum=0;i<maxi;i++){
		int t=c[i];
		c[i] = sum;
		sum += t;
	}
	
	for(int i=0;i<N;i++){
		int rnk = SA[i]+k<N?RA[SA[i]+k]:0;
		tempSA[c[rnk]] = SA[i];
		c[rnk]++;
	}
	for(int i=0;i<N;i++)
		SA[i] = tempSA[i];
}
void buildSA(){

	for(int i=0;i<N;i++)RA[i]=T[i];
	for(int i=0;i<N;i++)SA[i]=i;// put in SA all suffixes (unordered)
	
	for(int k=1;k<N;k<<=1){ //k: half of my current range
		
		// sort all suffixes of length 2k (SA array): first according to second half, then according to first half, USING RA
		countingSort(k);
		countingSort(0);
		
		
		// now SA sorted with length 2k
		// and RA sorted with length k

		int r=0;
		tempRA[SA[0]]=r;
		// update RA of length 2k ( using sorted SA of length 2k, and RA of length k )
		for(int i=1;i<N;i++) // loop on the sorted SA
			tempRA[SA[i]] = (RA[SA[i]]==RA[SA[i-1]] && RA[SA[i]+k]==RA[SA[i-1]+k])?r:++r;
		
		for(int i=0;i<N;i++)
			RA[i]=tempRA[i];
		
		if(RA[SA[n-1]] == N-1)break; // nice optimization trick
	}
}
int Phi[MAXN+5],PLCP[MAXN+5],LCP[MAXN+5];
void computeLCP(){
	
	
	//Phi: the prev suffix(idx) of current suffix(idx), in my suffix array 
	Phi[SA[0]] = -1;
    for(int i=1;i<N;i++)
		Phi[SA[i]] = SA[i-1];
	
	int L=0;
	for(int i=0;i<N;i++){
		if(Phi[i]==-1){PLCP[i]=0;continue;}
		
		int i1=i,i2=Phi[i];
		while(T[i1+L] == T[i2+L])L++;   
		
		PLCP[i] = L;
		L=max(L-1,0);
	}
	
	// PCLP[the suffix index]
	// LCP[the suffix rank]
	for(int i=0;i<N;i++){ // i:0 to n-1, ranks of suffixes
		LCP[i] = PLCP[SA[i]]; 
	}

}
int main(){
	int tc;
	scanf("%d",&tc);
	while(tc--){
		scanf("%d%s",&n,buff);
		T=buff;
		
		T=T+T+"$";
		N=2*n+1;
		
		buildSA();
		
		computeLCP();
		
		//for(int i=0;i<n;i++)
		//	printf("SA:%2d\tRA:%2d\t%s\t%d\n",SA[i],RA[SA[i]],T.substr(SA[i]).c_str(),LCP[i]);		
		
		int i,ans;
	    for(i=0;i<N;i++){
			if(SA[i]<n )
				{ans = SA[i]; i++;break;}
		}
		
		while(LCP[i]>=n){
			ans=min(ans,SA[i]);
			i++;
		}
		
		printf("%d\n",ans);
		
	}
}
