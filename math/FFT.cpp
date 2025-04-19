#ifdef IGNODE_THIS_FILE
/*
 * 做 FFT
 * len 必须是 2^k 形式
 * on == 1 时是 DFT，on == -1 时是 IDFT
 */
void fft(Complex y[], int len, int on) {
    // 位逆序置换
    change(y, len);
    // 模拟合并过程，一开始，从长度为一合并到长度为二，一直合并到长度为 len。
    for (int h = 2; h <= len; h <<= 1) {
      // wn：当前单位复根的间隔：w^1_h
      Complex wn(cos(2 * PI / h), sin(on * 2 * PI / h));
      // 合并，共 len / h 次。
      for (int j = 0; j < len; j += h) {
        // 计算当前单位复根，一开始是 1 = w^0_n，之后是以 wn 为间隔递增： w^1_n
        // ...
        Complex w(1, 0);
        for (int k = j; k < j + h / 2; k++) {
          // 左侧部分和右侧是子问题的解
          Complex u = y[k];
          Complex t = w * y[k + h / 2];
          // 这就是把两部分分治的结果加起来
          y[k] = u + t;
          y[k + h / 2] = u - t;
          // 后半个 「step」 中的ω一定和 「前半个」 中的成相反数
          // 「红圈」上的点转一整圈「转回来」，转半圈正好转成相反数
          // 一个数相反数的平方与这个数自身的平方相等
          w = w * wn;
        }
      }
    }
    // 如果是 IDFT，它的逆矩阵的每一个元素不只是原元素取倒数，还要除以长度 len。
    if (on == -1) {
      for (int i = 0; i < len; i++) {
        y[i].x /= len;
        y[i].y /= len;
      }
    }
  }

#endif