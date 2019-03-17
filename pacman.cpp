#include <algorithm>
#include <fstream>
#include <list>
#include <queue>
#include <vector>
using namespace std;
void pacman(int **a, int n, int m, int sn, int sm) {
    int dn, dm;
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < m; ++c) {
            if (a[r][c] == 2) dn = r, dm = c;
        }
    }
    vector<vector<int>> b(n, vector<int>(m, INT_MAX));
    vector<vector<pair<int, int>>> pre(n, vector<pair<int, int>>(m, {-1, -1}));
    queue<vector<int>> loc;
    loc.push({dn, dm});
    b[dn][dm] = 0;
    int dr[]{1, 0, -1, 0}, dc[]{0, 1, 0, -1};
    while (!loc.empty()) {
        int cr = loc.front()[0], cc = loc.front()[1];
        for (int i = 0; i < 4; ++i) {
            int nr = cr + dr[i], nc = cc + dc[i];
            if (nr >= 0 && nr < n && nc >= 0 && nc < m && a[nr][nc] == 0 &&
                b[nr][nc] > b[cr][cc] + 1) {
                loc.push({nr, nc});
                b[nr][nc] = b[cr][cc] + 1;
                pre[nr][nc] = {cr, cc};
            }
        }
        loc.pop();
    }
    for (int cr = sn, cc = sm; pre[cr][cc].first != -1;) {
        int tmpr = pre[cr][cc].first;
        int tmpc = pre[cr][cc].second;
        a[tmpr][tmpc] = 5;
        cr = tmpr;
        cc = tmpc;
    }
    ofstream fout("output.txt");
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < m; ++c) {
            fout << a[r][c] << ' ';
        }
        fout << endl;
    }
}
int main() {
    ifstream fin("input.txt");
    int n, m, sn, sm;
    fin >> n >> m;
    int **a = new int *[n];
    for (int i = 0; i < n; ++i) a[i] = new int[m];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            fin >> a[i][j];
        }
    }
    fin >> sn >> sm;
    pacman(a, n, m, sn, sm);
    for (int i = 0; i < n; ++i) delete[] a[i];
    delete[] a;
}