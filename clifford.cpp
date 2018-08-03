#include "attractor.hpp"

int main() {

    auto clf = Clifford({-1.4, 1.6, 1.0, 0.7}, 20, 20);
    clf.run({0.,0.}, 1000*1000);
    clf.file_export("./clifford.dat");

    return 0;
}
