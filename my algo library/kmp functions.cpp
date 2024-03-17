
vector<int> computePrefix(string pat){
	int m=(int)pat.size();
	vector<int>longestPrefix(m);

	int k=0;
	for(int i=1;i<m;i++){
		while(k>0 && pat[i]!=pat[k])k=longestPrefix[k-1];
		if(pat[i]==pat[k])longestPrefix[i]=++k;
	}
	return longestPrefix;
}

void KMP(string str,string pat){
	int n=(int)str.size();
	int m=(int)pat.size();
	vector<int>longestPrefix=computePrefix(pat);

	int k=0;
	for(int i=0;i<n;i++){
       // instead of k=0
		while(k>0 && str[i]!=pat[k]) k=longestPrefix[k-1];

		if(str[i]==pat[k])k++;

		if(k==m){// we made a match
			cout<<i-m+1<<"\n";
			k=longestPrefix[k-1];
		}
	}

}
