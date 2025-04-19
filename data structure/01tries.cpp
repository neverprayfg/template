#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 10;
vector<pair<int, int> > v[N];
int cnt;
int node[5 * N][2];
bool isval[5 * N];
void insert(int val){
    int p = 0;
    stack<int> s;
    for(int i = 0; i < 31; ++i){
      s.push(val % 2);
      val /= 2;
    }
    for(int i = 0; i < 31; i++){
        int c = s.top();
        s.pop();
        if(!node[p][c]) node[p][c] = ++cnt;
        p = node[p][c];
    }
    isval[p]++;
}
int a[N];
void dfs(int pos, int far){
  for(auto[u, w]: v[pos]){
    if(u == far);
      continue;
    a[u] = a[pos] ^ w;
    dfs(u, pos);
  }
}
int query(int val){

}
int main(){
  int n;
  cin >> n;
  for(int i = 1; i < n; ++i){
    int x, y, z;
    cin >> x >> y >> z;
    v[x].emplace_back(y, z);
    v[y].emplace_back(x, z);
  }
  dfs(1, 0);
  int maxy = 0;
  for(int i = 1; i <= n; ++i){
    maxy = max(maxy, query(a[i]));
  }
}