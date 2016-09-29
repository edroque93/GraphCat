#pragma once

#include <string>
#include <vector>

class Graph {
    std::vector<int> mat_a_;
    std::vector<int> mat_ai_;
    std::vector<int> mat_aj_;

   public:
    void read_csv(const std::string &filename, char delim = ',');

    // inline int num_nodes() { return offsets_.length(); }

    Graph(){};
    virtual ~Graph(){};
};
