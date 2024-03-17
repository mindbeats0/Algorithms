#include <bits/stdc++.h>
using namespace std;
const int MAXN=1e3;
char s[MAXN+5];
int z[MAXN+5],n;
void computeZ(){
	int L = 0, R = 0;
	for (int i = 1; i < n; i++) {
	  if (i > R) {
		L = R = i;
		while (R < n && s[R-L] == s[R]) R++;
		z[i] = R-L; R--;
	  } else {
		int k = i-L;
		if (z[k] < R-i+1) z[i] = z[k];
		else {
		  L = i;
		  while (R < n && s[R-L] == s[R]) R++;
		  z[i] = R-L; R--;
		}
	  }
	}

}
int main(){
	
	  /*char str1[]="Sample string";
	  
	  strcpy (str1,str1+2);
	  printf("%s ***\n",str1);
	  
	  char str2[40];
	  
	  char str3[40];
	  strcpy (str2,str1);
	  strcpy (str3,"copy successful");
	  printf ("str1: %s\nstr2: %s\nstr3: %s\n",str1,str2,str3);
	*/
	
	int tc;
	scanf("%d",&tc);
	while(tc--){
		scanf("%s",s);
		int N = strlen(s);
		int ans = N*(N+1)/2;
		
		for(int i=0;i<N;i++){
			n = strlen(s);
			computeZ();
			int mx=0;
			for(int j=0;j<n;j++)
				mx = max(mx,z[j]); 
			ans -= mx;
		//	if(i==n-1)printf("%d ###\n",mx);
			strcpy(s,s+1);
			memset(z,0,sizeof z);
			
		}
		printf("%d\n",ans);
	}
	

}
