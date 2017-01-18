#include "graph_builder.hpp"

using namespace std;

vector<node *> graph_builder::bfs(node *start) {
    vector<node *> graph;
    queue<node *> queue;

    queue.push(start);

    while (!queue.empty()) {
        node *root = queue.front();
        queue.pop();
        if (!root->mark) {
            root->mark = true;
            graph.push_back(root);
            for (node *child : root->connections) {
                queue.push(child);
            }
        }
    }

    for (node *n : graph) {
        n->mark = false;
    }

    return graph;
}
