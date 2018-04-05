#include "functions.h"

using namespace std;


//opens input files and stores pointers in FILE pointer array given
void openInputFiles(string name, ifstream inPut[]){
  cout << "made it all the way here3" << endl;
  // open files named average###.ppm
  if(name == "average"){
    int i;


    string fileName;
    for(i = 0; i < 10; i++){
      int ext = i+1;
      if(ext < 10){
        fileName = string("average_") + string("00") + to_string(ext) + string(".ppm");
      };
      if(ext >= 10){
        fileName = string("average_") + string("0") + to_string(ext) + string(".ppm");
      };
      cout << fileName << endl;
      cout << "made it all the way here4" << endl;
      inPut[i].open(fileName);
      cout << "made it all the way here5" << endl;
      if(!inPut[i]){
        cout << "Error: Could not open " << fileName << endl;
        exit(0);
      };
    }
  };
  // open files named median###.ppm
  if(name == "median"){
    int i;


    string fileName;
    for(i = 0; i < 9; i++){
      int ext = i+1;
      if(ext < 10){
        fileName = string("median_") + string("00") + to_string(ext) + string(".ppm");
      };
      if(ext >= 10){
        fileName = string("median_") + string("0") + to_string(ext) + string(".ppm");
      };

      inPut[i].open(fileName);
      if(!inPut[i]){
        cout << "Error: Could not open " << fileName << endl;
        exit(0);
      };
    }
  };

}

//removes noise using average value of pixels
Image removeNoiseAverage(vector<Image> img){
  cout << "made it all the way here8" << endl;
  cout << "made it all the way here2" << endl;
  vector<Pixel> averagedPix;
  int val, avg;
  int sum = 0;
  int i;
  int r = 0;
  int totalPixels = (img[0].header().height())*(img[0].header().width());
  averagedPix.resize(totalPixels);
  while(r < totalPixels){
  // Average Red values
    for(i = 0; i < 10; i++){
      val = img[i].pixels()[r].r();
      sum += val;
    };
    avg = sum/10;
    averagedPix[r].set_r(avg);
    sum = 0;
  // Average Green values
    for(i = 0; i < 10; i++){
      val = img[i].pixels()[r].g();
      sum += val;
    };
    avg = sum/10;
    averagedPix[r].set_g(avg);
    sum = 0;
  // Average Blue values
    for(i = 0; i < 10; i++){
      val = img[i].pixels()[r].b();
      sum += val;
    };
    avg = sum/10;
    averagedPix[r].set_b(avg);
    sum = 0;
    //move on to next pixel
    r++;
  };
  Image newImg(img[0], averagedPix);
  cout << "made it all the way here9" << endl;
  return newImg;
};

//opens values using median pixel values
Image removeNoiseMedian(vector<Image> img){
  cout << "made it all the way here1" << endl;
  vector<unsigned int> nums;
  nums.resize(9);
  cout << "made it all the way here16" << endl;
  vector<Pixel> medianPix;
  int i, val, median;
  int r = 0;
  int totalPixels = (img[0].header().height())*(img[0].header().width());
  medianPix.resize(totalPixels);
  cout << "made it all the way here17" << endl;

  while(r < totalPixels){
  // Average Red values
    for(i = 0; i < 9; i++){
      val = img[i].pixels()[r].r();
      nums[i] = val;
    };
    std::sort(nums.begin(), nums.end());
    median = nums[4];
    medianPix[r].set_r(median);
  if(r = (totalPixels/2)){
    cout << "made it all the way here18 Progress:" << r << " out of: " << totalPixels << endl;
  };
  // Average Green values
    for(i = 0; i < 9; i++){
      val = img[i].pixels()[r].g();
      nums[i] = val;
    };
    std::sort(nums.begin(), nums.end());
    median = nums[4];
    medianPix[r].set_g(median);

  // Average Blue values
    for(i = 0; i < 9; i++){
      val = img[i].pixels()[r].b();
      nums[i] = val;
    };
    std::sort(nums.begin(), nums.end());
    median = nums[4];
    medianPix[r].set_b(median);

    //move on to next pixel
    r++;
  };
  Image newImg(img[0], medianPix);
  cout << "made it all the way here7" << endl;
  return newImg;
};
