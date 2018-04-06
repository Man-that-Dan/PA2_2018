/*
  Daniel Toro
  Project 2
  CPSC 1020
  MWF 11:15

*/

#ifndef FILTER_H
#define FILTER_H
#include "../image/Header.h"
#include "../image/Image.h"
#include "../image/Pixel.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <vector>


using namespace std;
using Matrix = vector<vector<int>>;
namespace Filter {
  extern Matrix K3, K5;
  Image& sharpen(Image& img, Matrix& k);
  Pixel apply_kernel(Image& img, int x, int y, Matrix& k);
  int clamp(int lo, int hi, int x);
}
#endif
