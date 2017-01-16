#include <iomanip>
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
    {"config", "Configuration file"}, {"verbose", "Verbose output", "yes"},
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

    std::cout << std::fixed << std::setprecision(4);

    config cfg = config::read_ini(opts.get<string>("config"));
    database attrib;  // TODO dummy object

    auto in = cfg["input"];
    topology topo = topology::read_csv(in.get<string>("topology"));

    verbose() << "Configuration:\n" << cfg;
    verbose() << "Topology:\n" << topo;
    verbose() << '\n';

    //
    // Object test --side quest--
    //

    // class dummy : public node {
    //    public:
    //     dummy(std::string name) : name(name){};
    //     std::string name;
    // };
    //
    // dummy a("a"), b("b"), c("c"), d("d"), e("e"), f("f"), g("g");
    // a.connections.push_back(&c);  // Directed graph test
    // a.connections.push_back(&b);
    // a.connections.push_back(&e);
    // a.connections.push_back(&f);
    // // b.connections.push_back(&a);
    // // c.connections.push_back(&a);
    // c.connections.push_back(&d);
    // // d.connections.push_back(&c);
    // d.connections.push_back(&e);
    // // e.connections.push_back(&d);
    // // e.connections.push_back(&a);
    // // e.connections.push_back(&f);
    // e.connections.push_back(&g);
    // // f.connections.push_back(&a);
    // f.connections.push_back(&e);
    // f.connections.push_back(&g);
    // // g.connections.push_back(&e);
    // // g.connections.push_back(&f);
    //
    // topology dummy_topo =
    // topology::generate_topology(graph_builder::bfs(&a));
    // topology dummy_topo_draw =
    //     topology::generate_topology(graph_builder::bfs(&a));
    // dummy_topo.fix_identity();
    // verbose() << dummy_topo;

    compute system(topo);
    system.generate_eigenvectors();

    auto iters = cfg["compute"].get<int>("iterations");
    for (int i = 0; i < iters; ++i) {
        backend::plot(cfg, topo, system.get_points(), attrib,
                      std::string("-") + std::to_string(i));
        std::cout << "Iter " << i << '\n';
        system.update();
    }

    system.normalize();
    backend::plot(cfg, topo, system.get_points(), attrib, "-final");

    //
    // -----
    //
} catch (const std::exception &ex) {
    cerr << "error: " << ex.what() << endl;
    return EXIT_FAILURE;
}
