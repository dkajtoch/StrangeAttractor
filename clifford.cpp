#include "attractor.hpp"

int main() {

    auto clf = Clifford({-1.4, 2.0, 1.0, 0.7}, 1500, 1000);
    clf.run({0.,0.}, 10*60);
    clf.pgm_export("clifford", "8bit");
    clf.pgm_export("clifford", "16bit");
    clf.data_export("clifford.bin");

    return 0;
}
