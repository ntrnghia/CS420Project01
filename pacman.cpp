#include <unistd.h>  //use sleep()
#include <fstream>
#include <iostream>
#include <queue>
#include <stack>
#include <vector>
using namespace std;
void print(vector<vector<int>> &a, int cr, int cc, int &path_length,
           int &point) {
    system("cls");
    for (int r = 0; r < a.size(); ++r) {
        for (int c = 0; c < a[0].size(); ++c) {
            if (r == cr && c == cc)
                cout << "@ ";
            else
                cout << a[r][c] << ' ';
        }
        cout << endl;
    }
    cout << "Path length: " << ++path_length << endl;
    if (a[cr][cc] == 2) {
        a[cr][cc] = 0;
        point += 10;
    } else
        --point;
    cout << "Point: " << point;
    sleep(0.75);
}
void level_1_2(vector<vector<int>> &a, int sm, int sn, int &path_length,
               int &point) {
    if (!a.size()) return;
    int m = a.size(), n = a[0].size();
    int dm, dn;
    for (int r = 0; r < m; ++r) {
        for (int c = 0; c < n; ++c) {
            if (a[r][c] == 2) dm = r, dn = c;
        }
    }
    vector<vector<int>> b(m, vector<int>(n, INT_MAX));
    vector<vector<pair<int, int>>> pre(m, vector<pair<int, int>>(n));
    queue<pair<int, int>> loc;
    loc.push({dm, dn});
    b[dm][dn] = 0;
    int dr[]{1, 0, -1, 0}, dc[]{0, 1, 0, -1};
    while (!loc.empty()) {
        int cr = loc.front().first, cc = loc.front().second;
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
    pre[dm][dn] = {-1, -1};
    for (int cr = sm, cc = sn; cr != -1 || cc != -1;) {
        print(a, cr, cc, path_length, point);
        a[cr][cc] = 5;
        int tmpr = pre[cr][cc].first;
        int tmpc = pre[cr][cc].second;
        cr = tmpr;
        cc = tmpc;
    }
    cout << "\n<5 is pacman trace>";
}
void dfs(vector<vector<int>> &a, vector<vector<bool>> &b, int cr, int cc,
         int &path_length, int &point) {
    print(a, cr, cc, path_length, point);
    int m = a.size(), n = a[0].size();
    int dr[]{1, 0, -1, 0}, dc[]{0, 1, 0, -1};
    for (int i = 0; i < 4; ++i) {
        int nr = cr + dr[i], nc = cc + dc[i];
        if (nr >= 0 && nr < m && nc >= 0 && nc < n &&
            (a[nr][nc] == 0 || a[nr][nc] == 2) && b[nr][nc] == false) {
            b[nr][nc] = true;
            dfs(a, b, nr, nc, path_length, point);
            print(a, cr, cc, path_length, point);
        }
    }
}
void level_3(vector<vector<int>> &a, int sm, int sn, int &path_length,
             int &point) {
    if (!a.size()) return;
    int m = a.size(), n = a[0].size();
    vector<vector<bool>> b(m, vector<bool>(n, false));
    b[sm][sn] = true;
    dfs(a, b, sm, sn, path_length, point);
}
int main() {
    ifstream fin("input.txt");
    int m, n, sm, sn, lv;
    fin >> m >> n;
    vector<vector<int>> a(m, vector<int>(n));
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            fin >> a[i][j];
        }
    }
    fin >> sm >> sn;
    fin.close();
    cout << "Which level you want to try: ";
    cin >> lv;
    int path_length = -1, point = 1;
    switch (lv) {
        case 1:
        case 2:
            level_1_2(a, sm, sn, path_length, point);
            break;
        case 3:
            level_3(a, sm, sn, path_length, point);
            break;
        default:
            break;
    }
    cout << "\nPress enter to exit!";
    cin.get();
    cin.get();
    ofstream fout("output.txt");
    fout << "Path length: " << path_length << endl;
    fout << "Game point: " << point << endl;
    fout.close();
}