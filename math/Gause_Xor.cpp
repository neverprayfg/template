#ifdef IGNODE_THIS_FILE

std::bitset<1010> matrix[2010];  // matrix[1~n]：增广矩阵，0 位置为常数
std::vector<bool> GaussElimination(int n, int m) { 
  // n 为未知数个数，m 为方程个数，返回方程组的（多解 / 无解返回一个空的 vector）
  for (int i = 1; i <= n; i++) {
    int cur = i;
    while (cur <= m && !matrix[cur].test(i)) cur++;
    if (cur > m) return std::vector<bool>(0);
    if (cur != i) swap(matrix[cur], matrix[i]);
    for (int j = 1; j <= m; j++)
      if (i != j && matrix[j].test(i)) matrix[j] ^= matrix[i];
  }
  std::vector<bool> ans(n + 1);
  for (int i = 1; i <= n; i++) ans[i] = matrix[i].test(0);
  return ans;
}
#endif