#include <bits/stdc++.h>
using namespace std;

#define MAX_N 30010
typedef pair<int,int>pii;
char T[MAX_N];
int n;
int RA[MAX_N],tempRA[MAX_N];
int SA[MAX_N],tempSA[MAX_N],revSA[MAX_N];
int c[MAX_N];
int mini_LCP[MAX_N][20],mini_SA[MAX_N][20];
int Phi[MAX_N+5],PLCP[MAX_N+5],LCP[MAX_N+5];
void countingSort(int k){
    int i,sum,maxi=max(300,n);
    memset(c,0,sizeof c);
    for(int i=0;i<n;i++)
        c[i+k<n?RA[i+k]:0]++;
    for(int i=sum=0;i<maxi;i++){
        int t=c[i]; c[i]=sum; sum+=t;
    }
    for(int i=0;i<n;i++)
        tempSA[c[SA[i]+k<n?RA[SA[i]+k]:0]++]=SA[i];

    for(int i=0;i<n;i++)
        SA[i]=tempSA[i];

    for(int i=0;i<n;i++)
        revSA[SA[i]]=i;
}
 void constructSA(){
     int i,k,r;
     for(int i=0;i<n;i++)RA[i]=T[i];
     for(int i=0;i<n;i++)SA[i]=i;

    for(int k=1;k<n;k<<=1){
        countingSort(k);
        countingSort(0);

        tempRA[SA[0]]=r=0;

        for(int i=1;i<n;i++)
            tempRA[SA[i]] =
                (RA[SA[i]]==RA[SA[i-1]] && RA[SA[i]+k]==RA[SA[i-1]+k])?r:++r;

        for(int i=0;i<n;i++)
            RA[i]=tempRA[i];
        if(RA[SA[n-1]]==n-1)break;
    }
 }

int lcp(int a, int b){
    if(a>b)swap(a,b);


    if(a==b)return n-SA[a]-1;
    a++;
    int len = b-a+1;
    int k = log2(len);

   // cout<<a<<","<<b<<" k: "<<k  <<" >>> " <<min(mini_LCP[a][k],mini_LCP[b-(1<<k)+1][k])<<"----\n";

    return min(mini_LCP[a][k],mini_LCP[b-(1<<k)+1][k]);
}
pii SIDES(int len,int idx){
    pii ret;
    // get lowest SA that matches SA[idx] with length>=len
    int lo=0,hi=idx,mid,ans=-1;
    while(lo<=hi){
        mid = (lo+hi)>>1;
        if(lcp(mid,idx)>=len)ans=mid,hi=mid-1;
        else lo=mid+1;
    }
    ret.first=ans;

    // get highest SA that matches SA[idx] with length>=len
    lo=idx,hi=n-1,mid,ans=-1;
    while(lo<=hi){
        mid = (lo+hi)>>1;
        if(lcp(mid,idx)>=len)ans=mid,lo=mid+1;
        else hi=mid-1;
    }
    ret.second=ans;

    return ret;
}

void computeLCP(){
	//Phi: the prev suffix of this suffix, in SA
	Phi[SA[0]] = -1;
    for(int i=1;i<n;i++)
		Phi[SA[i]] = SA[i-1];

	int L=0;
	for(int i=0;i<n;i++){
		if(Phi[i]==-1){PLCP[i]=0;continue;}

		int i1=i,i2=Phi[i];
		while(T[i1+L] == T[i2+L])L++;

		PLCP[i] = L;
		L=max(L-1,0);
	}

	// PCLP[the suffix index]
	// LCP[the suffix rank]
	for(int i=0;i<n;i++){ // i:0 to n-1, ranks of suffixes
		LCP[i] = PLCP[SA[i]];
	}
}

int get_min(int a,int b){
    int len = b-a+1;
    int k = log2(len);
    return min(mini_SA[a][k],mini_SA[b-(1<<k)+1][k]);
}
int dp[100000];
int main(){
    int tc,A,B,N;
    scanf("%d",&tc);
    while(tc--){
        scanf("%d%d%d",&N,&A,&B);
        scanf("%s",T);
        n=N;
        T[n++]='$';
        constructSA();

        computeLCP();

        for(int k=0;(1<<k)<=n;k++){
            for(int i=0;i<n;i++){
                if(!k)mini_LCP[i][k] = LCP[i];
                else{
                    mini_LCP[i][k] = min(mini_LCP[i][k-1],mini_LCP[i+(1<<(k-1))][k-1]);
                }
            }
        }

        for(int k=0;(1<<k)<=n;k++){
            for(int i=0;i<n;i++){
                if(!k)mini_SA[i][k] = SA[i];
                else{
                    mini_SA[i][k] = min(mini_SA[i][k-1],mini_SA[i+(1<<(k-1))][k-1]);
                }
            }
        }



      //  for(int i=0;i<n;i++)printf("%2d\t%s\n",SA[i],T+SA[i]);




        for(int idx=N-1;idx>=0;idx--){

            dp[idx]=1000000000;

            int lo=1,hi=N-idx,mid,len=-1;
            while(lo<=hi){
                mid = (lo+hi)>>1;
                pii sides = SIDES(mid,revSA[idx]);

                int mini_idx = get_min(sides.first,sides.second);
                int e = mini_idx+mid-1;

              // if(idx==4 && mid==4) cout<<mini_idx<<" $$ "<<sides.first<<" , "<<sides.second<<" e: "<<e<<endl;
                    //cout<<"cur_idx: "<<idx<<" mini_idx: "<<mini_idx<<"  **end:  "<<e<<"  len: "<< mid<<endl;

                if(e < idx)len=mid,lo=mid+1;
                else hi=mid-1;
            }

           // cout<<"idx: "<<idx<<" len: "<<len<<endl;
            if(len!=-1 && len*A>B)dp[idx]=dp[idx+len]+B;
            dp[idx] = min(dp[idx],dp[idx+1]+A);

        }


        printf("%d\n",dp[0]);
    }
}
