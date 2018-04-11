    using Weight = int;
    using Flow = int;
    struct Edge {
        int s, d; Weight w; Flow c;
        Edge() {};
        Edge(int s, int d, Weight w = 1) : s(s), d(d), w(w), c(w) {};
    };
    bool operator<(const Edge &e1, const Edge &e2) { return e1.w < e2.w; }
    bool operator>(const Edge &e1, const Edge &e2) { return e2 < e1; }
    inline ostream &operator<<(ostream &os, const Edge &e) { return (os << '(' << e.s << ", " << e.d << ", " << e.w << ')'); }
    
    using Edges = vector<Edge>;
    using Graph = vector<Edges>;
    using Array = vector<Weight>;
    using Matrix = vector<Array>;
    
    void addArc(Graph &g, int s, int d, Weight w = 1) {
        g[s].emplace_back(s, d, w);
    }
    void addEdge(Graph &g, int a, int b, Weight w = 1) {
        addArc(g, a, b, w);
    addArc(g, b, a, w);
    }
