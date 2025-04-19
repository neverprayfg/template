#ifdef IGNORE_THIS_FILE
constexpr int N = 250;
constexpr ll INF = 0x3fffffffffffff;
struct Edge {
    int from, to;
    ll can_flow;   
    Edge(int u, int v, ll can_f) : from(u), to(v), can_flow(can_f) {}
};
struct EK {
    int n, m;             // n：点数，m：边数
    vector<Edge> e;   // e：所有边的集合
    vector<int> G[N];  // G：点 x -> x 的所有边在 e 中的下标
    ll a[N];     // a：点 x -> BFS 过程中最近接近点 x 的边给它的最大流
    int p[N];    // p：点 x -> BFS 过程中最近接近点 x 的边

    void init(int n) {
        for (int i = 0; i <= n; i++) G[i].clear();
        e.clear();
    }

    void AddEdge(int from, int to, ll cap) {
        e.emplace_back(from, to, cap);
        e.emplace_back(to, from, 0);
        m = e.size();
        G[from].push_back(m - 2);
        G[to].push_back(m - 1);
    }

    ll Maxflow(int s, int t) {
        ll max_flow = 0;
        while(true) {
            memset(a, 0, sizeof(a));
            queue<int> qu;
            qu.push(s);
            a[s] = INF;
            while (!qu.empty()) {
                int u = qu.front();
                qu.pop();
                for (int i: G[u]) {  // 遍历以 u 作为起点的边
                    const auto& [from, to, can_flow] = e[i];
                    if (!a[to] && can_flow) {
                        p[to] = i;  // e[i] 是最近接近点 to 的边
                        a[to] = min(a[u], can_flow);  // 最近接近点 to 的边赋给它的流
                        qu.push(to);
                    }
                }
                if (a[t]) break;  // 如果汇点接受到了流，就退出 BFS
            }
            if (!a[t])
                break;  // 如果汇点没有接受到流，说明源点和汇点不在同一个连通分量上
            for (int u = t; u != s; u = e[p[u]].from) {  // 通过 u 追寻 BFS 过程中 s -> t 的路径
                e[p[u]].can_flow -= a[t];      // 减少路径上边的 can_flow 值
                e[p[u] ^ 1].can_flow += a[t];  // 增加反向路径的 can_flow 值
            }
            max_flow += a[t];
        }
        return max_flow;
    }
};
#endif