#ifndef GRAPH_BUILDER_HPP
#define GRAPH_BUILDER_HPP

#include <iostream>
#include <queue>
#include <vector>

#include <gsl/gsl_matrix.h>

#include "../topology.hpp"
#include "node.hpp"

namespace graph_builder {
std::vector<node *> bfs(node *start);
};

#endif
