#include "Image.h"
#include <vector>

using namespace std;

// Param constructor

Image::Image(ifstream& in) : HDR(Image::read_header(in)), PIX(Image::read_pixels(this->HDR, in)) { }
Image::Image(const Image& i, vector<Pixel> pix) : HDR(i.HDR), PIX(pix) { }
Image::vector<Pixel> createjunk(){
  vector<Pixel> junk;
  junk.resize(1);
  junk[0] = Pixel();
  return junk;
};
Image::Image() : HDR(Header()), PIX(Image::createjunk()) { }
// Copy constructor

Image::Image(const Image& img) : HDR(img.HDR),  PIX(img.PIX) { }


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


vector<Pixel> Image::read_pixels (const Header& hdr, ifstream& in) {
  int num_pixels = hdr.width() * hdr.height();

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
  if (this == &rhs) return *this;
  // Header is simple
  this->HDR = rhs.HDR;  // Assignment operator


  vector<Pixel> Duplicate(rhs.PIX);
  this->PIX = Duplicate;

  return *this;
}

// Get one pixel
Pixel& Image::operator() (int x, int y) {
  int ndx = (this->HDR.width() * y) + x;
  return this->PIX[ndx];
}
