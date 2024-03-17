int bit[MAXN+5];
void update(int idx,int val){
    for(int x = idx;x <= MAXN;x += x & -x)
        bit[x]+=val;
}

int query(int idx){
    int ret = 0;

    for(int x = idx;x > 0;x -= x & -x)
        ret += bit[x];

    return ret;
}
