
  void calc_ancestors(int N, int T[MAXN], int P[MAXN][LOGMAXN])
  {
      int i, j;

  //we initialize every element in P with -1
      for (i = 0; i < N; i++)
          for (j = 0; 1 << j < N; j++)
              P[i][j] = -1;

  //the first ancestor of every node i is T[i]
      for (i = 0; i < N; i++)
          P[i][0] = T[i];

  //bottom up dynamic programing
      for (j = 1; 1 << j < N; j++)
         for (i = 0; i < N; i++)
             if (P[i][j - 1] != -1)
                 P[i][j] = P[P[i][j - 1]][j - 1];
  }



  int get_ith_parent(int p,int ith){
      if(!ith)return p;

    int lg;
    for (lg = 0; (1 << lg) <= ith; lg++);
     lg--;


      for (int i = lg; i >= 0; i--){

          if (ith >= (1 << i))
              p = P[p][i];
              ith-=(1 << i);
      }

      return p;

}
