    /**
     * 動的 CHT 単調性無しok 各操作 O(logN)
     * **必ず厳密な探索範囲[minn, maxx]を与えること**
     * T = int 以外で未検証
     */
    template <typename T, const T id = numeric_limits<T>::min()>
    class CHT {
        using L = T;   // 返り値の型 (縦軸)
        const T accuracy = 0;  // 精度 (横軸)
        struct Line {
            T a, b;
            Line (T a = 0, T b = 0) : a(a), b(b) {}
            L get (T x) { return a * x + b; }
        };
        struct Node {
            Line line;
            Node *lch, *rch;
            Node (Line line) : line(line), lch(nullptr), rch(nullptr) {}
        };
    
    private :
        // 探索区間（横軸）の最小、最大
        const T minn, maxx; 
        Node *root;
    
        // [lb, ub]
        Node* update(Node *p, T lb, T ub, Line& line) {
            if (!p) return new Node(line);
            if (p->line.get(lb) >= line.get(lb) && 
                    p->line.get(ub) >= line.get(ub)) return p;
            if (p->line.get(lb) <= line.get(lb) && 
                    p->line.get(ub) <= line.get(ub)) {
                p->line = line;
                return p;
            }
            T mid = (lb + ub) / 2;
            if (p->line.get(mid) < line.get(mid)) swap(p->line, line);
            if (p->line.get(lb) <= line.get(lb))
                p->lch = update(p->lch, lb, mid, line);
            else 
                p->rch = update(p->rch, mid, ub, line);
            return p;
        }
        L query(Node *p, T lb, T ub, T t) {
            if (!p) { return id; }
            if (ub - lb <= accuracy) return p->line.get(t);
            T mid = (lb + ub) / 2;
            if (t <= mid) {
                return max(p->line.get(t), query(p->lch, lb, mid, t));
            }
            return max(p->line.get(t), query(p->rch, mid, ub, t));
        }
    
    public :
        CHT (const T minn, const T maxx) : minn(minn), maxx(maxx), root(nullptr) {}
        void insert(T a, T b) {
            Line line(a, b);
            root = update(root, minn, maxx, line);
        }
        L get(T x) {
            return query(root, minn, maxx, x);
        }
    
    };
    
