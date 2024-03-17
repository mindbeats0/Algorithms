#include <bits/stdc++.h>
using namespace std;
const int MAXN=1e5;
const int MAXLG=20;
struct entry{
	int fst,snd,idx;
	const bool operator <(const entry&other)const{
		if(fst!=other.fst)return fst<other.fst;
		return snd<other.snd;
	}
}L[MAXN+5];
int P[MAXLG+5][MAXN+5];
char s[MAXN+5],pat[1010];
int N;
int get_order(char c){
	int rnk = tolower(c)-'a';
	if(isupper(c))return rnk;
	return 26+rnk;
	
}
void suffix_Array(){
	for(int i=0;i<N;i++)
		P[0][i] = get_order(s[i]);
		
	for(int stp=1;1<<stp <=N;stp++){
		for(int i=0;i<N;i++){
			L[i].fst = P[stp-1][i];
			L[i].snd = (i+(1<<stp)<N)?P[stp-1][i+(1<<stp)]:-1;
			L[i].idx = i;
		}
		sort(L,L+N);
		for(int i=0;i<N;i++){
			if(i && L[i].fst==L[i-1].fst && L[i].snd==L[i-1].snd)P[stp][L[i].idx] = P[stp][L[i-1].idx];
			else P[stp][L[i].idx] = i;
		}	
	}
}
bool is_substr(string pat){
	int lo=0,hi=N-1,mid;
	while(lo<=hi){
		mid = (lo+hi)>>1;
		
		int st=L[mid].idx;
		int comp=0,i;
		for(i=0;i<pat.size();i++){	
		
			if(pat[i]<s[st+i]){comp=-1; break;}
			else if(pat[i]>s[st+i]){comp=1; break;}
		}
		
		if(comp==-1)hi=mid-1;
		if(comp==1)lo=mid+1;
		if(comp==0 && i==pat.size())return true;
		if(comp==0 && i<pat.size())lo=mid+1;
		
	}
	return false;
}
int main(){
	
	int tc,q;
	scanf("%d",&tc);
	while(tc--){
		scanf("%s",s);
		N=strlen(s);
		suffix_Array();
		
		
		// PRINT ALL THE SUFFIXES
		/* 
		int stp;
		for(stp=1; 1<<stp <=N;stp++);stp--;
		
		for(int i=0;i<N;i++){
			int st=L[i].idx;
		//	printf("%d**\n",st);
			for(int j=st;j<N;j++)
				printf("%c",s[j]);
			printf("\n");
		}
		*/
		scanf("%d",&q);
		for(int i=0;i<q;i++){
			scanf("%s",pat);
			
			printf("%c\n",is_substr((string)pat)?'y':'n');
			
		}
	}
	return 0;
}
