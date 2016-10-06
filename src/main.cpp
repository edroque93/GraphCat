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

using namespace std;

// Command line options
option_list opts = {
    {"config", "Configuration file"},
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

    config cfg = config::read_ini(opts.get<string>("config"));
    database pos; // TODO dummy object
    
    auto in = cfg["input"];
    topology topo = topology::read_csv(in.get<string>("topology"));

    verbose() << "Configuration:\n" << cfg;
    verbose() << "Topology:\n" << topo;
    verbose() << '\n';

    topo.fix_identity();  // Im lazy
    vector<double> x, y;
    compute c(topo);
    c.generate_eigenvectors(x, y);

    backend b = backend(topo, x, y, pos);
    b.plot(cfg);

} catch (const std::exception &ex) {
    cerr << "error: " << ex.what() << endl;
    return EXIT_FAILURE;
}
