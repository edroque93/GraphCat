#include <cstdio>
#include <iomanip>
#include <iostream>
#include <vector>

#include <sys/time.h>

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
                    {"iters", "Number of iterations"},
                    {"output", "Output file"},
                    {"animate", "Draw each frame"}};

void setup_env() { std::cout << std::fixed << std::setprecision(4); }

double get_time_ms() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_usec * 1e-3 + tv.tv_sec * 1e3;
}

int main(int argc, char **argv) try {
    setup_env();
    opts.parse(argc - 1, argv + 1);

    config cfg = config::read_ini(opts.get<string>("config", GCAT_CONFIG));

    topology topo = topology::read_csv(
        opts.get<string>("topology", cfg["input"]["topology"]));

    cout << "Initializing system\n";
    compute sys(topo);
    sys.generate_eigenvectors();

    backend be(topo);

    auto output = cfg["output"];
    be.set_width(output.get<int>("width", 512));
    be.set_height(output.get<int>("height", 512));
    be.set_margin(output.get<int>("margin", 16));
    be.set_margin(
        output.get<canvas::img_format>("type", canvas::img_format::PNG));

    string outfile =
        opts.get<string>("output", output.get<string>("filename", "out"));
    bool animate =
        opts.get<bool>("animate", output.get<bool>("animate", false));

    int iters = opts.get<int>("iters", cfg["compute"].get<int>("iterations"));
    if (iters > 1000) {
        cout << "Too many frames for animation\n";
        animate = false;
    }
    char buffer[5];
    bool converged = false;
    double start = get_time_ms();
    for (int i = 0; i < iters && !converged; ++i) {
        if (animate) {
            sprintf(buffer, "-%03d", i);
            be.plot(sys.get_points(), outfile + buffer);
        }
        converged = sys.update();
        cout << "Iteration " << (i + 1) << ": " << (get_time_ms() - start)*1e-3
             << " s\n";
        if (converged) cout << "=> Converged\n";
    }

    if (animate) {
        sprintf(buffer, "-%03d", iters);
        be.plot(sys.get_points(), outfile + buffer);
    } else {
        be.plot(sys.get_points(), outfile);
    }

} catch (const std::exception &ex) {
    cerr << "error: " << ex.what() << endl;
    return EXIT_FAILURE;
}
