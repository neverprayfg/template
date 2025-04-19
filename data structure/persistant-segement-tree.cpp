#ifdef IGNORE_THIS_FILE
struct PTR{
    int n, tot;
    vector<int> ls, rs, sum, root;
    PTR(int _n){
        n = _n;
        tot = 0;
        ls = vector<int>(n << 6), rs = vector<int>(n << 6), sum = vector<int>(n << 6);
        root = vector<int>(n + 1);
    }
    int update(int q, int l, int r, int rt){
        int dir = ++tot;
        ls[dir] = ls[rt], rs[dir] = rs[rt];
        if(l == r){
          sum[dir] = sum[rt] + 1;
          return dir;
        }
        int mid = (l + r) >> 1;
        if(q <= mid)
          ls[dir] = update(q, l, mid, ls[dir]);
        else
          rs[dir] = update(q, mid + 1, r, rs[dir]);
        sum[dir] = sum[ls[dir]] + sum[rs[dir]];
        return dir;
    };
    int query(int q, int l, int r, int tl, int tr){
        if(l == r)
          return l;
        int mid = (l + r) >> 1;
        int sum1 = sum[ls[tr]] - sum[ls[tl]];
        if(q <= sum1)
          return query(q, l, mid, ls[tl], ls[tr]);
        else
          return query(q - sum1, mid + 1, r, rs[tl], rs[tr]);
      };    
};

#endif

