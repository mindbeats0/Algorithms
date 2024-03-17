#include <bits/stdc++.h>
using namespace std;
const int MAXN=1e6;
char s[MAXN+5];
int match(string str,string pat){
	int n=str.size();
	int m=pat.size();
	
	// compute prefix vector
	vector<int>F(m);
	int k=0;F[0]=0;
	for(int i=1;i<m;i++){
		while(k && pat[i]!=pat[k])
			k=F[k-1];
		if(pat[i]==pat[k])F[i]=++k;
	}
	
	k=0;
	for(int i=0;i<n;i++){
		while(str[i]!=pat[k] && k)
			k=F[k-1];
			
		if(str[i]==pat[k])k++;

		if(k==m)return k;
		
	}
	return k;
	
}
int main(){
	int n;
	while(scanf("%s",s)){
		if(s[0]=='*')return 0;
		n=strlen(s);
		// compute prefix vector
		vector<int>F(n);
		int k=0;F[0]=0;
		for(int i=1;i<n;i++){
			while(k && s[i]!=s[k])
				k=F[k-1];
			if(s[i]==s[k])F[i]=++k;
		}
		
		
	
		int block = n-F[n-1];
		if(n%block==0)printf("%d\n",n/block);
		else printf("1\n");
		
		
	}
}
