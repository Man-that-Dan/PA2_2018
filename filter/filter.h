#ifndef FILTER_H
#define FILTER_H
/*#INCLUDES GO HERE*/
using namespace std;
using Matrix = vector<vector<int>>;
namespace Filter {
  extern Matrix K3, K5;
  Image& sharpen(Image&, Matrix&);
  Pixel apply_kernel(Image&, int x, int y, Matrix&);
  int clamp(int, int, int);
}
#endif
