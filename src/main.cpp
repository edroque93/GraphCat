#include <iostream>
#include <vector>

#include "backend/backend.hpp"
#include "common/database.hpp"
#include "common/topology.hpp"
#include "compute/compute.hpp"
// TODO common or utils?
#include "common/config.hpp"
#include "utils/log.hpp"
#include "utils/option.hpp"

#include "builder/graph_builder.hpp"
#include "builder/node.hpp"

using namespace std;

// Command line options
option_list opts = {
    {"topo", "Topology file"},
    {"pos", "Positions for each node"},
    {"fmt", "Output file(s) format"},
    {"verbose", "Verbose output", "yes"},
};

ostream &verbose() {
    static bool v = opts.get<bool>("verbose");
    return log_if(v);
}

int main(int argc, char **argv) try {
    if (argc == 1) {
        opts.show_help();
        return 0;
    }

    opts.parse(argc - 1, argv + 1);

    class dummy : public node {
       public:
        dummy(std::string name) : name(name){};
        std::string name;
    };

    dummy a("a"), b("b"), c("c"), d("d"), e("e"), f("f"), g("g");
    a.connections.push_back(&c);
    a.connections.push_back(&b);
    a.connections.push_back(&e);
    a.connections.push_back(&f);
    b.connections.push_back(&a);
    c.connections.push_back(&a);
    c.connections.push_back(&d);
    d.connections.push_back(&c);
    d.connections.push_back(&e);
    e.connections.push_back(&d);
    e.connections.push_back(&a);
    e.connections.push_back(&f);
    e.connections.push_back(&g);
    f.connections.push_back(&a);
    f.connections.push_back(&e);
    f.connections.push_back(&g);
    g.connections.push_back(&e);
    g.connections.push_back(&f);

    topology dummy_topo = topology::generate_topology(graph_builder::bfs(&a));
    verbose() << dummy_topo;
    vector<double> x, y;
    compute comp(dummy_topo);
    comp.generate_eigenvectors(x, y);
    backend back = backend(dummy_topo, x, y, pos);
    back.plot(fmt);
} catch (const std::exception &ex) {
    cerr << "error: " << ex.what() << endl;
    return EXIT_FAILURE;
}
