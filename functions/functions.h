#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <stdlib.h>
#include <stdio.h>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <istream>
#include <ostream>
#include <iomanip>
#include <string>
#include <vector>
#include "../image/Header.h"
#include "../image/Image.h"
#include "../image/Pixel.h"
#include <ctype.h>


using namespace std;


void openInputFiles(string name, ifstream inPut[]);
// Image removeNoiseAverage(vector<Image> img);
Image* removeNoiseAverage(Image* img[]);
Image removeNoiseMedian(vector<Image> img);


#endif
