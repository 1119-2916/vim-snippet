    int fact[1145140];
    int pascal_table[100][100];

    /*
     * tableをdoubleにしてncmの割合も求められる
     * 1/2して下ってゆくように書き換えてその場で作る.
     */
    void make_pascal(int mod)
    {
        rep(i, 100) {
            pascal_table[i][0] = 1;
            for (int j = 1; j < i; j++) {
                pascal_table[i][j] = (pascal_table[i-1][j-1] +
                    pascal_table[i-1][j]) % mod;
            }
            pascal_table[i][i] = 1;
        }
    }

    int gcd(int a, int b) { if (b == 0) return a; return gcd(b, a%b); }

    int extgcd(int a, int b, int &x, int &y)
    {
        int d = a;
        if (b != 0) {
            d = extgcd(b, a % b, y, x);
            y -= (a / b) * x;
        } else { x = 1; y = 0; }
        return d;
    }

    int repow(int x, int n, int mod)
    {
        if (n == 0) return 1;
        int res = repow(x * x % mod, n / 2, mod);
        if (n & 1) res = res * x % mod;
        return res;
    }
    
    int mod_inverse(int a, int m)
    {
        int x, y;
        extgcd(a, m, x, y);
        return ( m + x % m ) % m;
    }
    
    int table(int n, int p)
    {
        int sum = 1;
        fact[0] = 1;
        Rep(i, n+2) {
            sum *= i;
            sum %= p;
            fact[i] = sum;
        }
    }
    
    int mod_fact(int n, int p, int &e)
    {
        e = 0;
        if (n == 0) return 1;
        int res = mod_fact(n / p, p, e);
        e += n / p;
    
        if (n / p % 2 != 0) return res * (p - fact[n % p]) % p;
        return res * fact[n % p] % p;
    }
    
    /*
     * nCr mod p
     * nHr = (n+r-1)Cr
     * 必ずtable()を呼んでから使う.
     * n = 1001000くらいで
     */
    int mod_comb(int n, int k, int p) {
        if (n < 0 || k < 0 || n < k) return 0;
        int e1, e2, e3;
        int a1 = mod_fact(n, p, e1), a2 = mod_fact(k, p, e2), a3 = mod_fact(n-k, p, e3);
        if (e1 > e2 + e3) return 0;
        return a1 * mod_inverse(a2 * a3 % p, p) % p;
    }
    
    int ncm(int n, int r)
    {
        if (r == 0) return 1;
        return (n-r+1) * ncm(n, r-1) / r;
    }
