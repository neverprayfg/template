#ifdef IGNORE_THIS_FILE
struct Trie {
  static const int N = 5000100; // 预设最大节点数
  int cnt = 0;
  vector<vector<int>> node{N, vector<int>(26)};
  vector<int> isval{N};

  void insert(string& s, int len) {
    int p = 0;
    for(int i = 0; i < len; ++i){
      int c = s[i] - 'a';
      if(!node[p][c]){
        node[p][c] = ++cnt;
      }
      p = node[p][c];
    }
    ++isval[p];
  }

  int find(string& s, int len) {
    int p = 0;
    for(int i = 0; i < len; ++i){
      int c = s[i] - 'a';
      if(!node[p][c]) return 0;
      p = node[p][c];
    }
    return isval[p];
  }
};
#endif