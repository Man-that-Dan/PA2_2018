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
  if(k == K3){
    int neighborX, neighborY, sumR, sumG, sumB, filtX, filtY;
    sumR = 0;
    sumG = 0;
    sumB = 0;

    //looping through matrix and neighboring pixels
    //row
    for(filtY = 0, neighborY = -1; filtY < 3; filtY++, neighborY++){
      //column
      for(filtX = 0, neighborX = -1; filtX < 3; filtX++, neighborX++){
        int currR = static_cast<int>(img((neighborX + x), (neighborY + y)).r());
        int currG = static_cast<int>(img((neighborX + x), (neighborY + y)).g());
        int currB = static_cast<int>(img((neighborX + x), (neighborY + y)).b());

        sumR+=(currR * k[filtY][filtX]);
        sumG+=(currG * k[filtY][filtX]);
        sumB+=(currB * k[filtY][filtX]);
      };
    };
    int sumR1 = Filter::clamp(0, 255, sumR);
    int sumG1 = Filter::clamp(0, 255, sumG);
    int sumB1 = Filter::clamp(0, 255, sumB);
    int R = sumR1;
    int G = sumG1;
    int B = sumB1;

    //create new pixel
    Pixel retValue(R, G, B);


    return retValue;
  };

  //5x5 operation
  if(k == K5){

    int neighborX, neighborY, sumR, sumG, sumB, filtX, filtY;
    sumR = 0;
    sumG = 0;
    sumB = 0;
    //looping through matrix and neighboring pixels
    //row
    for(filtY = 0, neighborY = -2; filtY < 5; filtY++, neighborY++){
      //column
      for(filtX = 0, neighborX = -2; filtX < 5; filtX++, neighborX++){

        sumR+=(img((neighborX + x), (neighborY + y)).r() * k[filtY][filtX]);
        sumG+=(img((neighborX + x), (neighborY + y)).g() * k[filtY][filtX]);
        sumB+=(img((neighborX + x), (neighborY + y)).b() * k[filtY][filtX]);
      };
    };
    int sumR1 = Filter::clamp(0, 255, sumR);
    int sumG1 = Filter::clamp(0, 255, sumG);
    int sumB1 = Filter::clamp(0, 255, sumB);
    int R = sumR1;
    int G = sumG1;
    int B = sumB1;


    //create new pixel
    Pixel retValue(R, G, B);

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
  for(y = 0; y < height; y++){
    for(x = 0; x < width; x++){
      newPix[(y*width)+x] = img(x, y);
    };
  };

  //3x3 operation
  if(k == K3){

    //loop through all pixels except edge pixels
    for(y = 1; y < (height - 1); y++){
      for(x = 1; x < (width - 1); x++){
        ndx = (width * y) + x;
        newPix[ndx] = Filter::apply_kernel(img, x, y, K3);

      };
    };
  };

  //5x5 operation
  if(k == K5){

    //loop through all pixels except edge pixels
    for(y = 2; y < (height - 2); y++){
      for(x = 2; x < (width - 2); x++){
        ndx = (width * y) + x;
        newPix[ndx] = Filter::apply_kernel(img, x, y, K5);

      };
    };
  };

  Image retImg(img, newPix);
  //assign new image object to object given
  img = retImg;
  return img;
}
