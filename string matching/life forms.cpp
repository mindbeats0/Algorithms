#include <bits/stdc++.h>
#include <locale>
#include <stdio.h>
#include <cctype>
using namespace std;
const int MAXN=1e6;
string T;
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
void computeLCP(){ //LCP[i] = longest common prefix between SA[i] and SA[i-1]
	//Phi: the prev suffix of this suffix, in SA
	Phi[SA[0]] = -1;
    for(int i=1;i<n;i++)
		Phi[SA[i]] = SA[i-1];

	int L=0;
	for(int i=0;i<n;i++){
		if(Phi[i]==-1){PLCP[i]=0;continue;}

		int i1=i,i2=Phi[i];
		while(T[i1+L]!='#' && T[i1+L] == T[i2+L])L++;

		PLCP[i] = L;
		L=max(L-1,0);
	}

	// PCLP[the suffix index]
	// LCP[the suffix rank]
	for(int i=0;i<n;i++){ // i:0 to n-1, ranks of suffixes
		LCP[i] = PLCP[SA[i]];
	}
}
char buff[1010];
int k;
int order[MAXN+5];


int Tree[4*MAXN];
void build(int idx,int s,int e){
    if(s==e){
        Tree[idx]=LCP[s];
        return ;
    }
    build(idx*2,s,(s+e)/2);
    build(idx*2+1,(s+e)/2+1,e);
    Tree[idx] = min(Tree[idx*2],Tree[idx*2+1]);
}
int get(int idx,int qs,int qe,int s,int e){
    if(e<qs || s>qe)return 10000;
    if(s==e){
        return Tree[idx];
    }
    return min (get(idx*2,qs,qe,s,(s+e)/2),get(idx*2+1,qs,qe,(s+e)/2+1,e));
}



int lcp(int a,int b){
    a++;

    int ret =  get(1,a,b,0,n-1);
    //cout<<a<<"  $$ "<<b<<"   "<<ret<<endl;
    return ret;

}


vector<int>all[1010];
int solve(){
    for(int i=0;i<=1005;i++)all[i].clear();

    int res=0,idx=-1;
    unordered_map<int,int>mp;
    int i=0,j=0;mp[order[SA[0]]]=1;


    int maxi=0;

    while( i<=j &&j<n){
        //cout<<i<<"  ,  "<<j<<" sz: "<<mp.size()<<endl;
        if(mp.size()>= k/2+1){
            int ret = lcp(i,j);
            all[ret].push_back(SA[i]);
            if(ret>maxi)maxi=ret;

            mp[order[SA[i]]]--;
            if(!mp[order[SA[i]]])mp.erase(order[SA[i]]);
            i++;
        }
        else {
            j++;
            if(j<n)mp[order[SA[j]]]++;

        }
    }

    return maxi;
}

int main(){


    bool f=0;
    while(scanf("%d",&k),k){
        if(f)printf("\n");
        f=1;

        scanf("%d",&k);


        if(k==1){
            scanf("%s",buff);
            printf("%s\n",buff);
            continue;
        }

        T="";
        for(int i=0;i<k;i++){
            scanf("%s",buff);
            T+=buff;
            T+='#';

        }
        T+='$';
        n=T.size();


        int idx = 0;
        for(int i=0;i<n;i++){
            order[i]=idx;

            //cout<<i<<"  "<<idx<<endl;

            if(T[i]<'a' || T[i]>'z')idx++;

        }
       //printf("!!%s!!\n",T.c_str());
        buildSA();
        computeLCP();
        build(1,0,n-1);


      //  for(int i=0;i<n;i++)
        //    printf("%2d\t%s\t%d\n",SA[i],T.substr(SA[i]).c_str(),LCP[i]);

          int  len = solve();
          if(!len)printf("?\n");
          else{
            unordered_set<string>S;
            for(int i=0;i<all[len].size();i++){
                if(S.count(T.substr(all[len][i],len)))continue;
                printf("%s\n",T.substr(all[len][i],len).c_str());
                S.insert(T.substr(all[len][i],len));
            }
          }

    }


}

