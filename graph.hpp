#pragma once

#include "util.hpp"

///////////////////////////////////////////////////////////////////////////////////////////////////

struct GraphNode {
    explicit GraphNode(int value) : v(value) {}

    int v = 0;
    std::vector<GraphNode*> ps;
};
