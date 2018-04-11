    //最大公約数
    int gcd(int x, int y) { return y ? gcd(y, x%y) : x; }
    //最小公倍数
    int lcm(int x, int y) { return x / gcd(x, y) * y; }
    //最大公約数 複数個
    int gcd(const vector<int> &v) {
        int ret = v[0];
        for (int i = 1; i < v.size(); i++)
            ret = gcd(ret, v[i]);
        return ret;
    }
    //最小公倍数 複数個
    int lcm(const vector<int> &v) {
        int ret = v[0];
        for (int i = 1; i < v.size(); i++)
            ret = lcm(ret, v[i]);
        return ret;
    }
