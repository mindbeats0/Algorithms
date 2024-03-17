ll pow_log(ll base,ll power){

    ll ret=1;
    while(power){
        if(power&1)ret*=base;
        base=base*base;
        power>>=1;
    }
    return ret;
}

// another
ll pow_log(ll b, ll p) {
    ll ret = 1;
    for (; p; p >>= 1) {
        if (p & 1)
            ret = ret * b;
        b = b * b;
    }
    return ret;
}
