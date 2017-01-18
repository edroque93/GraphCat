#include <iomanip>
#include <iostream>
#include <vector>

#include "backend.hpp"
#include "compute.hpp"
#include "support/config.hpp"
#include "support/option.hpp"
#include "topology.hpp"

#ifndef GCAT_CONFIG
#define GCAT_CONFIG "~/.gcatrc"
#endif

using namespace std;

// Command line options
option_list opts = {{"config", "Configuration file"},
                    {"topology", "Topology file"},
                    {"iters", "Number of iterations"}};

void setup_env() { std::cout << std::fixed << std::setprecision(4); }

int main(int argc, char **argv) try {
    setup_env();
    opts.parse(argc - 1, argv + 1);

    config cfg = config::read_ini(opts.get<string>("config", GCAT_CONFIG));

    topology topo = topology::read_csv(
        opts.get<string>("topology", cfg["input"]["topology"]));

    cout << "Initializing system\n";

    compute sys(topo);
    sys.generate_eigenvectors();

    auto iters = opts.get<int>("iters", cfg["compute"].get<int>("iterations"));
    for (int i = 0; i < iters; ++i) {
        backend::plot(cfg, topo, sys.get_points(), string("-") + to_string(i));
        cout << "Iter " << i << '\n';
        sys.update();
    }
    backend::plot(cfg, topo, sys.get_points(), string("-") + to_string(iters));

} catch (const std::exception &ex) {
    cerr << "error: " << ex.what() << endl;
    return EXIT_FAILURE;
}
