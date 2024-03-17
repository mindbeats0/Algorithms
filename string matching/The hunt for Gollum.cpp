#include <bits/stdc++.h>
using namespace std;
int F[2010];
char pat[2010][2010],s[2010][2010];
bool iseq(char pat[][2010],int rp,int cp,int lenp,char s[][2010],int rs,int cs,int lens){
	
	while(rp<lenp && rs<lens){
		if(pat[rp][cp] != s[rs][cs])break;
		rp++; rs++;
	}
	
	return rp==lenp;
}
int main(){
	int n1,n2,m1,m2;
	scanf("%d%d",&m1,&m2);
	for(int i=0;i<m1;i++)
		scanf("%s",pat[i]);
		
	scanf("%d%d",&n1,&n2);
	for(int i=0;i<n1;i++)
		scanf("%s",s[i]);

 		
	// compute prefix aray
	int k=0;
	for(int i=1;i<m2;i++){
		while(k && !iseq(pat,0,k,m1,pat,0,i,m1))
			k=F[k-1];
		if(iseq(pat,0,k,m1,pat,0,i,m1))F[i]=++k;
	}
	
	
	vector<pair<int,int> >res;
	for(int i=0;i<n1;i++){
	    // try to begin matching from each row in the string S	
	    
		int k=0;
		for(int j=0;j<n2;j++){
			while(k && !iseq(pat,0,k,m1,s,i,j,n1))
				k=F[k-1];
			if(iseq(pat,0,k,m1,s,i,j,n1))++k;
			
			if(k==m2){
				res.push_back(make_pair(i,j-m2+1));
				k=F[k-1];
			}
		}
		
		
	}
	for(int i=0;i<res.size();i++)printf("(%d,%d)\n",res[i].first+1,res[i].second+1);
	if(res.size()==0)printf("NO MATCH FOUND...\n");
	
}

