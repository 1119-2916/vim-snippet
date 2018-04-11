    /* 
     * 必ずgraphも一緒にincludeすること
     */
    struct Dinic {
        int n, s, t;
        vector<int> level, prog, que;
        vector< vector< Flow > > cap, flow;
        vector< vector < int > > g;
        Flow inf;
        Dinic(const Graph &graph)
            : n(graph.size()),
            cap(n, vector<Flow>(n)),
            flow(n, vector<Flow>(n)),
            g(n, vector<int>()),
            inf(numeric_limits<Flow>::max() / 8) {
                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < graph[i].size(); j++) {
                        Edge e = graph[i][j];
                        int u = e.s, v = e.d;
                        Flow c = e.c;
                        cap[u][v] += c;
                        cap[v][u] += c;
                        flow[v][u] += c;
                        g[u].push_back(v);
                        g[v].push_back(u);
                    }
                }
            }
        inline Flow residue(int u, int v) { return cap[u][v] - flow[u][v]; }
        Flow solve(int s_, int t_) {
            this->t = t_, this->s = s_;
            que.resize(n + 1);
            Flow res = 0;
            while (levelize()) {
                prog.assign(n, 0);
                res += augment(s, inf);
            }
            return res;
        }
        bool levelize() {
            int l = 0, r = 0;
            level.assign(n, -1);
            level[s] = 0;
            que[r++] = s;
            while (l != r) {
                int v = que[l++];
                if (v == t) break;
                for (int i = 0; i < g[v].size(); i++) {
                    int d = g[v][i];
                    if (level[d] == -1 && residue(v, d) != 0) {
                        level[d] = level[v] + 1;
                        que[r++] = d;
                    }
                }
            }
            return level[t] != -1;
        }
        Flow augment(int v, Flow lim) {
            Flow res = 0;
            if (v == t) return lim;
            for (int &i = prog[v]; i < (int)g[v].size(); i++) {
                const int &d = g[v][i];
                if (residue(v, d) == 0 || level[v] >= level[d]) continue;
                const Flow aug = augment(d, min(lim, residue(v, d)));
                flow[v][d] += aug;
                flow[d][v] -= aug;
                res += aug;
                lim -= aug;
                if (lim == 0) break;
            }
            return res;
        }
    };
