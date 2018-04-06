/*
  Daniel Toro
  Project 2
  CPSC 1020
  MWF 11:15

*/

#include <iostream>
#include <string>
#include "image/Pixel.h"
#include "image/Header.h"
#include "image/Image.h"
#include "filter/filter.h"
#include "functions/functions.h"

using namespace std;


int main(int argc, char const *argv[]) {
  if (argc != 3) {
    std::cerr << "USAGE: ./out <in.ppm> <out.ppm>";
    return 1;
  };


  string in;
  in = argv[2];
  string out1 = "k3_" + in;
  string out2 = "k5_" + in;
  // Open files
  std::ifstream input(argv[1]);
  std::ofstream output(out1);
  std::ofstream output2(out2);


  if (!(input && output2 && output)) {
    std::cerr << "Could not open input/output\n";
    return 1;
  }

  // ifstream constructor, let's read the file twice!
  //create two images form input file
  Image pic(input);
  Image picCopy = pic;
  //sharpen image with both matrices
  Image outK3 = Filter::sharpen(pic, Filter::K3);
  Image outK5 = Filter::sharpen(picCopy, Filter::K5);

  //Write images to output files
  outK5.write_to(output2);
  outK3.write_to(output);



  //close files
  input.close();
  output2.close();
  output.close();

  return 0;
}
