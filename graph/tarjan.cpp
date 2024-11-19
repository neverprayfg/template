#ifdef IGNORE_THIS_FILE
  int dfn_cnt = 0, scc_cnt = 0;
  vector<int> dfn(n + 1), low(n + 1), scc_id(n + 1); 
  stack<int> s;
  vector<bool> in_stack(n + 1);
  vector<vector<int> > v(n + 1), scc(n + 1);
  // scc_id是每个节点所属于的scc编号, scc是这个编号下的所有节点
  auto tarjan = [&](int u, auto&& self) -> void {
    dfn[u] = low[u] = ++dfn_cnt;
    s.push(u), in_stack[u] = true;
    for(int i: v[u]){
      if(!dfn[i]){
        self(i, self);
        low[u] = min(low[u], low[i]);
      }
      else if(in_stack[i])
        low[u] = min(low[u], dfn[i]);
    }
    if(dfn[u] == low[u]){
      int tp;
      ++scc_cnt;
      do{
        tp = s.top();
        scc_id[tp] = scc_cnt;
        scc[scc_cnt].push_back(tp);
        in_stack[tp] = false;
        s.pop();
      } while(tp != u);
    }
  };
#endif