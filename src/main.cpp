#include <iomanip>
#include <iostream>
#include <vector>

#include "backend.hpp"
#include "compute.hpp"
#include "support/config.hpp"
#include "support/option.hpp"
#include "topology.hpp"

using namespace std;

// Command line options
option_list opts = {
    {"config", "Configuration file"}, {"verbose", "Verbose output", "yes"},
};

int main(int argc, char **argv) try {
    if (argc == 1) {
        opts.show_help();
        return 0;
    }

    opts.parse(argc - 1, argv + 1);

    std::cout << std::fixed << std::setprecision(4);

    config cfg = config::read_ini(opts.get<string>("config"));

    auto in = cfg["input"];
    topology topo = topology::read_csv(in.get<string>("topology"));

    compute system(topo);
    system.generate_eigenvectors();

    auto iters = cfg["compute"].get<int>("iterations");
    for (int i = 0; i < iters; ++i) {
        backend::plot(cfg, topo, system.get_points(),
                      std::string("-") + std::to_string(i));
        std::cout << "Iter " << i << '\n';
        system.update();
    }

    system.normalize();
    backend::plot(cfg, topo, system.get_points(), "-final");

} catch (const std::exception &ex) {
    cerr << "error: " << ex.what() << endl;
    return EXIT_FAILURE;
}
