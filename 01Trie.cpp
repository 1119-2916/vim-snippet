    /*
     * 正整数値の入力を想定
     * xor した i 番目を取り出したい時は xor(x) get(i) xor(x) する
     */
    template< int dig = 64 >
    struct Binary_Trie {
        using T = int; // int 以外の利用を想定していない 定数のキャストのため
        bool use_set = false;
        struct Trie_Node {
            struct Trie_Node *left, *right;
            std::set< int > ids; // 自分以下の id のリスト
            int num;
            T lazy;
            Trie_Node() : left(nullptr), right(nullptr), num(0), lazy(0) {}
            Trie_Node(Trie_Node *left, Trie_Node *right) : left(left), right(right) 
            {
                this->num = 0; this->lazy = 0;
                if (left != nullptr) this->num += left->num; 
                if (right != nullptr) this->num += right->num; 
            }
        };
        Trie_Node *head;
        Binary_Trie() : head(nullptr) {}
        int size() { return (head) ? head->num : 0; }
        bool empty() { return !head; }
        void propagate(Trie_Node *p, int digit) {
            if ((p->lazy >> (T)digit) & (T)1) swap(p->left, p->right);
            if (p->left) p->left->lazy ^= p->lazy;
            if (p->right) p->right->lazy ^= p->lazy;
            p->lazy = 0;
        }
        Trie_Node* add(Trie_Node *p, int input, int id, int digit = dig-1) {
            if (!p) p = new Trie_Node;
            p->num++; 
            if (use_set) p->ids.insert(id);
            if (digit < 0) return p;
            propagate(p, digit);
            bool f = (input >> (T)digit) & (T)1;
            if (f) p->right = add(p->right, input, id, digit-1);
            else p->left = add(p->left, input, id, digit-1);
            return p;
        }
        Trie_Node* remove(Trie_Node *p, int input, int id, int digit = dig-1) {
            if (p->num == 1) return nullptr;
            p->num--; 
            if (use_set) p->ids.erase(id);
            if (digit < 0) return p;
            propagate(p, digit);
            bool f = (input >> (T)digit) & (T)1;
            if (f) p->right = remove(p->right, input, id, digit-1);
            else p->left = remove(p->left, input, id, digit-1);
            return p;
        }
        // k 番目に小さい値を得る [0, n)
        // 0-index なので注意
        T get(Trie_Node *p, int k, int digit = dig-1) {
            if (digit < 0) return 0;
            propagate(p, digit);
            int tmp = p->left ? p->left->num : 0;
            return ((k < tmp) ?  get(p->left, k, digit-1) : 
                (get(p->right, k-tmp, digit-1) | ((T)1 << (T)digit)));
        }
        // 数 k よりも小さい値の中で最大のものがいくつあるか
        // k bit ある時、2^k-1 は利用できないことに注意
        int search(Trie_Node *p, int k, int digit = dig-1) {
            if (!p || digit < 0) return 0;
            propagate(p, digit);
            int f = (k >> (T)digit) & (T)1;
            if (f) return search(p->right, k, digit-1)
                + (p->left ? p->left->num : 0);
            else return search(p->left, k, digit-1);
        }
    
        void insert(int input, int id = 0) {
            head = add(head, input, id);
        }
        void eject(int input, int id = 0) {
            head = remove(head, input, id);
        }
        T query(int k) {
            return get(head, k);
        }
        void xor_all(int x) {
            if (head) head->lazy ^= x;
        }
        // data 以上で最小の値が何番目か
        int lower_bound(int data) {
            return search(head, data);
        }
    };
