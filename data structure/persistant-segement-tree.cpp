#ifdef IGNORE_THIS_FILE
  int n, tot = 0;
  vector<int> ls(n << 5), rs(n << 5), sum(n << 5);
  vector<int> root(n + 1);
  auto update = [&](int q, int l, int r, int rt, auto&& self) -> int {
    int dir = ++tot;
    ls[dir] = ls[rt], rs[dir] = rs[rt];
    if(l == r){
      sum[dir] = sum[rt] + 1;
      return dir;
    }
    int mid = (l + r) >> 1;
    if(q <= mid)
      ls[dir] = self(q, l, mid, ls[dir], self);
    else
      rs[dir] = self(q, mid + 1, r, rs[dir], self);
    sum[dir] = sum[ls[dir]] + sum[rs[dir]];
    return dir;
  };
  auto query = [&](int q, int l, int r, int tl, int tr, auto&& self) -> int {
    if(l == r)
      return l;
    int mid = (l + r) >> 1;
    int sum1 = sum[ls[tr]] - sum[ls[tl]];
    if(q <= sum1)
      return self(q, l, mid, ls[tl], ls[tr], self);
    else
      return self(q - sum1, mid + 1, r, rs[tl], rs[tr], self);
  };
#endif
