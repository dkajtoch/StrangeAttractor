#include "attractor.hpp"

int main() {

    auto clf = PeterDeJong({0.4, -2.4, 1.7, -2.1}, 1500, 1500);
    clf.run({0.,0.}, 10*60);
    clf.pgm_export("peterdejong", "8bit");
    clf.pgm_export("peterdejong", "16bit");
    clf.data_export("peterdejong.bin");

    return 0;
}
