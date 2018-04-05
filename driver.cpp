#include <iostream>
#include <string>
#include "image/Pixel.h"
#include "image/Header.h"
#include "image/Image.h"
#include "filter/filter.h"
#include "functions/functions.h"

using namespace std;
//test

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
  Image pic(input);
  Image picCopy = pic;
  Image outK3 = Filter::sharpen(pic, Filter::K3);
  Image outK5 = Filter::sharpen(picCopy, Filter::K5);


  outK5.write_to(output2);
  outK3.write_to(output);

  //extra credit portion
  // vector<ifstream> MedInput;
  // vector<ifstream> AvgInput;
  ifstream MedInput[9];
  ifstream AvgInput[10];

  Image MedImgs[9];
  Image* MedPtr = MedImgs;
  vector<Image> AvgImgs;

  openInputFiles("median", MedInput);
  openInputFiles("average", AvgInput);

  int i;
  for(i = 0; i < 9; i++){

    MedImgs[i] = Image(MedInput[i]);
  };
  cout << "made it all the way here6" << endl;
  for(i = 0; i < 10; i++){
    AvgImgs.push_back(Image(AvgInput[i]));
  };

  cout << "made it all the way here10" << endl;
  Image MedImg = removeNoiseMedian(MedImgs);
  cout << "made it all the way here11" << endl;
  // Image AvgImg = removeNoiseAverage(AvgImgs);
  cout << "made it all the way here12" << endl;
  ofstream Medout("Noise_rem_med.ppm");
  cout << "made it all the way here13" << endl;
  ofstream Avgout("Noise_rem_avg.ppm");

  MedImg.write_to(Medout);
  cout << "made it all the way here14" << endl;
  // AvgImg.write_to(Avgout);

  //close files

  for(i = 0; i < 10; i++){
    AvgInput[i].close();
  };
  for(i = 0; i < 9; i++){
    MedInput[i].close();
  };
  Medout.close();
  Avgout.close();
  input.close();
  output2.close();
  output.close();

  return 0;
}
