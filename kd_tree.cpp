// 用多个heuristic来优化：
// 1. 取中点，并使用quick select
// 2. 取variance最大的一维进行divide
// 3. Query时，若一个结点的两个子树都有可能包含答案，先在与查询点距离最近的一个子树中搜索答案
// 建树平均时间复杂度是O(nlogn)，查询平均时间复杂度是O(logn)，最坏情况仍然可能是O(n)

#include <bits/stdc++.h>

using namespace std;

const int DIM = 3;

struct KDTree {
    double ans;
    int n;
    vector<vector<int>> child;
    vector<vector<double>> p;
    vector<vector<vector<double>>> bound;

    KDTree(vector<vector<double>>& p) : p(p) {
        n = p.size();
        child.assign(n, vector<int>(2, -1));
        bound.assign(DIM, vector<vector<double>>(n, vector<double>(2)));
        Build();
    }

    double Square(double x) {
        return x * x;
    }

    double Dist(int x, vector<double>& v) {
        double ret = 0;
        for (int d = 0; d < DIM; d++)
            ret += Square(p[x][d] - v[d]);
        return sqrt(ret);
    }

    void Maintain(int x) {
        for (int d = 0; d < DIM; d++)
            bound[d][x][0] = bound[d][x][1] = p[x][d];
        for (int c = 0; c < 2; c++) {
            if (child[x][c] != -1) {
                for (int d = 0; d < DIM; d++) {
                    bound[d][x][0] = min(bound[d][x][0], bound[d][child[x][c]][0]);
                    bound[d][x][1] = max(bound[d][x][1], bound[d][child[x][c]][1]);
                }
            }
        }
    }

    int Build() {
        Build(0, n - 1);
    }

    int Build(int l, int r) {
        if (l > r)
            return -1;
        int mid = (l + r) / 2;
        vector<double> avg(DIM), var(DIM);
        for (int d = 0; d < DIM; d++)
            for (int i = l; i <= r; i++)
                avg[d] += p[i][d];
        for (int d = 0; d < DIM; d++)
            avg[d] /= (r -l + 1);
        for (int d = 0; d < DIM; d++)
            for (int i = l; i <= r; i++)
                var[d] += Square(p[i][d] - avg[d]);
        int dim = 0;
        for (int d = 0; d < DIM; d++)
            if (var[d] > var[dim])
                dim = d;
        auto cmp = [&](vector<double>& a, vector<double>& b) {
            return a[dim] < b[dim];
        };
        nth_element(p.begin() + l, p.begin() + mid, p.begin() + r + 1, cmp);
        child[mid][0] = Build(l, mid - 1);
        child[mid][1] = Build(mid + 1, r);
        Maintain(mid);
        return mid;
    }

    double BoundDist(int x, vector<double>& v) {
        double ret = 0;
        for (int d = 0; d < DIM; d++) {
            if (v[d] < bound[d][x][0])
                ret += Square(bound[d][x][0] - v[d]);
            else if (v[d] > bound[d][x][1])
                ret += Square(bound[d][x][1] - v[d]);
        }
        return sqrt(ret);
    }

    double Query(vector<double>& v) {
        ans = INFINITY;
        Query(0, n - 1, v);
        return ans;
    }

    void Query(int l, int r, vector<double>& v) {
        if (l > r)
            return;
        int mid = (l + r) / 2;
        ans = min(ans, Dist(mid, v));
        if (l == r)
            return;
        if (child[mid][0] == -1)
            Query(mid + 1, r, v);
        else if (child[mid][1] == -1)
            Query(l, mid - 1, v);
        else {
            double Distl = BoundDist(child[mid][0], v);
            double Distr = BoundDist(child[mid][1], v);
            if (Distl < ans && Distr < ans) {
                if (Distl < Distr) {
                    Query(l, mid - 1, v);
                    if (Distr < ans)
                        Query(mid + 1, r, v);
                }
                else {
                    Query(mid + 1, r, v);
                    if (Distl < ans)
                        Query(l, mid - 1, v);
                }
            }
            else {
                if (Distl < ans)
                    Query(l, mid - 1, v);
                if (Distr < ans)
                    Query(mid + 1, r, v);
            }
        }
    }
};


int main() {
    int n = 10000;
    random_device rd;
    mt19937 rng(rd());
    uint MAX = -1;
    int X = 100000;

    vector<vector<double>> p(n, vector<double>(DIM));
    for (int i = 0; i < n; i++)
        for (int d = 0; d < DIM; d++)
            p[i][d] = double(rng()) / MAX * X;

    KDTree kd(p);
    int q = 1000;
    for (int i = 0; i < q; i++) {
        vector<double> cur(DIM);
        for (int d = 0; d < DIM; d++)
            cur[d] = double(rng()) / MAX * X;
        double ans = kd.Query(cur);
        double sol = INFINITY;
        for (int i = 0; i < n; i++) {
            double ret = 0;
            for (int d = 0; d < DIM; d++)
                ret += kd.Square(p[i][d] - cur[d]);
            sol = min(sol, sqrt(ret));
        }
        if (ans != sol)
            cout << ans << " " << sol << '\n';
    }
    return 0;
}