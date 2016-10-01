#include <iostream>
#include <vector>

#include "backend/backend.hpp"
#include "common/database.hpp"
#include "common/topology.hpp"
#include "utils/log.hpp"
#include "utils/option.hpp"

using namespace std;

// Command line options
option_list opts = {
    {"topo", "Topology file"},
    {"pos", "Positions for each node"},
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

    verbose() << "Topology:\n" << topo;
    verbose() << "Positions:\n" << pos;

    verbose() << '\n';

    auto rec = pos[0];
    verbose() << "node " << rec["node"] << ": (" << rec["xpos"] << ','
              << rec["ypos"] << ")\n";

    auto xpos = pos.values<double>("xpos");
    verbose() << "x positions:";
    for (auto &x : xpos) {
        verbose() << ' ' << x;
    }
    verbose() << '\n';

    auto ypos = pos.where([&](const database::record &r) {
        return r.get<double>("ypos") == 0;
    });
    verbose() << "nodes with y=0:";
    for (auto &y : ypos) {
        verbose() << ' ' << pos[y]["node"];
    }
    verbose() << '\n';

} catch (const std::exception &ex) {
    cerr << "error: " << ex.what() << endl;
    return EXIT_FAILURE;
}
