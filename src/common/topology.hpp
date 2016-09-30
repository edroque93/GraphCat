#pragma once

#include <ostream>
#include <string>
#include <vector>

#include <gsl/gsl_matrix.h>

class topology {
  gsl_matrix *matrix = nullptr;
  topology(){};

public:
  ~topology();

  topology(const topology &);
  topology &operator=(const topology &);

  topology(topology &&);
  topology &operator=(topology &&);

  inline size_t size() const { return matrix->size1; }

  static topology read_csv(const std::string &filename);
  static topology read_dat(const std::string &filename);

  void save_csv(const std::string &filename, char delim = ' ');
  void save_dat(const std::string &filename);

  friend std::ostream &operator<<(std::ostream &os, const topology &top);
};
