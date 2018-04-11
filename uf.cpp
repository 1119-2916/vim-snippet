    struct UnionFind {
        vector<int> parent;
        int size;
        UnionFind(int n) :parent(n, -1), size(n) {}
        bool unite(int x, int y) {
            x = root(x); y = root(y);
            if (x == y)return false;
            if (sizeOf(x) < sizeOf(y))swap(x, y);
            parent[x] += parent[y]; parent[y] = x; size--;
            return true;
        }
        bool same(int x, int y) { return root(x) == root(y); }
        int root(int x) { return parent[x] < 0 ? x : parent[x] = root(parent[x]); }
        int sizeOf(int x) { return -parent[root(x)]; }
    };
