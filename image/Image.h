/*
  Daniel Toro
  Project 2
  CPSC 1020
  MWF 11:15

*/

#ifndef IMAGE_H
#define IMAGE_H 1

#include "Header.h"
#include "Pixel.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <vector>

using namespace std;

class Image {
  private:
    Header HDR;
    vector<Pixel> PIX;


    // Disallow default constructor, why?
    Image ();

    // Used by Constructors to build Image

    static vector<Pixel> read_pixels(const Header&, std::ifstream&);
    static Header read_header(std::ifstream&);
    static void ignore_comments(std::ifstream&);

    // Private helper methods
    void write_header(std::ofstream&) const;

  public:
    // Constructors
    Image (std::ifstream&);
    Image (const Image& i);
    Image(const Image& i, vector<Pixel> pix);

    vector<Pixel> createjunk();
    // Public member functions
    void write_to(std::ofstream&) const;
    void make_p3();
    void make_p6();

    // Don't let someone change the header arbitrarily,
    // Image should control what fields are allowed to change
    const Header& header() const;
    // Const accessor

    const vector<Pixel> pixels() const;

    // Assignment - More complicated than you think!
    Image& operator=(const Image& rhs);

    // Cool Pixel grabber

    Pixel& operator()(int, int);
};

#endif
