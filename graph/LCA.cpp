#ifdef IGNORE_THIS_FILE
  vector<vector<int> > a(n + 1, vector<int>(20)), v(n + 1);
  vector<int> dep(n + 1);
  auto build = [&](int u, int fa, auto&& self) -> void {
    dep[u] = dep[fa] + 1, a[u][0] = fa;
    for(int i = 1; i <= 19; ++i)
      a[u][i] = a[a[u][i - 1]][i - 1];
    for(int i: v[u]){
      if(i == fa) continue;
      self(i, u, self);
    }
  };
  auto lca = [&](int x, int y) -> int {
    if(dep[y] > dep[x]) swap(x, y);
    for(int i = 19; i >= 0; --i){
      if(dep[a[x][i]] >= dep[y]) 
        x = a[x][i];
    }
    if(x == y) return x;
    for(int i = 19; i >= 0; --i){
      if(a[x][i] != a[y][i])
        x = a[x][i], y = a[y][i];
    }
    return a[x][0];
  };
#endif


