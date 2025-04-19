#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e4 + 10;
vector<pair<int, int>> v[N];
int n, m;
bool vis[N];
int siz[N], dep[N];
int st[1000 * N];
int wt[N];
int ans[101];
int get(int u, int far, int& num) { // 求子树的重心
    siz[u] = 1;
    wt[u] = 0;
    ++num;
    int root = -1;
    for(auto&[i, w]: v[u]){
        if(i == far || vis[i]) continue;
        root = max(root, get(i, u, num));
        siz[u] += siz[i];
        wt[u] = max(wt[u], siz[i]);
    }
    wt[u] = max(wt[u], num - siz[u]);
    if(wt[u] <= num / 2){
        return u;
    }
    return root;   
}

void cal(int u, int far, int w, vector<int> &lst) { // 向下暴力递归计算
    dep[u] = dep[far] + w;
    lst.push_back(u);
    for (auto &[i, w] : v[u]) {
        if (vis[i] || i == far) continue;
        cal(i, u, w, lst);
    }
}

void dfs2(int u, vector<int>& cur) {
    int num = 0;
    int root = get(u, 0, num);
    vis[root] = true;
    st[0] = 1; 
    dep[root] = 0;
    vector<vector<int> > lst;
    for (auto &[i, w] : v[root]) {
        if (vis[i]) continue;
        vector<int> tmp;
        cal(i, root, w, tmp);
        lst.push_back(tmp);
        for (auto &node : tmp) {
            for(int k = 0; k < cur.size(); ++k){
                if (cur[k] >= dep[node]) {
                    ans[k] += st[cur[k] - dep[node]];
                }
            }
        }

        for (auto &node : tmp) {
            if(dep[node] <= 1e7){
                ++st[dep[node]];
            }
        }
    }
    for(auto& i: lst){
        for(auto& j: i){
            if(dep[j] <= 1e7)
                st[dep[j]] = 0;
        }
    }
    st[0] = 0;
    for (auto &[i, w] : v[root]) {
        if (vis[i]) continue;
        dfs2(i, cur);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i < n; ++i) {
        int u, v_, w;
        cin >> u >> v_ >> w;
        v[u].emplace_back(v_, w);
        v[v_].emplace_back(u, w);
    }
    vector<int> cur;
    for(int i = 0; i < m; ++i){
        int x;
        cin >> x;
        cur.push_back(x);
    }
    dfs2(1, cur);
    for(int i = 0; i < m; ++i){ 
        cout << (ans[i] ? "AYE\n" : "NAY\n");
    }
    return 0;
}