#ifdef IGNORE_THIS_FILE
struct ACAutomaton {
    static const int N = 2e6 + 6;
    static const int maxn = 2e5 + 10;
    
    int tran[N][26] = {};
    vector<int> uid[maxn];
    int fail[N] = {};
    int ru_degree[maxn] = {};
    int dp[N] = {};
    int ans[maxn] = {};
    int tot = 0;

    void clear() {
        for(int i = 0; i < N; i++) {
            memset(tran[i], 0, sizeof(tran[i]));
            fail[i] = dp[i] = 0;
        }
        for(int i = 0; i < maxn; i++) uid[i].clear();
        memset(ru_degree, 0, sizeof(ru_degree));
        memset(ans, 0, sizeof(ans));
        tot = 0;
    }

    void insert(const string& s, int id) {
        int u = 0;
        for(char ch : s) {
            int c = ch - 'a';
            if(!tran[u][c]) tran[u][c] = ++tot;
            u = tran[u][c];
        }
        uid[u].push_back(id);
    }

    void build() {
        queue<int> q;
        for(int i = 0; i < 26; i++)
            if(tran[0][i]) q.push(tran[0][i]);
        
        while(!q.empty()) {
            int u = q.front();
            q.pop();
            for(int i = 0; i < 26; i++) {
                if(tran[u][i]) {
                    fail[tran[u][i]] = tran[fail[u]][i];
                    q.push(tran[u][i]);
                } else {
                    tran[u][i] = tran[fail[u]][i];
                }
            }
        }
    }

    void query(const string& t) {
        int u = 0;
        for(char ch : t) {
            u = tran[u][ch - 'a'];
            dp[u]++;
        }

        for(int i = 1; i <= tot; i++)
            ru_degree[fail[i]]++;
        
        queue<int> q;
        for(int i = 1; i <= tot; i++)
            if(!ru_degree[i]) q.push(i);
        
        while(!q.empty()) {
            int u = q.front();
            q.pop();
            dp[fail[u]] += dp[u];
            if(--ru_degree[fail[u]] == 0)
                q.push(fail[u]);
        }

        for(int i = 1; i <= tot; i++)
            for(int id : uid[i])
                ans[id] = dp[i];
    }
};

#endif