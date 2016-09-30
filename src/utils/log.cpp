#include "log.hpp"

using namespace std;

class null_buffer : public streambuf {
   public:
    int overflow(int c) { return c; }
};

class null_stream : public ostream {
    null_buffer buf;

   public:
    null_stream() : ostream(&buf) {}
};

ostream &log_if(bool flag, ostream &out) {
    static null_stream nu;
    return flag ? out : nu;
}
