#pragma once

#include "util.hpp"

///////////////////////////////////////////////////////////////////////////////////////////////////

struct GraphVertex;

struct GraphEdge {
    int weight;
    GraphVertex* to = nullptr;

    GraphEdge(int w, GraphVertex* v) {
        weight = w;
        to = v;
    }

    bool operator<(const GraphEdge& rhs) const {
        return to < rhs.to;
    }
};

struct GraphVertex {
    int val;
    std::set<GraphEdge> edges;  // <next node, weight>

    explicit GraphVertex(int v) {
        val = v;
    }

    void add_edge(int weight, GraphVertex* to) {
        edges.emplace(weight, to);
    }
};

class Graph {
public:
    explicit Graph(int direction = true) {
        _directed = direction;
    }

    size_t size() const {
        return _vs.size();
    }

    void add_edge(int weight, int from, int to) {
        if (from < 0 || to < 0 || from >= _vs.size() || to >= _vs.size()) {
            return;
        }
        _vs[from].edges.emplace(weight, &_vs[to]);
        if (!_directed) {
            _vs[to].edges.emplace(weight, &_vs[from]);
        }
    }

    void add_vertex(int v) {
        _vs.emplace_back(v);
    }

    /**
     * @param ins   edges, <weight, from_index>
     * @param outs  edges, <weight, to>
     */
    void add_vertex(int v, const std::vector<std::pair<int, int>>& ins,
            const std::vector<std::pair<int, int>>& outs) {
        _vs.emplace_back(v);
        for (auto& in : ins) {
            if (in.second >= 0 && in.second < _vs.size() - 1) { // except new node
                _vs[in.second].add_edge(in.first, &_vs.back());
                if (!_directed) {
                    _vs.back().add_edge(in.first, &_vs[in.second]);
                }
            }
        }
        for (auto& out : outs) {
            if (out.second >= 0 && out.second < _vs.size()) {
                _vs.back().add_edge(out.first, &_vs[out.second]);
                if (!_directed) {
                    _vs[out.second].add_edge(out.first, &_vs.back());

                }
            }
        }
    }

    void reverse() {
        if (!_directed) {
            return;
        }

        size_t len = _vs.size();
        std::vector<bool> visited(len, false);
        std::deque<GraphVertex*> qq{&_vs[0]};
        visited[0] = true;
        while (!qq.empty()) {
            for (size_t i = qq.size(); i > 0; --i) {
                GraphVertex* v = qq.front();
                qq.pop_front();

                for (auto iter = v->edges.begin(); iter != v->edges.end();) {
                    if (visited[iter->to->val]) {
                        ++iter;
                        continue;
                    }
                    visited[iter->to->val] = true;

                    qq.emplace_back(iter->to);
                    iter->to->add_edge(iter->weight, v);
                    iter = v->edges.erase(iter);
                }
            }
        }
    }

    std::vector<int> dfs_traversal(int start) {
        size_t len = _vs.size();
        std::vector<bool> visited(len, false);
        std::vector<int> res;
        std::function<void(GraphVertex*)> r_func;
        r_func = [&](GraphVertex* v) {
            if (visited[v->val]) {
                return;
            }
            visited[v->val] = true;
            res.emplace_back(v->val);
            for (auto& edge : v->edges) {
                r_func(edge.to);
            }
        };
        r_func(&_vs[start]);
        return res;
    }

    std::vector<int> bfs_traversal(int start) {
        size_t len = _vs.size();
        std::vector<bool> visited(len, false);
        std::vector<int> res;
        std::deque<GraphVertex*> qq{&_vs[start]};
        while (!qq.empty()) {
            for (size_t i = qq.size(); i > 0; --i) {
                GraphVertex* v = qq.front();
                qq.pop_front();
                if (visited[v->val]) {
                    continue;
                }
                visited[v->val] = true;
                res.emplace_back(v->val);
                for (auto& edge : v->edges) {
                    qq.emplace_back(edge.to);
                }
            }
        }
        return res;
    }

    std::vector<std::vector<int>> min_paths_dijkstra(int start) {
        size_t len = _vs.size();
        if (start < 0 || start >= len) {
            return {};
        }
        std::map<GraphVertex*, int> cc; // <node index, dist start>
        std::map<GraphVertex*, GraphVertex*> parent;
        for (size_t i = 0; i < len; ++i) {
            cc.emplace(&_vs[i], i == start ? 0 : INT_MAX);
            if (i == start) {
                parent[&_vs[i]] = nullptr;
            }
        }

        while (!cc.empty()) {
            // find minimum from cc, TODO.. more efficient
            GraphVertex* vertex = cc.begin()->first;
            int min = cc.begin()->second;
            for (auto& entry : cc) {
                if (entry.second < min) {
                    vertex = entry.first;
                    min = entry.second;
                }
            }

            cc.erase(vertex);

            for (auto& edge : vertex->edges) {
                auto entry = cc.find(edge.to);
                if (entry != cc.end() && min + edge.weight < entry->second) {
                    entry->second = min + edge.weight;
                    parent[edge.to] = vertex;
                }
            }
        }

        std::vector<std::vector<int>> res;
        for (size_t i = 0; i < len; ++i) {
            GraphVertex* p = &_vs[i];
            std::vector<int> path;
            while (p != nullptr) {
                auto entry = parent.find(p);
                if (entry == parent.end()) {
                    break;
                }
                path.emplace_back(p->val);
                p = entry->second;
            }
            if (!path.empty()) {
                path.insert(path.begin(), cc[&_vs[i]]);
            }
            res.emplace_back(path);
        }
        return res;
    }

    /**
        - From start point, search at most for (v-1) times.
        - Only which edges relax happend that will going to next round search.
          It's easy to use queue to do this
        - Negative weight circle exist if search time over v-1 and there still relax happend,
          and minimum path is meaningless.
     */
    std::vector<std::vector<int>> min_paths_bellman_ford_spfa(int start) {
        size_t len = _vs.size();
        if (start < 0 || start >= len) {
            return {};
        }
        std::map<GraphVertex*, int> cc; // <node index, dist start>
        std::map<GraphVertex*, GraphVertex*> parent;
        GraphVertex* vertex = &_vs[start];
        cc[vertex] = 0;
        parent[vertex] = nullptr;

        int idx = 0;
        std::deque<GraphVertex*> qq{vertex};
        while (!qq.empty()) {
            if (idx++ > _vs.size() - 1) {
                // negetive circle exist, loop time more than count(vertex) - 1
                return {};
            }
            for (size_t i = qq.size(); i > 0; --i) {
                vertex = qq.front();
                qq.pop_front();
                for (auto& edge : vertex->edges) {
                    auto cc_entry = cc.find(edge.to);
                    if (cc_entry == cc.end() || cc[vertex] + edge.weight < cc_entry->second) {
                        cc[edge.to] = cc[vertex] + edge.weight;
                        parent[edge.to] = vertex;

                        if (!qq.empty() && cc[edge.to] < cc[qq.front()]) { // SLF
                            qq.emplace_front(edge.to);
                        } else {
                            qq.emplace_back(edge.to);
                        }
                    }
                }
            }
        }

        std::vector<std::vector<int>> res;
        for (size_t i = 0; i < len; ++i) {
            GraphVertex* p = &_vs[i];
            std::vector<int> path;
            while (p != nullptr) {
                auto entry = parent.find(p);
                if (entry == parent.end()) {
                    break;
                }
                path.emplace_back(p->val);
                p = entry->second;
            }
            if (!path.empty()) {
                path.insert(path.begin(), cc[&_vs[i]]);
            }
            res.emplace_back(path);
        }
        return res;
    }

    /**
        If valus on diagonal of distance is negative,
        then there is a negative weight circle in graph
     */
    std::vector<std::vector<std::vector<int>>> all_min_paths_floyd_warshall() {
        size_t len = _vs.size();
        std::vector<std::vector<int>> dist(len, std::vector<int>(len, INT_MAX));
        std::vector<std::vector<int>> parents(len, std::vector<int>(len, -1));
        for (size_t i = 0; i < len; ++i) {
            for (size_t j = 0; j < len; ++j) {
                if (i == j) {
                    dist[i][j] = 0;
                    continue;
                }
                GraphEdge edge(0, &_vs[j]);
                auto entry = _vs[i].edges.find(edge);
                if (entry != _vs[i].edges.end()) { // there is a edge
                    dist[i][j] = entry->weight;
                    parents[i][j] = i;
                }
            }
        }

        for (size_t k = 0; k < len; ++k) {
            for (size_t i = 0; i < len; ++i) {
                for (size_t j = 0; j < len; ++j) {
                    if (dist[i][k] == INT_MAX || dist[k][j] == INT_MAX) {
                        continue;
                    }
                    if (dist[i][k] + dist[k][j] < dist[i][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                        parents[i][j] = parents[k][j];
                    }
                }
            }
        }

        for (size_t i = 0; i < len; ++i) {
            if (dist[i][i] < 0) {
                return {};
            }
        }

        std::vector<std::vector<std::vector<int>>> res;
        for (int i = 0; i < len; ++i) {
            // search i -> each j's paths
            std::vector<std::vector<int>> paths;
            for (int j = 0; j < len; ++j) {
                // construct i -> j each node
                std::vector<int> one_path;
                for (int idx = j; idx != -1 && idx != i; idx = parents[i][idx]) {
                    one_path.insert(one_path.begin(), idx);
                }
                one_path.insert(one_path.begin(), i);
                paths.emplace_back(one_path);
            }
            res.emplace_back(paths);
        }
        return res;
    }

private:
    bool _directed = true;
    std::vector<GraphVertex> _vs;
};

// TODO... nearest coordinates

FTEST(test_graph) {
    int A = 0;
    int B = 1;
    int C = 2;
    int D = 3;
    int E = 4;
    int F = 5;

    auto dijkstra = [&](const std::vector<int>& vertexs,
            const std::vector<std::tuple<int, int, int>>& pairs, int start) {
        Graph graph(false);
        for (auto& vertex : vertexs) {
            graph.add_vertex(vertex);
        }
        for (auto& pair : pairs) {
            graph.add_edge(std::get<0>(pair), std::get<1>(pair), std::get<2>(pair));
        }
        LOG(INFO) << "dfs start at " << start << ": " << graph.dfs_traversal(start);
        LOG(INFO) << "bfs start at " << start << ": " << graph.bfs_traversal(start);
        LOG(INFO) << "dijkstra start at " << start << ": " << graph.min_paths_dijkstra(start);
    };

    auto spfa = [&](const std::vector<int>& vertexs,
            const std::vector<std::tuple<int, int, int>>& pairs, int start) {
        Graph graph;
        for (auto& vertex : vertexs) {
            graph.add_vertex(vertex);
        }
        for (auto& pair : pairs) {
            graph.add_edge(std::get<0>(pair), std::get<1>(pair), std::get<2>(pair));
        }
        LOG(INFO) << "dfs start at " << start << ": " << graph.dfs_traversal(start);
        LOG(INFO) << "bfs start at " << start << ": " << graph.bfs_traversal(start);
        const auto& re = graph.min_paths_bellman_ford_spfa(start);
        if (re.empty()) {
            LOG(INFO) << "spfa negetive circle detected";
        } else {
            LOG(INFO) << "spfa start at " << start << ": " << re;
        }

        const auto& all_re = graph.all_min_paths_floyd_warshall();
        if (all_re.empty()) {
            LOG(INFO) << "flyod negetive circle detected";
        } else {
            for (size_t i = 0; i < all_re.size(); ++i) {
                LOG(INFO) << "flyod start at " << i << ": " << all_re[i];
            }
        }
    };

    auto reverse = [&](const std::vector<int>& vertexs,
            const std::vector<std::tuple<int, int, int>>& pairs) {
        Graph graph;
        for (auto& vertex : vertexs) {
            graph.add_vertex(vertex);
        }
        for (auto& pair : pairs) {
            graph.add_edge(std::get<0>(pair), std::get<1>(pair), std::get<2>(pair));
        }
        LOG(INFO) << "reverse before " << graph.bfs_traversal(0);
        graph.reverse();
        LOG(INFO) << "reverse after " << graph.bfs_traversal(graph.size() - 1);
    };

    /**
          1     2
       A --→ B --→ C
     */
    dijkstra({A, B, C}, {{1, A, B}, {2, B, C}}, A);
    spfa({A, B, C}, {{1, A, B}, {2, B, C}}, A);
    reverse({A, B, C}, {{1, A, B}, {2, B, C}});

    /**
          1     2
       A --→ B ←-- C
     */
    spfa({A, B, C}, {{1, A, B}, {2, C, B}}, A);
    spfa({A, B, C}, {{1, A, B}, {2, C, B}}, B);
    spfa({A, B, C}, {{1, A, B}, {2, C, B}}, C);
    reverse({A, B, C}, {{1, A, B}, {2, C, B}});

    /**
               2
           B ----→ C
      5   ↗        | 3
        /    9     ↓
       A --------→ D
      2 ↘          ↘ 2
         E -------→ F
              3
    */
    dijkstra({A, B, C, D, E, F}, {{5, A, B}, {9, A, D}, {2, A, E}, {2, B, C},
            {3, E, F}, {3, C, D}, {2, F, D}}, A);
    spfa({A, B, C, D, E, F}, {{5, A, B}, {9, A, D}, {2, A, E}, {2, B, C},
            {3, E, F}, {3, C, D}, {2, F, D}}, A);
    reverse({A, B, C, D, E, F}, {{5, A, B}, {9, A, D}, {2, A, E}, {2, B, C},
            {3, E, F}, {3, C, D}, {2, F, D}});

    /**
               2
           B ----→ C
      5   ↗        | 3
        /    9     ↓
       A --------→ D
      2 ↘          ↖ 2
         E -------→ F
              3
    */
    spfa({A, B, C, D, E, F}, {{5, A, B}, {9, A, D}, {2, A, E}, {2, B, C},
            {3, E, F}, {3, C, D}, {2, D, F}}, A);
    spfa({A, B, C, D, E, F}, {{5, A, B}, {9, A, D}, {2, A, E}, {2, B, C},
            {3, E, F}, {3, C, D}, {2, D, F}}, B);
    spfa({A, B, C, D, E, F}, {{5, A, B}, {9, A, D}, {2, A, E}, {2, B, C},
            {3, E, F}, {3, C, D}, {2, D, F}}, C);
    spfa({A, B, C, D, E, F}, {{5, A, B}, {9, A, D}, {2, A, E}, {2, B, C},
            {3, E, F}, {3, C, D}, {2, D, F}}, D);
    spfa({A, B, C, D, E, F}, {{5, A, B}, {9, A, D}, {2, A, E}, {2, B, C},
            {3, E, F}, {3, C, D}, {2, D, F}}, E);
    spfa({A, B, C, D, E, F}, {{5, A, B}, {9, A, D}, {2, A, E}, {2, B, C},
            {3, E, F}, {3, C, D}, {2, D, F}}, F);
    reverse({A, B, C, D, E, F}, {{5, A, B}, {9, A, D}, {2, A, E}, {2, B, C},
            {3, E, F}, {3, C, D}, {2, D, F}});


    /**

          8  /---→ D ---┐
           /       ↑   ↓ 2
         A       1 └-- E
       4 | \ 5        ↑
         ↓  ↘       /
         B → C ---/  4
          -3
     */
    spfa({A, B, C, D, E}, {{4, A, B}, {5, A, C}, {8, A, D}, {-3, B, C},
            {4, C, E}, {1, E, D}, {2, D, E}}, A);
    spfa({A, B, C, D, E}, {{4, A, B}, {5, A, C}, {8, A, D}, {-3, B, C},
            {4, C, E}, {1, E, D}, {2, D, E}}, B);
    spfa({A, B, C, D, E}, {{4, A, B}, {5, A, C}, {8, A, D}, {-3, B, C},
            {4, C, E}, {1, E, D}, {2, D, E}}, C);
    spfa({A, B, C, D, E}, {{4, A, B}, {5, A, C}, {8, A, D}, {-3, B, C},
            {4, C, E}, {1, E, D}, {2, D, E}}, D);
    spfa({A, B, C, D, E}, {{4, A, B}, {5, A, C}, {8, A, D}, {-3, B, C},
            {4, C, E}, {1, E, D}, {2, D, E}}, E);
    reverse({A, B, C, D, E}, {{4, A, B}, {5, A, C}, {8, A, D}, {-3, B, C},
            {4, C, E}, {1, E, D}, {2, D, E}});

    /**
          10    20
       A --→ B --→ C
       ↑     8     │
       └───────────┘
     */
    dijkstra({A, B, C}, {{10, A, B}, {20, B, C}, {8, C, A}}, A);
    dijkstra({A, B, C}, {{10, A, B}, {20, B, C}, {8, C, A}}, B);
    dijkstra({A, B, C}, {{10, A, B}, {20, B, C}, {8, C, A}}, C);
    spfa({A, B, C}, {{10, A, B}, {20, B, C}, {8, C, A}}, A);
    spfa({A, B, C}, {{10, A, B}, {20, B, C}, {8, C, A}}, B);
    spfa({A, B, C}, {{10, A, B}, {20, B, C}, {8, C, A}}, C);
    reverse({A, B, C}, {{10, A, B}, {20, B, C}, {8, C, A}});

    /**
          3     4
       A --→ B --→ C
       ↑    -8     │
       └───────────┘
     */
    spfa({A, B, C}, {{3, A, B}, {4, B, C}, {-8, C, A}}, A);
    spfa({A, B, C}, {{3, A, B}, {4, B, C}, {-8, C, A}}, B);
    spfa({A, B, C}, {{3, A, B}, {4, B, C}, {-8, C, A}}, C);
    reverse({A, B, C}, {{3, A, B}, {4, B, C}, {-8, C, A}});
}

int count_of_graph(std::vector<std::vector<int>>& matrix) {
    if (matrix.empty() || matrix.front().size() != matrix.size()) {
        return 0;
    }
    int n = matrix.size();

    auto BFS_method = [&] {
        std::map<int, std::vector<int>> nexts;
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (matrix[i][j]) {
                    nexts[i].emplace_back(j);
                }
            }
        }
        int res = 0;
        while (!nexts.empty()) {
            std::queue<int> qq{{nexts.begin()->first}};
            while (!qq.empty()) {
                for (size_t i = qq.size(); i > 0; --i) {
                    int x = qq.front();
                    qq.pop();
                    if (nexts.count(x) == 0) {
                        continue;
                    }
                    for (int next : nexts[x]) {
                        qq.emplace(next);
                    }
                    nexts.erase(x);
                }
            }
            ++res;
        }
        return res;
    };
    auto DFS_method = [&] {
        std::function<bool(int)> rfunc;
        rfunc = [&](int start) {
            bool flag = false;
            for (int i = start + 1; i < n; ++i) {
                if (matrix[start][i]) {
                    flag = true;
                    matrix[start][i] = 0;
                    rfunc(i);
                }
            }
            return flag;
        };
        int res = 0;
        for (int i = 0; i < n; ++i) {
            if (rfunc(i)) {
                ++res;
            }
        }
        return res;
    };
    return DFS_method();
}

FTEST(test_count_of_graph) {
    auto t = [](const std::vector<std::vector<int>>& matrix) {
        std::vector<std::vector<int>> nns = matrix;
        auto re = count_of_graph(nns);
        LOG(INFO) << matrix << " count of graph: " << re;
        return re;
    };

    FEXP(t({
            {1, 1, 0},
            {1, 1, 1},
            {0, 1, 1}}), 1);
    FEXP(t({
            {1, 1, 1, 0, 0},
            {1, 1, 1, 0, 0},
            {1, 1, 1, 0, 0},
            {0, 0, 0, 1, 1},
            {0, 0, 0, 1, 1}}), 2);
    FEXP(t({
            {1, 1, 0, 0, 1},
            {1, 1, 0, 0, 0},
            {0, 0, 1, 1, 0},
            {0, 0, 1, 1, 0},
            {1, 0, 0, 0, 1}}), 2);
}