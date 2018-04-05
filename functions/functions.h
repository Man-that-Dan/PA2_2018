#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <string.h>
#include <vector>
#include "../image/Header.h"
#include "../image/Image.h"
#include "../image/Pixel.h"
#include <ctype.h>


using namespace std;


void openInputFiles(string name, vector<ifstream> inPut);
Image removeNoiseAverage(vector<Image> img);
Image removeNoiseMedian(vector<Image> img);


#endif
