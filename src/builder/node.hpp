#ifndef NODE_HPP
#define NODE_HPP

#include <iostream>

class node {
   public:
    node(){};
    ~node(){};

    // void paint();
    std::vector<node *> connections;
    bool mark = false;
};

#endif
