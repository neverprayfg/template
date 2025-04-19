#include <vector>
#include <string>
#include <array>
using namespace std;

struct Eertree {
    vector<array<int, 26>> tr;    // 转移数组
    vector<int> fail;             // 失配指针
    vector<int> len;              // 节点表示的回文串长度
    vector<int> ans;              // 存储每个位置的回文深度
    vector<int> depth;            // 节点深度
    int tot, last;                // 总节点数和当前最后节点

    Eertree() {
        tr.resize(2);
        tr[0].fill(0), tr[1].fill(0);
        fail.resize(2);
        len.resize(2);
        depth.resize(2);
        
        fail[0] = 1;  // 偶根失配指向奇根
        fail[1] = 0;  // 奇根失配指向偶根
        len[0] = 0;   // 偶根长度0
        len[1] = -1;  // 奇根长度-1
        depth[0] = 0;
        depth[1] = 0;
        tot = 1;      // 已创建两个节点
        last = 1;     // 初始指向奇根
    }

    void insert(const string& s) {
        ans.resize(s.size());
        for (int i = 0; i < s.size(); i++) {
            int c = s[i] - 'a';
            int fa = get_fail(last, i, s);
            
            if (!tr[fa][c]) {
                create_node(fa, c, i, s);
            }
            last = tr[fa][c];
            ans[i] = depth[last];
        }
    }

    int get_fail(int pos, int idx, const string& s) {
        while (idx - len[pos] - 1 < 0 || 
               s[idx] != s[idx - len[pos] - 1]) {
            pos = fail[pos];
        }
        return pos;
    }

    void create_node(int fa, int c, int idx, const string& s) {
        int cur = ++tot;
        tr.resize(tot + 1);
        tr.back().fill(0);
        
        // 扩展关联数组
        fail.resize(tot + 1);
        len.resize(tot + 1);
        depth.resize(tot + 1);

        tr[fa][c] = cur;
        len[cur] = len[fa] + 2;
        
        // 设置失配指针
        int tmp = get_fail(fail[fa], idx, s);
        fail[cur] = (fa != 1) ? tr[tmp][c] : 0;
        
        // 计算节点深度
        depth[cur] = depth[fail[cur]] + 1;
    }
};