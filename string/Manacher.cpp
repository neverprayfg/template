#ifdef IGNORE_THIS_FILE

struct Manacher {
    string transformed;
    vector<int> d1;

    Manacher(const string& s) {
        // 预处理字符串，插入'#'
        transformed = "#";
        for (char c : s) {
            transformed += c;
            transformed += '#';
        }
        int n = transformed.size();
        d1.resize(n);
        // 计算每个中心点的最长回文半径
        int l = 0, r = -1;
        for (int i = 0; i < n; ++i) {
            int k = (i > r) ? 1 : min(d1[l + r - i], r - i + 1);
            while (i - k >= 0 && i + k < n && transformed[i - k] == transformed[i + k]) {
                k++;
            }
            d1[i] = k--;
            if (i + k > r) {
                l = i - k;
                r = i + k;
            }
        }
    }
};

#endif