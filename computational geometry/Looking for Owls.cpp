//https://codeforces.com/contest/350/problem/D
#include<bits/stdc++.h>
using namespace std;
 
struct fraction {
	long long a, b;
 
	fraction() {
		a = b = 0;
	}
 
	fraction(long long aa, long long bb) {
		if (!bb)
			a = 1, b = 0;
		else if (!aa)
			a = 0, b = 1;
		else {
			long long g = __gcd(abs(aa), abs(bb));
			aa /= g, bb /= g;
			if (bb < 0)
				aa *= -1, bb *= -1;
			a = aa, b = bb;
		}
	}
 
	const bool operator <(const fraction& rhs) const {
		return a * rhs.b < b * rhs.a;
	}
 
	const bool operator ==(const fraction& rhs) const {
		return !(*this < rhs) && !(rhs < *this);
	}
 
	const bool operator <=(const fraction& rhs) const {
		return !(rhs < *this);
	}
 
	const bool operator !=(const fraction& rhs) const {
		return *this < rhs || rhs < *this;
	}
 
	fraction& operator =(const fraction& rhs) {
		a = rhs.a, b = rhs.b;
		return *this;
	}
 
	fraction operator +(const fraction& rhs) const {
		return fraction(a * rhs.b + b * rhs.a, b * rhs.b);
	}
 
	fraction& operator +=(const fraction& rhs) {
		return *this = *this + rhs;
	}
 
	fraction operator -(const fraction& rhs) const {
		return fraction(a * rhs.b - b * rhs.a, b * rhs.b);
	}
 
	fraction& operator -=(const fraction& rhs) {
		return *this = *this - rhs;
	}
 
	fraction operator *(const fraction& rhs) const {
		return fraction(a * rhs.a, b * rhs.b);
	}
 
	fraction& operator *=(const fraction& rhs) {
		return *this = *this * rhs;
	}
 
	fraction operator /(const fraction& rhs) const {
		return fraction(a * rhs.b, b * rhs.a);
	}
 
	fraction& operator /=(const fraction& rhs) {
		return *this = *this / rhs;
	}
};
 
 
 
struct Line{
    fraction m,c;
    void getLine(int x1,int y1,int x2,int y2){
        m = fraction(y1-y2,x1-x2);
        if(!m.b)c=fraction(x1,1);
        else c = fraction(y1,1)-m*fraction(x1,1);
 
 
 
    }
}line[300005];
struct Circle{
    int x,y,r;
}circle[1505];
 
 
map<pair<fraction,fraction> , vector<pair<int,int> >  >mp;
 
int main(){
    int n,m,x1,y1,x2,y2,x,y,r;
    scanf("%d%d",&n,&m);
    for(int i=0;i<n;i++){
        scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
 
        x1*=2,y1*=2,x2*=2,y2*=2;
        line[i].getLine(x1,y1,x2,y2);
 
        if(line[i].m.b){
            mp[make_pair(line[i].m,line[i].c)] .push_back(make_pair(min(x1,x2),-1));
            mp[make_pair(line[i].m,line[i].c)] .push_back(make_pair(max(x1,x2),1));
        }
        else{
 
            mp[make_pair(line[i].m,line[i].c)] .push_back(make_pair(min(y1,y2),-1));
            mp[make_pair(line[i].m,line[i].c)] .push_back(make_pair(max(y1,y2),1));
        }
 
 
    }
    for(int i=0;i<m;i++){
         scanf("%d%d%d",&circle[i].x,&circle[i].y,&circle[i].r);
         circle[i].x*=2; circle[i].y*=2; circle[i].r*=2;
 
    }
 
 
    map<pair<fraction,fraction> , vector<pair<int,int> >  >::iterator it;
    map<pair<fraction,fraction> , vector<pair<int,int> > >acc;
    // first: include  second: exclude
    for(it=mp.begin();it!=mp.end();it++){
        sort(it->second.begin(),it->second.end());
        acc[it->first].resize(it->second.size());
        int active_inc=0,active_ex=0;
        for(int i=0;i<acc[it->first].size();i++){
 
            if(i && mp[it->first][i-1].first < mp[it->first][i].first)active_inc=active_ex;
 
 
            if(mp[it->first][i].second==-1)active_inc++,active_ex++;
            if(mp[it->first][i].second==1)active_ex--;
 
            acc[it->first][i].first=active_inc;
            acc[it->first][i].second=active_ex;
 
        }
    }
 
 
 
    long long res=0;
    for(int i=0;i<m;i++){
        for(int j=i+1;j<m;j++){
 
            x1=circle[i].x,y1=circle[i].y;
            x2=circle[j].x,y2=circle[j].y;
 
            if(circle[i].r!=circle[j].r)continue;
 
            if( (abs(x1-x2)*abs(x1-x2)+abs(y1-y2)*abs(y1-y2)) <= 4*circle[i].r*circle[i].r)continue;
            int midx=(x1+x2)/2,midy=(y1+y2)/2;
 
 
            fraction slope(y1-y2,x1-x2);
            swap(slope.a,slope.b);
            slope.a*=-1;
            slope = fraction(slope.a,slope.b);
            fraction intersect = slope.b?fraction(midy,1)-slope*fraction(midx,1):fraction(midx,1);
 
 
             if(!mp.count(make_pair(slope,intersect)))continue;
            int idx = upper_bound(mp[make_pair(slope,intersect)].begin(),mp[make_pair(slope,intersect)].end(),
                                  make_pair(!slope.b?midy:midx,2))- mp[make_pair(slope,intersect)].begin() - 1 ;
 
 
            if(idx<0)continue;
 
             if(mp[make_pair(slope,intersect)][idx].first == (!slope.b?midy:midx))
                res += acc[make_pair(slope,intersect)][idx].first;
            else
                res += acc[make_pair(slope,intersect)][idx].second;
 
        }
    }
 
    printf("%I64d\n",res);
 
}