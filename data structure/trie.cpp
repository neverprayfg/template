#ifdef IGNORE_THIS_FILE
  int cnt = 0;
  vector<vector<int> > node(1, vector<int>(26));
  vector<int> isval(1);
  auto insert = [&](string& s, int len) -> void {
    int p = 0;
    for(int i = 0; i < len; i++){
      int c = s[i] - 'a';
      if(!node[p][c]){
        node.push_back(vector<int>(26, 0));
        isval.push_back(0);
        node[p][c] = ++cnt;
      }
      p = node[p][c];
    }
    ++isval[p];
  };
  auto find = [&](string& s, int len) -> int {
    int p = 0;
    for(int i = 0; i < len; i++){
      int c = s[i] - 'a';
      if(!node[p][c]) return 0;
      p = node[p][c];
    }
    return isval[p];
  };
#endif