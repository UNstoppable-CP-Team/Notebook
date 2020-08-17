/*
*   edge: edge structure where
*         v = from, cap = capacity, inv = id of the inverse edge, flow = current flow on the edge.
*
*   Dinic: n = number of nodes, s = source node, t = sink node;
*          lvl = vector level of nodes (level network)
*          g = network flow graph
*          call maxflow with oo = the require flow (infinite for maximum flow or a value if you want a flow <= x)
*
*/
//Complexity O (n * n * m); where m = number of edges
struct Edge {
    int v, cap, inv, flow;
    edge() {}
    edge(int v, int cap, int inv, int flow) : v(v), cap(cap), inv(inv),
                                              flow(flow) {}
};
struct Dinic {
    int n, s, t;
    vector<int> lvl;
    vector<vector<edge> > g;
    Dinic(int n) : n(n), lvl(n), g(n) {}
    void add_edge(int u, int v, int c) {
        g[u].push_back(edge(v, c, g[v].size(), 0));
        g[v].push_back(edge(u, 0, g[u].size()-1, c));
    }
    bool bfs() {
        fill(lvl.begin(), lvl.end(), -1);
        queue<int> q; 
        q.push(s);
        lvl[s] = 0;
        while(q.size()) {
            int u = q.front(); q.pop();
            for(int i = 0; i < g[u].size(); i++) {
                edge &e = g[u][i];
                if(e.cap > 0 && lvl[e.v] == -1) {
                    lvl[e.v] = lvl[u]+1;
                    q.push(e.v);
                }
            }
        }
        return lvl[t] != -1;
    }
    int dfs(int u, int nf) {
        if(u == t) return nf;
        int res = 0;
        for(int i = 0; i < g[u].size(); i++) {
            edge &e = g[u][i];
            if(e.cap > 0 && lvl[e.v] == lvl[u]+1) {
                int tf = dfs(e.v, min(nf, e.cap));
                res += tf;
                nf -= tf;
                e.cap -= tf;
                e.flow += tf;
                g[e.v][e.inv].cap += tf;
                g[e.v][e.inv].flow -= tf;
                if(nf == 0) return res;
            }
        }
        if (!res) lvl[u] = -1;
        return res;
    }
    int max_flow(int so, int si, int res = 0) {
        s = so; t = si;
        while(bfs())
            res += dfs(s, oo);
        return res;
    }
};
