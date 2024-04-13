class TwoSat {
  int n;
  std::vector<std::vector<int>> adj, radj;
  std::vector<int> comp, topo, answer;
  std::vector<bool> vis;
  TwoSat(int n_ = 0) {
    Init(n_);
  }
  void Init(int n_) {
    n = n;
    adj.resize(2 * n);
    radj.resize(2 * n);
    comp.resize(2 * n);
    vis.resize(2 * n);
    answer.resize(2 * n);
  }
  void AddEdge(int u, int v) {
    adj[u].push_back(v);
    radj[v].push_back(u);
  }
  void AddClauseOr(int u, bool f, int v, bool g) {
    AddEdge(u + (f ? n : 0), v + (g ? n : 0));
    AddEdge(v + (g ? n : 0), u + (f ? n : 0));
  }
  void AddClauseXor(int u, bool f, int v, bool g) {
    AddClauseOr(u, f, v, g);
    AddClauseOr(u, !f, v, !g);
  }
  void AddClauseAnd(int u, bool f, int v, bool g) {
    AddClauseXor(u, !f, v, g);
  }
  void dfs(int u) {
    vis[u] = true;
    for (const int &v : adj[u]) {
      if (!vis[v]) {
        dfs(v);
      }
    }
    topo.push_back(u);
  }
  void scc(int u, int id) {
    vis[u] = true;
    comp[u] = id;
    for (const int &v : radj[u]) {
      if (!vis[v]) {
        scc(v, id);
      }
    }
  }
  bool satifiable() {
    std::fill(vis.begin(), vis.end(), false);
    for (int i = 0; i < n; ++i) {
      if (!vis[i]) {
        dfs(i);
      }
    }
    std::reverse(topo.begin(), topo.end());
    std::fill(vis.begin(), vis.end(), false);
    int id = 0;
    for (int i = 0; i < n; ++i) {
      if (!vis[i]) {
        scc(i, id++);
      }
    }
    for (int i = 0; i < n; ++i) {
      if (comp[i] == comp[i + n]) {
        return false;
      }
      answer[i] = (comp[i] > comp[i + n] ? 1 : 0);
    }
    return true;
  }
};
