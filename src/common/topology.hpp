#pragma once

#include <vector>

class topology {
    std::vector<int> values;
    std::vector<int> columns;
    std::vector<int> row_index;

   public:
    inline int size() const { return row_index.size(); }
    void read_csv(const std::string &filename, char delim = ' ');
};
