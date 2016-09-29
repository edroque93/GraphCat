#include <iostream>
#include <vector>

#include <cairo/cairo-svg.h>

#include "option.hpp"

using namespace std;

void show_usage(char *progname) {
    cout << "usage: " << progname << " [args]" << endl;
    exit(0);
}

int main(int argc, char **argv) try {
    std::vector<int> nums = {};
    std::vector<std::string> files = {};
    int iters = 10;

    OptionParser opts;
    opts.add("numbers", nums)
        .add("iters", iters)
        .add("files", files)
        .add("help", [&](int, char **) {
            show_usage(argv[0]);
            return 0;
        });

    opts.parse(argc - 1, argv + 1);

    cout << "Numbers =";
    for (auto &num : nums) {
        cout << ' ' << num;
    }
    cout << endl;
    cout << "Iterations = " << iters << endl;
    cout << "Files =" << endl;
    for (auto &file : files) {
        cout << "- " << file << endl;
    }

    Node a;

} catch (const std::exception &ex) {
    cerr << "error: " << ex.what() << endl;
    return -1;
}
