    template<class T >
    struct DiscreteFourierTransform
    {
       using Complex = T;
        vector<Complex> dft(vector<Complex> a, int n, int sgn = 1)
        {
            if (n == 1) return a;
            vector<Complex> b(n / 2), c(n / 2);
            for (int i = 0; i < n / 2; i++) {
                b[i] = a[2 * i];
                c[i] = a[2 * i + 1];
            }
            b = dft(b, n / 2, sgn);
            c = dft(c, n / 2, sgn);
            Complex zeta(cos(2.0 * M_PI / n), sin(2.0 * M_PI / n) * sgn);
            Complex pow_zeta = 1;
            for (int i = 0; i < n; i++) {
                a[i] = b[i % (n / 2)] + pow_zeta * c[i % (n / 2)];
                pow_zeta *= zeta;
            }
            return a;
        }
    
        vector<Complex> inv_dft(vector<Complex> a, int n)
        {
            a = dft(a, n, -1);
            for (int i = 0; i < n; i++) {
                a[i] /= n;
            }
            return a;
        }
    
        vector<Complex> multiply(vector<Complex> a, vector<Complex> b)
        {
            int sz = a.size() + b.size() + 1;
            int n = 1; while (n < sz) n *= 2;
            a.resize(n); b.resize(n);
            a = dft(a, n);
            b = dft(b, n);
            vector<Complex> f(n);
            for (int i = 0; i < n; i++) {
                f[i] = a[i] * b[i];
            }
            return inv_dft(f, n);
        }
    };
