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
  if((k[0].size()) == 3){
    int neighborX, neighborY, sumR, sumG, sumB, filtX, filtY;
    sumR = 0;
    sumG = 0;
    sumB = 0;
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
    //create new pixel
    Pixel retValue(R, G, B);
    return retValue;
  };

  //5x5 operation
  if((k[0].size()) == 5){
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
    //create new pixel
    Pixel retValue(R, G, B);
    return retValue;
  };
}

Image& Filter::sharpen(Image& img, Matrix& k){
  int x, y;
  int width = img->HDR.width();
  int height = img->HDR.height();

  //3x3 operation
  if((k[0].size()) == 3){
    //loop through all pixels except edge pixels
    for(int x = 1; x < (width - 1); x++){
      for(int y = 1; y < (height - 1); y++){
        img(x,y) = Filter::apply_kernel(img, x, y, k);
      };
    };
  };

  //5x5 operation
  if((k[0].size()) == 5){
    //loop through all pixels except edge pixels
    for(int x = 2; x < (width - 2); x++){
      for(int y = 2; y < (height - 2); y++){
        img(x,y) = Filter::apply_kernel(img, x, y, k);
      };
    };
  };

}
