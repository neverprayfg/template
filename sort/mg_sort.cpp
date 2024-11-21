#ifdef IGNORE_THIS_TILE
  void mg_sort(int l, int r, vector<int>& a) {
    if(l == r)
      return;
    int mid = (l + r) >> 1;
    mg_sort(l, mid, a);
    mg_sort(mid + 1, r, a);
    auto merge = [](int l, int r, int mid, vector<int>& a) -> void {
      vector<int> b;
      int lp = l;
      int rp = r + 1;
      while(lp <= mid && rp <= r){
        if(a[lp] < a[rp])
          b.push_back(a[lp++]);
        else  
          b.push_back(a[rp++]);
      }
      while(lp <= mid)
        b.push_back(a[lp++]);
      while(rp <= r)
        b.push_back(a[rp++]);
      copy(b.begin(), b.end(), a.begin() + l);
    };
    merge(l, r, mid, a);
  };
#endif