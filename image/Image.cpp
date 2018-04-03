#include "Image.h"
#include <vector>

using namespace std;
// Param constructor
Image::Image (ifstream& in) {
   this->HDR = Image::read_header(in);
   this->PIX = Image::read_pixels(this->HDR, in);
}

// Copy constructor
Image::Image (const Image& img) {
  this->HDR = img.HDR;  // Assignment operator is really useful!
  // Delete: We have to allocate new memory here
  // DeletE: int num_pixels = img.HDR.width() * img.HDR.height();
  // // Delete: this->PIX = new Pixel[num_pixels];
  // Delete: this->PIX = vector<Pixel>
  // Delete: this->PIX.resize(num_pixels);

  // Delete: might need to change this to work with vectors
  // Delete: copy(img.PIX, img.PIX + num_pixels, this->PIX);
  vector<Pixel> Duplicate(img.PIX);
  this->PIX = Duplicate;
}

// Destructor
/* Delete:
Image::~Image () {
  delete[] PIX;  // Don't allow memory leaks!
}
*/
Header Image::read_header (ifstream& in) {
  string magic;
  int w, h, mc;

  in >> magic;
  Image::ignore_comments(in);
  in >> w;
  Image::ignore_comments(in);
  in >> h;
  Image::ignore_comments(in);
  in >> mc;
  in.ignore(256, '\n');
  return Header(magic, w, h, mc);
}

void Image::ignore_comments (ifstream& in) {
  char c;
  in.get(c);

  while ( isspace(c) || c == '#') {
    if (c == '#')
      in.ignore(256, '\n');
    in.get(c);
  }

  in.unget();
}

// Delete: This function allocates memory! Not anymore..well technically it still does
vector<Pixel> Image::read_pixels (const Header& hdr, ifstream& in) {
  int num_pixels = hdr.width() * hdr.height();
  // delete: Pixel* pixels = new Pixel[num_pixels];
  vector<Pixel> pixels;
  pixels.resize(num_pixels);


  if (hdr.magic() == "P3") {
    uint r,g,b;
    for (int i = 0; i < num_pixels; i++) {
      in >> r >> g >> b;
      pixels[i] = Pixel(r, g, b); // Assignment operator to the rescue again!
    }
  } else {
    uint8_t r,g,b;
    for (int i = 0; i < num_pixels; i++) {
      r = in.get();
      g = in.get();
      b = in.get();
      pixels[i] = Pixel(r, g, b);
    }
  }

  return pixels;
}

// accessors
const Header& Image::header () const { return this->HDR; }
const vector<Pixel> Image::pixels () const { return this->PIX; }

// If someone wants to change the header, the Image controls
// which fields it will to expose
void Image::make_p3 () { this->HDR.magic() = "P3"; }
void Image::make_p6 () { this->HDR.magic() = "P6"; }

void Image::write_header (ofstream& out) const {
  out << this->HDR.magic() << " "
      << this->HDR.width() << " "
      << this->HDR.height() << " "
      << this->HDR.max_color() << "\n";
}

void Image::write_to (ofstream& out) const {
  write_header(out);

  int num_pixels = this->HDR.width() * this->HDR.height();

  if (this->HDR.magic() == "P3") {
    for (int i = 0; i < num_pixels; i++) {
      Pixel p = this->PIX[i];
      out << (int) p.r() << ' '
          << (int) p.g() << ' '
          << (int) p.b() << ' ';
    }
  } else {
    for (int i = 0; i < num_pixels; i++) {
      Pixel p = this->PIX[i];
      out << p.r() << p.g() << p.b();
    }
  }
}

// This function is important!
Image& Image::operator=(const Image& rhs) {
  if (this == &rhs) return *this; // Why do we need this? Hint: delete[]
  // Header is simple
  this->HDR = rhs.HDR;  // Assignment operator

  // Pixels are not, we need to make sure there is enough room
  // delete: int num_pixels = rhs.HDR.width() * rhs.HDR.height();
  // delete: delete[] this->PIX;
  // delete: this->PIX = new Pixel[num_pixels];

  // And do a complete copy
  // delete: copy(rhs.PIX, rhs.PIX+num_pixels, this->PIX);
  vector<Pixel> Duplicate(rhs.PIX);
  this->PIX = Duplicate;

  return *this;
}

// Get one pixel
Pixel& Image::operator() (int x, int y) {
  int ndx = (this->HDR.width() * y) + x;
  return this->PIX[ndx];
}
