#include "attractor.hpp"

int main() {

   // class instance with default domain boundary
   auto clf = Clifford({-1.4, 2.0, 1.0, 0.7}, 1500, 1000);

   // class instance with user defined domain boundary
   auto clfu = Clifford({-1.4, 2.0, 1.0, 0.7}, 1500, 1000,
      {{"xmin", -1.0}, {"xmax", 1.0},
       {"ymin", -1.0}, {"ymax", 1.0}}
   );

   // run recurence for 10 seconds and initial point (x,y) = (0,0)
   clf.run({0.,0.}, 10);
   // save image in PGM format using 8bit coding
   clf.pgm_export("clifford", "8bit");
   // save image in PGM format using 16bit coding
   clf.pgm_export("clifford", "16bit");
   // save image using float 32bits numbers
   clf.data_export("clifford.bin");

   return 0;
}
