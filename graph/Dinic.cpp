#ifdef IGNORE_THIS_FILE
constexpr int N = 500;
constexpr ll INF = 0x3ffffffffffffff;
struct edge {
    int from, to;
    ll can_flow;
    edge(int f, int t, ll can_f) : from(f), to(t), can_flow(can_f){};
};
struct Dinic {
    vector<edge> e;
    vector<int> G[N];
    int dep[N], cur[N];  
    int n, m;
    void init(int n) {
        this->n = n;
        for(int i = 0; i <= n; ++i) G[i].clear();
        e.clear();
    }
  
    void addedge(int from, int to, ll cap) {
        e.emplace_back(from ,to, cap);
        e.emplace_back(to, from, 0);
        m = e.size();
        G[from].push_back(m - 2);
        G[to].push_back(m - 1);
    }
  
    bool bfs(int S, int T) {
        queue<int> q;
        memset(dep, 0, sizeof(int) * (n + 1));
  
        dep[S] = 1;
        q.push(S);
        while (q.size()) {
            int u = q.front();
            q.pop();
            for(int i = 0; i < G[u].size(); ++i){
                int id = G[u][i];
                const auto&[from, to, can_flow] = e[id];
                if ((!dep[to]) && can_flow) {
                    dep[to] = dep[u] + 1;
                    q.push(to);
                }
            }
        }
        return dep[T];
    }
  
    ll dfs(int u, int T, ll last_flow) {
        if (u == T || !last_flow) return last_flow;
        ll flow = 0;
        ll f;
        for (int& i = cur[u]; i < G[u].size(); ++i) {
            int id = G[u][i];
            const auto&[from, to, can_flow] = e[id];
            if (dep[u] + 1 == dep[to] && (f = dfs(to, T, min(last_flow, can_flow))) > 0) {
                e[id].can_flow -= f;
                e[id ^ 1].can_flow += f;
                flow += f;
                last_flow -= f;
                if (!last_flow) break;
            }
        }
        return flow;
      }
  
    ll dinic(int S, int T) {
        ll maxflow = 0;
        while (bfs(S, T)) {
            memset(cur, 0, sizeof(cur));
            maxflow += dfs(S, T, INF);
        }
        return maxflow;
    }
};
#endif