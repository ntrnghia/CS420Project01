#include <unistd.h>     //use sleep()
#include <fstream>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
void print(vector<vector<int>> a, int m, int n, int cr, int cc) {
    for (int r = 0; r < m; ++r) {
        for (int c = 0; c < n; ++c) {
            if (r == cr && c == cc)
                cout << "* ";
            else
                cout << a[r][c] << ' ';
        }
        cout << endl;
    }
}
void level_1_2(vector<vector<int>> a, int m, int n, int sm, int sn) {
    int dm, dn;
    for (int r = 0; r < m; ++r) {
        for (int c = 0; c < n; ++c) {
            if (a[r][c] == 2) dm = r, dn = c;
        }
    }
    vector<vector<int>> b(m, vector<int>(n, INT_MAX));
    vector<vector<pair<int, int>>> pre(m, vector<pair<int, int>>(n));
    queue<vector<int>> loc;
    loc.push({dm, dn});
    b[dm][dn] = 0;
    int dr[]{1, 0, -1, 0}, dc[]{0, 1, 0, -1};
    while (!loc.empty()) {
        int cr = loc.front()[0], cc = loc.front()[1];
        for (int i = 0; i < 4; ++i) {
            int nr = cr + dr[i], nc = cc + dc[i];
            if (nr >= 0 && nr < m && nc >= 0 && nc < n && a[nr][nc] == 0 &&
                b[nr][nc] > b[cr][cc] + 1) {
                loc.push({nr, nc});
                b[nr][nc] = b[cr][cc] + 1;
                pre[nr][nc] = {cr, cc};
            }
        }
        loc.pop();
    }
    int path_length = 0;
    pre[dm][dn] = {-1, -1};
    for (int cr = sm, cc = sn; cr != -1 || cc != -1; ++path_length) {
        system("cls");
        print(a, m, n, cr, cc);
        int tmpr = pre[cr][cc].first;
        int tmpc = pre[cr][cc].second;
        cr = tmpr;
        cc = tmpc;
        cout << "Path length: " << path_length << endl;
        cout << "Point: ";
        if (cr == -1 && cc == -1)
            cout << 11 - path_length;
        else
            cout << -path_length;
        sleep(1);
    }
    cin.get();
}
void level_3(int **a, int m, int n, int sm, int sn) {}
int main() {
    ifstream fin("input.txt");
    int m, n, sm, sn;
    fin >> m >> n;
    vector<vector<int>> a(m, vector<int>(n));
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            fin >> a[i][j];
        }
    }
    fin >> sm >> sn;
    level_1_2(a, m, n, sm, sn);
}