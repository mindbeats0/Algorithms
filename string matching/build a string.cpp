#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> ii ;
#define INF 1e9
const int MAXN=3e4;
char T[MAXN+5];
int n;
int SA[MAXN+5],tempSA[MAXN+5];
int RA[MAXN+5],tempRA[MAXN+5];
int c[MAXN+5];
int Phi[MAXN+5],PLCP[MAXN+5],LCP[MAXN+5];

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

	// RA[i]: is the rank of string beginning at index i with that current length

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

int Tree[4*MAXN];
void build_segTree(int idx=1,int s=0,int e=n-1){
    if(s==e){
        Tree[idx] = SA[s];
        return ;
    }
    int mid = (s+e)>>1;
    build_segTree(idx*2,s,mid);
    build_segTree(idx*2+1,mid+1,e);
    Tree[idx] = min(Tree[idx*2],Tree[idx*2+1]);
}
int query_segTree(int qs,int qe, int idx=1,int s=0,int e=n-1){
    if(s>=qs && e<=qe)
        return Tree[idx];
    if(s>qe || e<qs)return INF;
    int mid = (s+e)>>1;

    return min ( query_segTree(qs,qe,idx*2,s,mid) , query_segTree(qs,qe,idx*2+1,mid+1,e) );

}
int get_lcp(int i,int j){

    int len=0;
   // printf("%d %d $$\n",i,j);
    while(i<n && j<n && T[i]==T[j])
        i++,j++,len++;


     //printf("%d %d %d ###\n",i,j,len)   ;
    return len;
}
ii get_range(int idx,int len){
    // find lower bound in SA
    int lo=0,hi=n-1,mid,ans1=-1,ans2;
    while(lo<=hi){
        mid = (lo+hi)>>1;

        int i1=SA[mid],i2=idx;
        int lcp = get_lcp(i1,i2);
        if(lcp >= len)ans1=mid,hi=mid-1;
        else {
            if(T[i1+lcp] > T[i2+lcp])hi = mid-1;
            else lo = mid+1;
        }
    }
    if(ans1==-1)return ii(-1,-1);


    // find upper bound in SA
    lo=0,hi=n-1,mid;
    while(lo<=hi){
        mid = (lo+hi)>>1;

        int i1=SA[mid],i2=idx;
        int lcp = get_lcp(i1,i2);
        if(lcp >= len)ans2=mid,lo=mid+1;
        else {
            if(T[i1+lcp] > T[i2+lcp])hi = mid-1;
            else lo = mid+1;
        }
    }
    return ii(ans1,ans2);


}

bool exist(int idx,int len){
    ii suffices = get_range(idx,len);

    if(suffices==ii(-1,-1))return false;

    int i=query_segTree(suffices.first,suffices.second);

    if(i +len <= idx )return true;
    return false;
}
int main(){

    int tc,A,B;
    scanf("%d",&tc);

    while(tc--){
        scanf("%d%d%d",&n,&A,&B);
        scanf("%s",T);
        T[n++]='$';
        buildSA();
        computeLCP();

        build_segTree();
       // for(int i=0;i<n;i++)
        //    printf("%2d\t%s\t%d\n",SA[i],T+SA[i],LCP[i]);
        // printf("----------------\n");


        int res = 0;
        int i=0;
        while(i<n-1){

            int lo=1,hi=min(i,n-1-i),mid;
            int LEN=0;
            while(lo<=hi){
                mid = (lo+hi)>>1;

                bool ex = exist(i,mid);


                if(ex)LEN=mid, lo=mid+1 ;
                else hi=mid-1;

            }


            if(!LEN)res+=A,i++;
            else res += min(A*LEN,B), i+=LEN;


        }
        printf("%d\n",res);
    }
    return 0;
}

