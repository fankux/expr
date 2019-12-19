#pragma once

#include "util.hpp"

///////////////////////////////////////////////////////////////////////////////////////////////////

class GraphNode {
public:
    int val;
    std::vector<Node*> neighbors;

    GraphNode() = default;

    GraphNode(int _val, std::vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};

