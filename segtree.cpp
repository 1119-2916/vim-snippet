    struct Monoid {
        using T = int;
        T operator()(const T &a, const T& b) { return min(a, b); }
        static const T I = INT_MAX;
    };
    struct SegmentTree {
        using T = Monoid::T;
        Monoid op;
        int n;
        vector<T> d;
        SegmentTree(int m) {
            for (n = 1; n < m; n *= 2);
            d.assign(2 * n - 1, op.I);
        }
        void update(int k, T x) {
            k += n - 1;
            d[k] = x;
            while (k > 0) {
                k = (k - 1) / 2;
                d[k] = op(d[2 * k + 1], d[2 * k + 2]);
            }
        }
        T query(int a, int b, int k, int l, int r) {
            if (r <= a || b <= l)return op.I;
            if (a <= l&&r <= b)return d[k];
            int xl = query(a, b, 2 * k + 1, l, (l + r) / 2);
            int xr = query(a, b, 2 * k + 2, (l + r) / 2, r);
            return op(xl, xr);
        }
        T query(int a, int b) {
            return query(a, b, 0, 0, n);
        }
    };
