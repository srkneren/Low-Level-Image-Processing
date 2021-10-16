/********************************************************************
 The original copy of the code can be found at http://web.eecs.utk.edu/~mkarakay/courses_files/testfiles.zip
 and it is modified for ELM463/667

 * Image.h - header file of the Image library which defines
 *           a new class "Image" and the associated member functions
 *
 * Author: Hairong Qi, hqi@utk.edu, ECE, University of Tennessee
 *
 * Created: 02/05/02
 *
 * Note:
 *   This is a simple C++ library for image processing.
 *   The purpose is not high performance, but to show how
 *   the algorithm works through programming.
 *   This library can only read in PGM/PPM format images.
 *
 ********************************************************************/

#ifndef IMAGE_H
#define IMAGE_H

#include <iostream>
#include <cstdlib>
#include <fstream>

using namespace std;

class Image {
  friend ostream & operator<<(ostream &, Image &);
  friend Image operator/(Image &, double);    // image divided by a scalar
  friend Image operator*(Image &, double);    // image multiplied by a scalar
  friend Image operator+(Image &, double);    // image add a scalar
  friend Image operator-(Image &, double);    // image subtract a scalar

 public:
  // constructors and destructor
  Image();                             // default constructor
  Image(int, int);                     // constructor with row & column
  Image(const Image &);                // copy constructor
  ~Image();                            // destructor


  // create an image
  void createImage();               	// create an image, parameters all set
  void createImage(int,        		    // create an image with row
		   int c=1            			// column (default 1, a column vector)
           );
  void initImage(float init=0.0);      	// initiate the pixel value of an img
										// the default is 0.0
  // get and set functions
  int getRow() const;                  	// get row # / the height of the img
  int getCol() const;                  	// get col # / the width of the image
  float getMaximum() const;            	// get the maximum pixel value
  float getMinimum() const;            	// get the mininum pixel value
  float getPix(int rows, int cols);		// get pixel value at (rows, cols)
  Image getImage() const;              	// get the image

  void setRow(int);                    // set row number
  void setCol(int);                    // set column number
  void setPix(int rows, int cols, float value);	// set Pixel value at (rows, cols)
  void setImage(Image &);              // set the image,

  // operator overloading functions
  float & operator()(int, int c = 0) const; // operator overloading (i,j), when c = 0, a column vector
  const Image operator=(const Image &);    // = operator overloading
  Image operator+(const Image &) const;    // overloading + operator
  Image operator-(const Image &) const;    // overloading - operator
  Image operator*(const Image &) const;    // overloading pixelwise *
  Image operator/(const Image &) const;    // overloading pixelwise division

  bool IsEmpty() const { return (image==NULL); }

  void readImage(char *fname);
  void writeImage(char *fname, bool flag = false);

  // YOUR MEMBER FUNCTIONS //

Image thresholdImage(float threshold = 127.0, float lowValue = 0.0, float highValue = 255.0);
Image ThresholdFunc(int th = 135);
Image resizeImage(int row,int col);
Image HistogramEqualization();
float PutFilterOnPoint_3x3(int PixelIndexX,int PixelIndexY,float FilterMatrix[3][3]);
float PutFilterOnPoint_5x5(int PixelIndexX,int PixelIndexY,float FilterMatrix[5][5]);
Image LaplacianFilter();
Image GaussFilt_5x5();
Image HighBoostFilter(int k=1);

  // END OF YOUR MEMBER FUNCTIONS//

 private:
  int nrows;		// number of rows / height
  int ncols;		// number of columns / width
  int maximum;		// the maximum pixel value
  float *image;		// image buffer
};



////////////////////////////////////
// image I/O
  Image readImage(char *);             // read image
  void writeImage(Image &,             // write an image
                char *,
                int flag = 0);         // flag for rescale, rescale when == 1
void CreateGaussFilter_5x5(double GKernel[][5]);

#endif
