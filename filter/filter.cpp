#include "filter.h"

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

int Filter::clamp(int lo, int hi, int x){
  return std::max(lo, std::min(x,hi));
}

Pixel Filter::apply_kernel(Image& img, int x, int y, Matrix& k){

  //3x3 operation
  if(k == "K3"){
    int neighborX, neighborY, sumR, sumG, sumB, filtX, filtY;
    sumR = 0;
    sumG = 0;
    sumB = 0;
    cout << "running K3" << endl;
    //looping through matrix and neighboring pixels
    //row
    for(filtX = 0, neighborX = -1; filtX < 3; filtX++, neighborX++){
      //column
      for(filtY = 0, neighborY = -1; filtY < 3; filtY++, neighborY++){
        sumR+=(img((neighborX + x), (neighborY + y)).r() * k[filtX][filtY]);
        sumG+=(img((neighborX + x), (neighborY + y)).g() * k[filtX][filtY]);
        sumB+=(img((neighborX + x), (neighborY + y)).b() * k[filtX][filtY]);
      };
    };

    uint8_t R = static_cast<uint8_t>(sumR);
    uint8_t G = static_cast<uint8_t>(sumG);
    uint8_t B = static_cast<uint8_t>(sumB);

    R = Filter::clamp(0, 255, R);
    G = Filter::clamp(0, 255, G);
    B = Filter::clamp(0, 255, B);
    //create new pixel
    Pixel retValue(R, G, B);

    return retValue;
  };

  //5x5 operation
  if(k == K5){
    cout << "running K5" << endl;
    int neighborX, neighborY, sumR, sumG, sumB, filtX, filtY;
    sumR = 0;
    sumG = 0;
    sumB = 0;
    //looping through matrix and neighboring pixels
    //row
    for(filtX = 0, neighborX = -2; filtX < 5; filtX++, neighborX++){
      //column
      for(filtY = 0, neighborY = -2; filtY < 5; filtY++, neighborY++){
        sumR+=(img((neighborX + x), (neighborY + y)).r() * k[filtX][filtY]);
        sumG+=(img((neighborX + x), (neighborY + y)).g() * k[filtX][filtY]);
        sumB+=(img((neighborX + x), (neighborY + y)).b() * k[filtX][filtY]);
      };
    };

    uint8_t R = static_cast<uint8_t>(sumR);
    uint8_t G = static_cast<uint8_t>(sumG);
    uint8_t B = static_cast<uint8_t>(sumB);

    R = Filter::clamp(0, 255, R);
    G = Filter::clamp(0, 255, G);
    B = Filter::clamp(0, 255, B);
    //create new pixel
    Pixel retValue(50, 50, 50);
    return retValue;
  };
    return Pixel(0, 0, 0);
}

Image& Filter::sharpen(Image& img, Matrix& k){
  int x, y;
  int width = img.header().width();
  int height = img.header().height();
  vector<Pixel> newPix;
  newPix.resize(width*height);
  int ndx;

  //populate new pixel vector with pixels from image
  for(y = 0; x < height; y++){
    for(x = 0; x < width; x++){
      newPix[(y*width)+x] = img(x, y);
    };
  };

  //3x3 operation
  if(k == K3){
    cout << "running K3" << endl;
    //loop through all pixels except edge pixels
    for(y = 1; x < (width - 1); y++){
      for(x = 1; y < (height - 1); x++){
        ndx = (width * y) + x;
        newPix[ndx] = Filter::apply_kernel(img, x, y, K3);

      };
    };
  };

  //5x5 operation
  if(k == K5){
    cout << "running K5" << endl;
    //loop through all pixels except edge pixels
    for(y = 2; x < (width - 2); y++){
      for(x = 2; y < (height - 2); x++){
        ndx = (width * y) + x;
        newPix[ndx] = Filter::apply_kernel(img, x, y, K5);

      };
    };
  };

  Image retImg(img, newPix);
  return retImg;
}
