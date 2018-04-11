    //lowest common ancestor (ダブリング + dfs再帰)
    //構築O(NlogN) クエリO(logN)
    struct LowestCommonAncestor {
        const int n, log2_n;
        vector< vector <int> > parent;
        vector<int> depth;
        const Graph &g;
        LowestCommonAncestor(const Graph &g, int root)
            :g(g), n(g.size()), log2_n(log2(n) + 1), parent(log2_n, vector<int>(n)), depth(n) {
            dfs(root, -1, 0);
            for (int k = 0; k + 1 < log2_n; k++) {
                for (int v = 0; v < n; v++) {
                    if (parent[k][v] < 0)
                        parent[k + 1][v] = -1;
                    else
                        parent[k + 1][v] = parent[k][parent[k][v]];
                }
            }
        }
        void dfs(int s, int p, int d) {
            parent[0][s] = p;
            depth[s] = d;
            for (int i = 0; i < g[s].size(); i++) {
                Edge e = g[s][i];
                if (e.d == p)continue;
                dfs(e.d, s, d + 1);
            }
        }
        int get(int u, int v) {
            if (depth[u] > depth[v]) swap(u, v);
            for (int k = 0; k < log2_n; k++) {
                if ((depth[v] - depth[u]) >> k & 1) {
                    v = parent[k][v];
                }
            }
            if (u == v) return u;
            for (int k = log2_n - 1; k >= 0; k--) {
                if (parent[k][u] != parent[k][v]) {
                    u = parent[k][u];
                    v = parent[k][v];
                }
            }
            return parent[0][u];
        }
        int dist(int u, int v) {
            int w = get(u, v);
            return depth[u] + depth[v] - depth[w] * 2;
        }
    };
