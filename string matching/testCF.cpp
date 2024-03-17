#include <bits/stdc++.h>
using namespace std;
const int MAXN=1e5;
char s[3][MAXN+5];
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
	
	/*string str="na";
	string pat="n";
	printf("%d\n",match(str,pat));
	return 0;
	*/
	for(int i=0;i<3;i++)
		scanf("%s",s[i]);
	int order[3]={0,1,2};
	int len=strlen(s[0])+strlen(s[1])+strlen(s[2]);
	int res=len;
	do{
		int i=order[0],j=order[1],k=order[2];
		string si=s[i],sj=s[j],sk=s[k];
		
		string temp;
		int matching=match(si,sj);
		temp=si+sj.substr(matching);
		
		matching=max(match(temp,sk),match(sk,temp));
		res=min(res,(int)temp.size()+(int)sk.size()-matching);
	}while(next_permutation(order,order+3));
	printf("%d\n",res);
}
