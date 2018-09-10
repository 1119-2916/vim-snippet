    /**
     * parent : size を負で持つ。負値でなければ参照する親のindexを持つ
     * timestamp : uniteされた時間を持つ
     * history : uniteされる寸前のtimeとsizeを持つQ
     * 必ずuniteは時系列の若い順に行うこと！
     * 同じ時間にuniteが発生しても正常に動作しそう
     */
    struct PartiallyPersistentUnionFind
    {
        using data_type = int;
        vector<data_type> parent, timestamp;
        vector< vector< pair< data_type, data_type > > > history;
    
        PartiallyPersistentUnionFind() {}
    
        PartiallyPersistentUnionFind(int sz)
            : parent(sz, -1), timestamp(sz, 1e9), history(sz)
        {
            for (auto &vs : history) vs.emplace_back(-1, -1);
        }
    
        bool unite(int t, int x, int y)
        {
            x = find(t, x);
            y = find(t, y);
            if (x == y) return false;
            if (parent[x] > parent[y]) swap(x, y);
            parent[x] += parent[y];
            history[x].emplace_back(t, parent[x]);
            parent[y] = x;
            timestamp[y] = t;
            return true;
        }
        int find(int t, int x)
        {
            if (t < timestamp[x]) return x;
            return find(t, parent[x]);
        }
    
        int size(int t, int x)
        {
            x = find(t, x);
            return -prev(lower_bound(begin(history[x]), end(history[x]), 
                        make_pair(t, (data_type)0)))->second;
        }
        bool same(int t, int x, int y)
        {
            return find(t, x) == find(t, y);
        }
    };
