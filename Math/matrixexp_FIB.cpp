//a sample C++ code to compute the N-th term of Fibonacci sequence, modulo 1,000,000,007.
//http://fusharblog.com/solving-linear-recurrence-for-programming-contest/

#include <vector>
#define REP(i,n) for (int i = 1; i <= n; i++)

using namespace std;

typedef long long ll;

typedef vector<vector<ll> > matrix;

const ll mod = 1000000007;

const int K = 2;

// computes A * B

matrix mul(matrix X, matrix Y){
     // RxQ  * QxC  = R*C
    int R = X.size();
    int Q = Y.size();
    int C = Y[0].size();

    matrix Z(R, vector<ll>(C));

    for(int i=0;i<R;i++)
        for(int j=0;j<C;j++)
            for(int k=0;k<Q;k++)
                Z[i][j] = (Z[i][j] + X[i][k]*Y[k][j])%mod;


    return Z;

}

// computes A ^ p
matrix matrixPow(matrix A, int p){
    if (p == 1)
        return A;

    if (p % 2)
        return mul(A, matrixPow(A, p-1));

    matrix temp = matrixPow(A, p/2);

    return mul(temp, temp);

}

int fib(int N){

    // create vector F1

    vector<ll> F1(K+1);

    F1[1] = 1;

    F1[2] = 1;

    // create matrix T

    matrix T(K+1, vector<ll>(K+1));

    T[1][1] = 0, T[1][2] = 1;

    T[2][1] = 1, T[2][2] = 1;



    // raise T to the (N-1)th power

    if (N == 1)

        return 1;

    T = matrixPow(T, N-1);

    // the answer is the first row of T . F1

    ll res = 0;

    REP(i, K)
        res = (res + T[1][i] * F1[i]) % mod;

    return res;

}
