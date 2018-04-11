    bool next_combination(std::vector<int>& v, int n) {
        int k = v.size();
        int p = k - 1;
        if (v[p] >= n) return false;
        while (p >= 0 && ++v[p] >= n - (k - p - 1)) --p;
        if (p < 0) return false;
        ++p;
        while (p < k) {
            v[p] = v[p - 1] + 1;
            ++p;
        }
        return true;
    }
