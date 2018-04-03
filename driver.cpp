#include <iostream>
#include <string>
#include "image/Pixel.h"
#include "image/Header.h"
#include "image/Image.h"
#include "filter/filter.h"

using namespace std;

Matrix Filter::K3 =
{{ 0,-1, 0},
 {-1, 5,-1},
 { 0,-1, 0}};

Matrix Filter::K5 =
{{ 0,  0, -1,  0,  0},
 { 0,  0, -1,  0,  0},
 {-1, -1,  9, -1, -1},
 { 0,  0, -1,  0,  0},
 { 0,  0, -1,  0,  0}};

int main(int argc, char const *argv[]) {
  if (argc != 3) {
    std::cerr << "USAGE: ./out <in.ppm> <out.ppm>";
    return 1;
  };
  string in = argv[2]
  string out1 = "k3_" + in;
  string out2 = "k5_" + in;
  // Open files
  std::ifstream in(argv[1]);
  std::ofstream output(out1);
  std::ofstream output2(out2);


  if (!(in && out2 && out)) {
    std::cerr << "Could not open input/output\n";
    return 1;
  }

  // ifstream constructor, let's read the file twice!
  Image in1(in);
  Image outK5 = Filter::sharpen(in1, K5);
  Image outK3 = Filter::sharpen(in1, K3);

  outK5.write_to(output2);
  outK3.write_to(output);


  in.close();
  output2.close();
  output.close();

  return 0;
}
