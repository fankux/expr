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
        return weight < rhs.weight;
    }
};

struct GraphVertex {
    int val;
    std::multiset<GraphEdge> edges;  // <weight, next node>

    GraphVertex() = default;

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
        _direction = direction;
    }

    void add_edge(int from, int to, int weight) {
        if (from < 0 || to < 0 || from >= _ns.size() || to >= _ns.size()) {
            return;
        }
        _ns[from].edges.emplace(weight, &_ns[to]);
        if (!_direction) {
            _ns[to].edges.emplace(weight, &_ns[from]);
        }
    }

    void add_vertex(int v) {
        _ns.emplace_back(v);
    }

    /**
     * @param ins   edges, <weight, from_index>
     * @param outs  edges, <weight, to>
     */
    void add_vertex(int v, const std::vector<std::pair<int, int>>& ins,
            const std::vector<std::pair<int, int>>& outs) {
        _ns.emplace_back(v);
        for (auto& in : ins) {
            if (in.second >= 0 && in.second < _ns.size() - 1) { // except new node
                _ns[in.second].add_edge(in.first, &_ns.back());
                if (!_direction) {
                    _ns.back().add_edge(in.first, &_ns[in.second]);
                }
            }
        }
        for (auto& out : outs) {
            if (out.second >= 0 && out.second < _ns.size()) {
                _ns.back().add_edge(out.first, &_ns[out.second]);
                if (!_direction) {
                    _ns[out.second].add_edge(out.first, &_ns.back());

                }
            }
        }
    }

    std::vector<std::vector<int>> min_paths(int from) {
        size_t len = _ns.size();
        if (from < 0 || from >= len) {
            return {};
        }
        std::map<GraphVertex*, int> cc; // <node index, dist from>
        std::map<GraphVertex*, GraphVertex*> parent;
        for (size_t i = 0; i < len; ++i) {
            cc.emplace(&_ns[i], i == from ? 0 : INT_MAX);
            if (i == from) {
                parent[&_ns[i]] = nullptr;
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
            GraphVertex* p = &_ns[i];
            std::vector<int> path;
            while (p != nullptr) {
                auto entry = parent.find(p);
                if (entry != parent.end()) {
                    path.emplace_back(p->val);
                    p = entry->second;
                }
            }
            res.emplace_back(path);
        }
        return res;
    }

private:
    bool _direction = true;
    std::vector<GraphVertex> _ns;
};

// TODO... A->B min path
// TODO... negtive weight
// TODO... traversal
// TODO... nearest coordinates
// TODO... Graph reverse

/**
               2
           B ----- C
      5   /        | 3
        /    9     |
       A --------- D
      2 \          \ 2
         E -------- F
              3
 */
FTEST(test_graph) {
    int A = 0;
    int B = 1;
    int C = 2;
    int D = 3;
    int E = 4;
    int F = 5;

    Graph graph(false);
    graph.add_vertex(A);
    graph.add_vertex(B);
    graph.add_vertex(C);
    graph.add_vertex(D);
    graph.add_vertex(E);
    graph.add_vertex(F);
    graph.add_edge(A, B, 5);
    graph.add_edge(A, D, 9);
    graph.add_edge(A, E, 2);
    graph.add_edge(B, C, 2);
    graph.add_edge(E, F, 3);
    graph.add_edge(C, D, 3);
    graph.add_edge(F, D, 2);

    LOG(INFO) << graph.min_paths(A);
}
