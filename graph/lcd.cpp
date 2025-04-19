#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 1e6 + 10;
vector<ll> v[N];
ll fa[N], dep[N], son[N], sz[N], top[N];
ll dfn[N], rid[N];   //dfn序列, dfn->标号
ll bot[N]; //维护子树dfn序结束编号
ll vl[N];
ll n, m, r, mod;
ll cnt = 0;

void dfs1(ll u, ll far){
  fa[u] = far, dep[u] = dep[far] + 1, sz[u] = 1;
  for(auto i: v[u]){
    if(i == far)
      continue;
    dfs1(i, u);
    sz[u] += sz[i];
    if(sz[son[u]] < sz[i])
      son[u] = i;
  }
}
void dfs2(ll u, ll head){
  top[u] = head;
  dfn[u] = ++cnt;
  rid[cnt] = u;
  if(!son[u]){
    bot[u] = cnt;
    return;
  }
  dfs2(son[u], head);
  for(auto i: v[u]){
    if(i == fa[u] || son[u] == i)
      continue;
    dfs2(i, i);
  }
  bot[u] = cnt;
}
ll sm[4 * N];
ll lz[4 * N];
void pushup(ll node){
  sm[node] = sm[node << 1] + sm[node << 1 | 1];
  sm[node] %= mod;
}

void pushdown(ll node, ll l, ll r, ll mid){
  if(lz[node]){
    lz[node << 1] += lz[node];
    lz[node << 1] %= mod;
    lz[node << 1 | 1] += lz[node];
    lz[node << 1 | 1] %= mod;
    sm[node << 1] += lz[node] * (mid - l + 1ll);
    sm[node << 1] %= mod;
    sm[node << 1 | 1] += lz[node] * (r - mid);
    sm[node << 1 | 1] %= mod;
    lz[node] = 0;
  }
}
void build(ll node, ll l, ll r){
  if(l == r){
    sm[node] = vl[rid[l]];
    sm[node] %= mod;
    return;
  }
  ll mid = (l + r) >> 1;
  build(node << 1, l, mid);
  build(node << 1 | 1, mid + 1, r);
  pushup(node);
}

void update(ll node, ll l, ll r, ll ql, ll qr, ll val){
  if(ql <= l && r <= qr){
    sm[node] += val * (r - l + 1ll);
    sm[node] %= mod;
    lz[node] += val;
    lz[node] %= mod;
    return;
  }
  ll mid = (l + r) >> 1;
  pushdown(node, l, r, mid);
  if(ql <= mid)
    update(node << 1, l, mid, ql, qr, val);
  if(qr > mid)
    update(node << 1 | 1, mid + 1, r, ql, qr, val);
  pushup(node);
}

ll query(ll node, ll l, ll r, ll ql, ll qr){
  if(ql <= l && r <= qr){
    return sm[node] % mod;
  }
  ll mid = (l + r) >> 1;
  pushdown(node, l, r, mid);
  ll sum = 0;
  if(ql <= mid)
    sum += query(node << 1, l, mid, ql, qr);
  if(qr > mid)
    sum += query(node << 1 | 1, mid + 1, r, ql, qr);
  return sum % mod;
}

void add_path(ll u, ll v, ll val){
  while(top[u] != top[v]){
    if(dep[top[u]] < dep[top[v]])
      swap(u, v);
    update(1, 1, n, dfn[top[u]], dfn[u], val);
    u = fa[top[u]];
  }
  if(dep[u] < dep[v]) swap(u, v);
  update(1, 1, n, dfn[v], dfn[u], val);
}

ll get_path(ll u, ll v){
  ll sum = 0;
  while(top[u] != top[v]){
    if(dep[top[u]] < dep[top[v]])
      swap(u, v);
    // sum += query(1, 1, n, dfn[top[u]], dfn[u]);
    // sum %= mod;
    u = fa[top[u]];
  }
  if(dep[u] < dep[v]) swap(u, v);
  sum += query(1, 1, n, dfn[v], dfn[u]);  
  return sum % mod;
}

void update_root(ll x, ll val){
  update(1, 1, n, dfn[x], bot[x], val);
}
ll get_root(ll x){
  return query(1, 1, n, dfn[x], bot[x]);
}
int main(){
  cin >> n >> m >> r >> mod;
  for(ll i = 1; i <= n; ++i){
    cin >> vl[i];
  }
  for(ll i = 1; i < n; ++i){
    ll x, y;
    cin >> x >> y;
    v[x].push_back(y);
    v[y].push_back(x);
  }
  dfs1(r, 0);
  dfs2(r, r);
  build(1, 1, n);
  for(ll i = 1; i <= m; ++i){
    ll op, x, y, z;
    cin >> op;
    if(op == 1){
      cin >> x >> y >> z;
      add_path(x, y, z);
    }
    else if(op == 2){
      cin >> x >> y;
      cout << get_path(x, y) << '\n';
    }
    else if(op == 3){
      cin >> x >> z;
      update_root(x, z);
    }
    else{
      cin >> x;
      cout << get_root(x) << '\n';
    }
  }
}