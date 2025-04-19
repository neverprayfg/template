#ifdef IGNORE_THIS_FILE
const int N = 1000;
const ll INF = 0x3ffffffffffff;
struct Edge {
    int from, to;
    ll can_flow;
    Edge(int f, int t, ll cap) : from(f), to(t), can_flow(cap){};
};
struct ISAP {
    int n, m; 
    int s, t; 
    vector<int> G[N]; 
    vector<Edge> e; 
    int dep[N], gap[N], cur[N];

    void init(int _n, int _s, int _t) {
        this->n = _n, this->s = _s, this->t = _t;
        for(int i = 0; i <= n; ++i){
            G[i].clear();
        }
    }

    void add_edge(int u, int v, ll cap) {
        e.emplace_back(u, v, cap);
        e.emplace_back(v, u, 0);
        m = e.size();
        G[u].push_back(m - 2);
        G[v].push_back(m - 1);
    }

    void bfs() {
        memset(dep, 0, sizeof(dep));
        queue<int> q;
        q.push(t);
        dep[t] = 1;
        gap[1] = 1;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int i : G[u]) {
                int v = e[i].to;
                if (!dep[v]) {
                    dep[v] = dep[u] + 1;
                    gap[dep[v]]++;
                    q.push(v);
                }
            }
        }
    }

    ll dfs(int u, ll flow) {
        if (u == t || !flow) return flow;
        ll used = 0;
        for (int &i = cur[u]; i < G[u].size(); ++i) {
            int id = G[u][i];
            auto&[from, to, can_flow] = e[id];
            if (can_flow && dep[u] == dep[to] + 1) {
                ll tmp = dfs(to, min(flow - used, can_flow));
                if (tmp) {
                    e[id].can_flow -= tmp;
                    e[id ^ 1].can_flow += tmp;
                    used += tmp;
                }
                if (used == flow) return used;
            }
        }
        
        --gap[dep[u]];
        if (!gap[dep[u]]) dep[s] = n + 1;
        ++dep[u];
        ++gap[dep[u]];
        return used;
    }

    ll isap() {
        ll max_flow = 0;
        bfs();
        while (dep[s] <= n) {
            memset(cur, 0, sizeof(cur));
            max_flow += dfs(s, INF);
        }
        return max_flow;
    }
};
#endif