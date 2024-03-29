#include <cstdio>
#include <cstring>
#define LSOne(S) (S & (-S))
using namespace std;

typedef long long ll;

ll B1[100005], B2[100005];

int N;

ll query(ll* ft, int b)	{
	ll sum = 0;
	for (; b; b -= LSOne(b)) sum += ft[b];
	return sum;
}
ll query(int b) {
    return query(B1, b) * b - query(B2, b);
}
ll range_query(int i, int j)    {
    return query(j) - query(i - 1);
}
void update(ll* ft, int k, ll v) {
	for (; k <= N; k += LSOne(k)) ft[k] += v;
}
void range_update(int i, int j, ll v)	{
	update(B1, i, v);
	update(B1, j + 1, -v);
	update(B2, i, v * (i - 1));
	update(B2, j + 1, -v * j);
}

int main()  {
	int T, C, p, q, cmd;
	ll v;

	scanf("%d", &T);
	while (T--)	{
		// C -> No. of operations
		scanf("%d %d", &N, &C);
		memset(B1, 0, (N+1) * sizeof(ll));
		memset(B2, 0, (N+1) * sizeof(ll));
		while (C--)	{
			scanf("%d %d %d", &cmd, &p, &q);
			// cmd is 0 for a range update and 1 for a range query
			if (cmd == 0)   {
                		scanf("%lld", &v);
                		range_update(p, q, v);
			} else
                		printf("%lld\n", range_query(p, q));
		}
	}

    return 0;
}
