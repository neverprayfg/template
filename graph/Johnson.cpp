#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll N = 3e3 + 10;
ll h[N];
struct edge{
  ll u;
  ll w;
  ll t;
};
vector<edge> v;
struct node{
  ll u;
  ll t;
  bool operator<(const node& other) const{
    return t < other.t;
  }
  bool operator>(const node& other) const{
    return t > other.t;
  } 
};
priority_queue<node, vector<node>, greater<node>> q;
vector<node> s[N];
bool bellmanford(ll n){
  bool flag = false;
  for(ll i = 1; i <= n; ++i){
    flag = false;
    for(auto j: v){
      if(h[j.w] > h[j.u] + j.t){
        h[j.w] = h[j.u] + j.t;
        flag = true;
      }
    }
    if(!flag){
      break;
    }
  }
  return flag;
}
ll w[N][N];
void  Dijskal(ll st, ll n){
  vector<ll> isval(n + 10);
  w[st][st] = 0;
  priority_queue<node, vector<node>, greater<node>> q;
  q.emplace(st, 0);
  while(!q.empty()){
    auto u = q.top();
    q.pop();
    if(isval[u.u])
      continue;
    isval[u.u] = 1;
    for(auto i: s[u.u]){
      if(w[st][i.u] > w[st][u.u] + i.t){
        w[st][i.u] = w[st][u.u] + i.t;
        q.emplace(i.u, w[st][i.u]);
      }
    } 
  }
  for(int i = 1; i <= n; ++i){
    w[st][i] = w[st][i] - h[st] + h[i];
  }
}
int main(){
  ll n, m;
  cin >> n >> m;
  for(ll i = 0; i < m; ++i){
    ll u, w, t;
    cin >> u >> w >> t;
    v.emplace_back(u, w, t);
  }
  for(ll i = 1; i <= n; ++i){
    v.emplace_back(0, i, 0);
  }
  if(bellmanford(n)){
    cout << -1;
    return 0;
  }
  for(auto& i: v){
    auto&[u, w, t] = i;
    t += h[u] - h[w];
  }
  for(ll i = 0; i < m; ++i){
    auto&[u, w, t] = v[i];
    s[u].emplace_back(w, t);
  }
  memset(w, 0x3f, sizeof(w));
  for(ll i = 1; i <= n; ++i){
    Dijskal(i, n);
  }
  for(ll i = 1; i <= n; ++i){
    ll sum = 0;
    for(ll j = 1; j <= n; ++j){
      if(w[i][j] > ll(1e9)){
        sum += j * ll(1e9);
      }
      else
        sum += w[i][j] * j;
    }
    cout << sum << '\n';
  }
}