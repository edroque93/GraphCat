#include <iostream>
#include <vector>

#include "backend/backend.hpp"
#include "common/database.hpp"
#include "common/topology.hpp"
// TODO common or utils?
#include "common/config.hpp"
#include "utils/log.hpp"
#include "utils/option.hpp"

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

    topology topo = topology::read_csv(opts.get<string>("topo"));
    database pos = database::read_csv(opts.get<string>("pos"));
    database fmt = database::read_csv(opts.get<string>("fmt"));

    verbose() << "Topology:\n" << topo;
    verbose() << "Positions:\n" << pos;
    verbose() << "Format:\n" << fmt;

    verbose() << '\n';

    backend b = backend(topo, pos.values<double>("xpos"),
                        pos.values<double>("ypos"), pos);
    b.plot(fmt);
} catch (const std::exception &ex) {
    cerr << "error: " << ex.what() << endl;
    return EXIT_FAILURE;
}
