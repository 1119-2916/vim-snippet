    //最小全域木 (Minimum Spanning Tree)
    //Kruskal O(|E|log|E|)
    //非連結グラフでは最小全域森
    // ** 要include uf, graph ** 
    pair<Weight, Edges> kruskal(const Graph &g) {
        int n = g.size();
        UnionFind uf(n);
        Edges es;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < g[i].size(); j++) {
                Edge e = g[i][j];
            //for (auto &e : g[i])
                es.push_back(e);
            }
        sort(es.begin(), es.end());
        Weight total = 0;
        Edges mst;
        for (int i = 0; i < es.size(); i++) {
            Edge e = es[i];
        //for (auto &e : es)
            if (!uf.same(e.s, e.d)) {
                uf.unite(e.s, e.d);
                mst.push_back(e);
                total += e.w;
            }
        }
        return make_pair(total, mst);
    }
