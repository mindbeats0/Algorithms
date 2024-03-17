#include <bits/stdc++.h>
using namespace std;
struct node{
	long long wid,len;
	node(){}
	node(long long wid,long long len):wid(wid),len(len){}
};
const int MAXN=50000;
const long long INF=1000000000000000;
node input[MAXN+5];
vector<node >land;
long long dp[MAXN+5];
bool cmp(const node&a,const node&b){
	if(a.wid!=b.wid)return a.wid>b.wid;
	return a.len>b.len;
}
int main(){
	//freopen("acquire.10.in","r",stdin);
	int N;
	cin>>N;
	for(int i=0;i<N;i++){
		cin>>input[i].wid>>input[i].len;
	}
	sort(input,input+N,cmp);

	long long prev=0;
	for(int i=0;i<N;i++){


		if(input[i].len<=prev)continue;

        cout<<input[i].wid<<","<<input[i].len<<endl;
		land.push_back(input[i]);
		prev=input[i].len;
	}
	return 0;
	N=(int)land.size();

	cout<<N<<endl;
	for(int i=0;i<N;i++)
        cout<<land[i].wid<<","<<land[i].len<<endl;
    cout<<endl;



	vector<pair<long long,long long> >lines;
	vector<long long>start;
	for(int ind=N-1;ind>=0;ind--){


		int i=(int)lines.size()-1;
		int x=0;
		long long  m1=land[ind].len,c1=dp[ind+1];
		while(i>=0){
			long long m2=lines[i].first,c2=lines[i].second;
			x=ceil((double)(c1-c2)/(double)(m2-m1));
			if(x>start[i])break;

			lines.pop_back();
			start.pop_back();
			i--;
		}

		lines.push_back(make_pair(m1,c1));
		start.push_back(x);


		long long X=land[ind].wid;

		 if(ind==N-1){
			 dp[ind]=land[ind].len*land[ind].wid;
		 }
		 else{
			 int idx=upper_bound (start.begin(), start.end(), X)-start.begin()-1;
			 dp[ind]=lines[idx].first*X+lines[idx].second;
		}
	}


	cout<<dp[0]<<"\n";
}
