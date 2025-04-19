#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 2e5 + 10;
ll fa[N], ht[N], top[N];
pair<ll, ll> son[N];
ll len[N];
vector<pair<ll, ll> > v[N];


void dfs1(ll u, ll far){
  fa[u] = far;
  for(auto [i, w]: v[u]){
    if(i == far)
      continue;
    dfs1(i, u);
    ht[u] = max(ht[u], ht[i] + w);
    if(ht[son[u].first] + son[u].second < ht[i] + w)
      son[u] = {i, w};
  }
} 

ll ans[N];
void dfs2(ll u, ll head){
  top[u] = head;
  if(!son[u].first){
    return;
  }
  len[son[u].first] = len[u] + son[u].second;
  dfs2(son[u].first, head);
  for(auto [i, w]: v[u]){
    if(i == fa[u] || son[u].first == i)
      continue;
    len[i] = w;
    dfs2(i, i);
  }
}
int main(){
  ll n;
  cin >> n;
  for(ll i = 1; i < n; ++i){
    ll x, y, z;
    cin >> x >> y >> z;
    v[x].emplace_back(y, z);
    v[y].emplace_back(x, z);
  }
  dfs1(1, 0);
  dfs2(1, 1);
  for(ll i = 1; i <= n; ++i){
    ans[top[i]] = max(ans[top[i]], len[i]);
  }
  ll sum = 0;
  sort(ans + 1, ans + 1 + n, [](const auto x, const auto y){return x > y;});
  for(ll i = 1; i <= n; ++i){
    sum += ans[i] * 2ll;
    cout << sum << ' ';
  }

}