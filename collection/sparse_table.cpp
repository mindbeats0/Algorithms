//SPARCE TABLE

// DP O(N^2)
  void process1(int M[MAXN][MAXN], int A[MAXN], int N)
  {
      int i, j;
      for (i =0; i < N; i++)
          M[i][i] = i;
      for (i = 0; i < N; i++)
          for (j = i + 1; j < N; j++)
              if (A[M[i][j - 1]] < A[j])
                  M[i][j] = M[i][j - 1];
              else
                  M[i][j] = j;
  }
  //--------------------------------------------------------------------
  // sparse tree
   void process2(int M[MAXN][LOGMAXN], int A[MAXN], int N)
  {
      int i, j;

      //initialize M for the intervals with length 1
      for (i = 0; i < N; i++)
          M[i][0] = i;
      //compute values from smaller to bigger intervals
      for (j = 1; (1<<j) <= N; j++)
          for (i = 0; i + (1 << j) - 1 < N; i++)
              if (A[M[i][j - 1]] < A[M[i + (1 << (j - 1))][j - 1]]) // if first half bigger than the second half
                  M[i][j] = M[i][j - 1];
              else
                  M[i][j] = M[i + (1 << (j - 1))][j - 1];
  }
  //--------------------------------------------------------------------
/*
complexities:
   sparse table <O(N logN),O(1)>
   segment tree <O(N),O(logN)>
*/
