    /*
     * table は半開区間2次元累積和配列
     */
    int cusum(vvi &table, int minx, int miny, int maxx, int maxy)
    {
        return table[maxx][maxy] + table[minx][miny]
            - table[maxx][miny] - table[minx][maxy];
    }
