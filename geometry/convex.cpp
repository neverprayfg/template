#ifdef IGNORE_THIS_FILE
  struct Point {
     ll x,y;
  };
  auto andrew = [](vector<Point>& p) -> vector<Point> {    // 传入下标从零开始的点数组，返回凸包数组
    auto cmp = [](Point &a, Point &b) -> bool {
      if(a.x != b.x) return a.x < b.x;
      return a.y < b.y;
    };
    auto cross = [](Point &u, Point &v, Point &w) -> bool {
      ll x1 = u.x - v.x, y1 = u.y - v.y;
      ll x2 = w.x - v.x, y2 = w.y - v.y;
      return x1 * y2 - x2 * y1 > 0; //如果不希望在凸包的边上有输入点。把 > 改成 >=
    };
    sort(p.begin(), p.end(), cmp);
    int n = p.size(), m = 0;
    vector<Point> res(n + 1);
    for(int i = 0; i < n; ++i){
      while(m > 1 && !cross(res[m - 1],res[m - 2], p[i])) --m;
      res[m++] = p[i];
    }
    int kk = m;
    for(int i = n - 2; i >= 0; i--){
      while(m > kk && !cross(res[m - 1], res[m - 2], p[i])) --m;
      res[m++] = p[i];
    }
    if(n > 1) --m;//凸包有m个顶点
    res.erase(res.begin() + m, res.end());
    return res;
  };
#endif