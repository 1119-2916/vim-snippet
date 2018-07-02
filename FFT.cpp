    namespace FFT {
        const double pi = M_PI;
        std::vector<std::complex<double>> tmp;
        size_t sz = 1;
     
        std::vector<std::complex<double>> fft(std::vector<std::complex<double>> a, bool inv = false) {
            size_t mask = sz - 1;
            size_t p = 0;
            for (size_t i = sz >> 1; i >= 1; i >>= 1) {
                auto& cur = (p & 1) ? tmp : a;
                auto& nex = (p & 1) ? a : tmp;
                std::complex<double> e = std::polar(1., 2 * pi * i * (inv ? -1 : 1) / sz);
                std::complex<double> w = 1;
                for (size_t j = 0; j < sz; j += i) {
                    for (size_t k = 0; k < i; ++k) {
                        nex[j + k] = cur[((j << 1) & mask) + k] + w * cur[(((j << 1) + i) & mask) + k];
                    }
                    w *= e;
                }
                ++p;
            }
            if (p & 1) std::swap(a, tmp);
            if (inv) for (size_t i = 0; i < sz; ++i) a[i] /= sz;
            return a;
        }
        std::vector<int> mul(std::vector<int> a, std::vector<int> b) {
            size_t m = a.size() + b.size() - 1;
            sz = 1;
            while (m > sz) sz <<= 1;
            tmp.resize(sz);
            std::vector<std::complex<double>> A(sz), B(sz);
            for (size_t i = 0; i < a.size(); ++i) A[i].real(a[i]);
            for (size_t i = 0; i < b.size(); ++i) B[i].real(b[i]);
            A = fft(A);
            B = fft(B);
            for (size_t i = 0; i < sz; ++i) A[i] *= B[i];
            A = fft(A, true);
            a.resize(m);
            for (size_t i = 0; i < m; ++i) a[i] = std::round(A[i].real());
            return a;
        }
    };
