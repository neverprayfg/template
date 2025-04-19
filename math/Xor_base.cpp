#ifdef IGNORE_THIS_FILE
auto insert = [](ll x, vector<ll>& a) -> void {
  for(int i = 63; i >= 0; --i){
    if(!((x >> i) & 1)) continue;
    if(a[i]) x ^= a[i];
    else{
      for(int j = 0; j < i; ++j){
        if((x >> j) & 1) 
          x ^= a[j];
      }
      for(int j = i + 1; j <= 63; ++j){
        if((a[j] >> i) & 1) 
          a[j] ^= x;
      }
      a[i] = x;
    }
  }
};
#endif