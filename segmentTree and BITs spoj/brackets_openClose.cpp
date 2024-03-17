// logic_max
#include <stdio.h>
#include <algorithm>
#include <assert.h>
#include <string>
#include <cstring>
#include <map>
#include <set>
#include <vector>
#include <iostream>
#include <queue>
#include <cmath>
#include <ctime>
#include <climits>
#include <iomanip>
#include <sstream>
using namespace std;
 
typedef long long LL;
#define tr(container, it)for(__typeof(container.begin()) it = container.begin(); it != container.end(); it++)
#define PB push_back
#define MP make_pair
#define REP(i,a,b) for (int i = (a); i < (int)(b); i++)
 
int GCD (int a, int b) { if (!a) return b; return GCD(b%a, a);}
 
#define X 30009
char str[X];
 
struct node {
    int close, open;
    node():close(0),open(0){}
    void init(char s) {
        if (s == '(') open = 1, close = 0;
        else close = 1, open = 0;
    }
    void merge(const node &l, const node &r) {
        int mi = min(l.open, r.close);
        open = (l.open - mi) + r.open;
        close = l.close + (r.close - mi);
    }
}tree[4*X];
 
void build(int root, int s, int e) {
    if (s == e) {
        tree[root].init(str[s]);
        return;
    }
    int mid = (s + e)/2;
    build(root*2, s, mid);
    build(root*2+1, mid+1, e);
    tree[root].merge(tree[root*2], tree[root*2+1]);
}
 
void update(int root, int s, int e, int pos) {
    if (s == e) {
        if (str[s] == '(') str[s] = ')';
        else str[s] = '(';
        tree[root].init(str[s]);
        return;
    }
    int mid = (s + e)/2;
    if (pos >= s && pos <= mid) update(root*2, s, mid, pos);
    else update(root*2+1, mid+1, e, pos);
    tree[root].merge(tree[root*2], tree[root*2+1]);
}
 
int main() {
    clock_t startTime = clock();
    ios_base::sync_with_stdio(false);
 
    int test = 10;
    while (test--) {
        int n; scanf("%d", &n);
        scanf("%s", str);
        build(1, 0, n-1);
        int m; scanf("%d", &m);
        printf("Test %d:\n", 10-test);
        while(m--) {
            int q; scanf("%d", &q);
            if (!q) {
                int ans = !tree[1].close && !tree[1].open;
                if (ans) puts("YES");
                else puts("NO");
            } else {
                --q;
                update(1, 0, n-1, q);
            }
        }
    }
 
    clock_t endTime = clock();
    cerr<<"\nTime:"<< double(endTime - startTime) / CLOCKS_PER_SEC <<" seconds\n" ;
    return 0;
}
