#include <iostream>
#include <vector>

#include "backend/backend.hpp"
#include "common/topology.hpp"
#include "utils/log.hpp"
#include "utils/option.hpp"

using namespace std;

// Command line options
option_list opts = {
    {"topo", "Topology file"},
    {"filters", "List of filters"},
    {"verbose", "Verbose output", "no"},
    {"save-csv", "Save topology"},
    {"save-dat"},
};

std::ostream &verbose() {
    static bool v = opts.get<bool>("verbose");
    return log_if(v);
}

int main(int argc, char **argv) try {
    if (argc == 1) {
        opts.show_help();
        return 0;
    }

    opts.parse(argc - 1, argv + 1);

    string topo_file = opts.get<string>("topo");
    verbose() << "parsing topology file: " << topo_file << '\n';
    topology topo = topology::read_csv(opts.get<string>("topo"));

    if (opts.is_set("save-csv")) {
        verbose() << "saving topology as csv";
        topo.save_csv(opts["save-csv"]);
    }

    verbose() << topo;

    // Just to show off..
    vector<string> filters = opts.get_all<string>("filters");
    if (filters.size() > 0) {
        verbose() << "filters:\n";
        for (auto &filter : filters) {
            verbose() << "- " << filter << '\n';
        }
    }

} catch (const std::exception &ex) {
    cerr << "error: " << ex.what() << endl;
    return EXIT_FAILURE;
}
