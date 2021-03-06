/**************************************************************
 * Problem: BZOJ3673
 * Author: Rqy
 * Date: 2018 Feb 26
 * Algorithm: 
**************************************************************/
#include <algorithm>
#include <cstdio>
const int N = 20050;
const int NN = 1000000;
int root[N], lc[NN], rc[NN], h[NN], fa[NN], cnt = 1, cur, n, m;
int get(int o, int l, int r, int *A, int x) {
  if (l == r) return A[o];
  int mid = (l + r) / 2;
  if (x <= mid) return get(lc[o], l, mid, A, x);
  else return get(rc[o], mid + 1, r, A, x);
}
void set(int &o, int l, int r, int x, int h1, int fa1) {
  lc[cnt] = lc[o]; rc[cnt] = rc[o]; o = cnt++;
  if (l == r) { h[o] = h1; fa[o] = fa1; return; }
  int mid = (l + r) / 2;
  if (x <= mid) set(lc[o], l, mid, x, h1, fa1);
  else set(rc[o], mid + 1, r, x, h1, fa1);
}
int find(int x) {
  int y;
  while (y = get(root[cur], 1, n, fa, x)) x = y;
  return x;
}
int main() {
  scanf("%d%d", &n, &m);
  for (cur = 1; cur <= m; ++cur) {
    int op, x, y;
    scanf("%d%d", &op, &x);
    root[cur] = root[cur - 1];
    if (op == 1) {
      scanf("%d", &y);
      x = find(x);
      y = find(y);
      if (x == y) continue;
      int hx = get(root[cur], 1, n, h, x);
      int hy = get(root[cur], 1, n, h, y);
      if (hx < hy) set(root[cur], 1, n, x, hx, y);
      else if (hx > hy) set(root[cur], 1, n, y, hy, x);
      else {
        set(root[cur], 1, n, y, hy, x);
        set(root[cur], 1, n, x, hx + 1, 0);
      }
    } else if (op == 2) {
      root[cur] = root[x];
    } else {
      scanf("%d", &y);
      printf("%d\n", find(x) == find(y));
    }
  }
  return 0;
}
