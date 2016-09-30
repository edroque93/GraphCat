#include "option.hpp"

#include <algorithm>
#include <stdlib.h>

extern char *__progname;

using namespace std;

std::vector<option_desc>::iterator option_list::find(const std::string &lab) {
  auto it = find_if(opts.begin(), opts.end(),
                    [&](const option_desc &o) { return o.label == lab; });
  if (it == opts.end()) {
    throw std::runtime_error("option -" + lab + " not found");
  }
  return it;
}

const string &option_list::operator[](const std::string &lab) {
  return find(lab)->value;
}

bool option_list::is_set(const std::string &lab) {
  return !find(lab)->value.empty();
}

int option_list::parse(int argc, char **argv) {
  int n = 0;
  while (n < argc) {
    char *arg = argv[n];
    if (arg[0] != '-')
      break;

    if (arg[1] == '\0')
      throw std::runtime_error("incomplete option");
    if (arg[1] == '-')
      return n + 1;
    if (arg[1] == '?' || arg[1] == 'h') {
      show_help();
      exit(EXIT_SUCCESS);
    }

    string lab = &arg[1];
    if (lab == "help") {
      show_help();
      exit(EXIT_SUCCESS);
    }

    auto it = find(lab);
    n += 1;
    if (n == argc) {
      throw std::runtime_error("option -" + lab + " has no value");
    }

    it->value = argv[n];
    n += 1;
  }
  return n;
}

void option_list::show_help(std::ostream &os) {
  os << "\n usage: " << __progname << " [-help] [opts] -- [args]\n\n"
     << " options:\n";
  size_t max_len = 10;
  for (auto &opt : opts)
    max_len = max(max_len, opt.label.size());
  for (auto &opt : opts) {
    os << "   -" << opt.label << string(2 + max_len - opt.label.size(), ' ')
       << opt.help;
    if (!opt.value.empty())
      os << " (" << opt.value << ')';
    os << '\n';
  }
  os << '\n';
}