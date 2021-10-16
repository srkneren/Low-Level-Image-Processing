/**********************************************************
 The original copy of the code can be found at http://web.eecs.utk.edu/~mkarakay/courses_files/testfiles.zip 
 and it is modified for ELM463/667
 
 * Image.cpp - the image library which implements
 *             the member functions defined in Image.h
 *
 * Author: Hairong Qi, ECE, University of Tennessee
 *
 * Created: 02/05/02
 *
 * Copyright (C) hqi@utk.edu
 **********************************************************/

#include "Image.h"
#include <iostream>
#include <iomanip>
#include <math.h>

using namespace std;

/**
 * Default constructor.
 */ 
Image::Image() {
  image = NULL;
  nrows = 0;
  ncols = 0;
  maximum = 255;
  //createImage(0, 0);
}

/**
 * Constructor for grayscale images.
 * @param nrows Numbers of rows (height).
 * @param ncols Number of columns (width).
 * @return The created image.
 */
Image::Image(int nRows, int nCols) {
  if (nRows<=0 || nCols<=0) {
    cout << "Image: Index out of range.\n";
    exit(3);
  }
  image = NULL;
  createImage(nRows, nCols);
}

/**
 * Copy constructor. 
 * @param img Copy image.
 * @return The created image.
 */
Image::Image(const Image &img) {
  int rows, cols;

  image = NULL;
  nrows = img.getRow();
  ncols = img.getCol();
  createImage(nrows, ncols);             // allocate memory
  
  for (rows=0; rows < nrows; rows++)
    for (cols=0; cols < ncols; cols++)
		image[rows * ncols + cols] = img(rows, cols);
}

/**
 * Destructor.  Frees memory.
 */
Image::~Image() {
  if (image)
    delete [] image;       // free the image buffer
}






/**
 * Allocate memory for the image and initialize the content to be 0.
 */
void Image::createImage() {

  if (image != NULL)
    delete [] image;

  maximum = 255;

  image = (float *) new float [nrows * ncols];
  if (!image) {
    cout << "CREATEIMAGE: Out of memory.\n";
    exit(1);
  }

  initImage();
}


/**
 * Allocate memory for the image and initialize the content to be zero.
 * @param r Numbers of rows (height).
 * @param c Number of columns (width).
 */
void Image::createImage(int numberOfRows, int numberOfColumns) {
  
  if (image != NULL)
    delete [] image;

  nrows = numberOfRows;
  ncols = numberOfColumns;
  maximum = 255;

  image = (float *) new float [nrows * ncols];
  if (!image) {
    cout << "CREATEIMAGE: Out of memory.\n";
    exit(1);
  }

  initImage();
}

/**
 * Initialize the image.
 * @para init The value the image is initialized to. Default is 0.0.
 */
void Image::initImage(float initialValue) {
  int i;

  for (i = 0; i < nrows * ncols; i++)
    image[i] = initialValue;
}

/**
 * Returns the total number of rows in the image.
 * @return Total number of rows.
 * \ingroup getset
 */
int Image::getRow() const {
  return nrows;
}

/**
 * Returns the total number of columns in the image.
 * @return Total number of columns.
 * \ingroup getset
 */
int Image::getCol() const {
  return ncols;
}

/**
 * Returns the maximum pixel value of a gray-level image. 
 * @return The intensity of that pixel.
 * \ingroup getset
 */
float Image::getMaximum() const {
  int i, j;
  float maxi=-10000;

 
  for (i=0; i<nrows; i++)
    for (j=0; j<ncols; j++)
      if (maxi < image[i*ncols+j])
	maxi = image[i*ncols+j];
  
  return maxi;
}


/**
 * Returns the minimum pixel value of the image.
 * @return The minimum pixel value.
 * \ingroup getset
 */
float Image::getMinimum() const {
  int i, j;
  float mini=10000; 

  for (i=0; i<nrows; i++)
    for (j=0; j<ncols; j++)
      if (mini > image[i*ncols+j])
	mini = image[i*ncols+j];

  return mini;
}



/**
 * Returns the pixel value at rows, cols
 * @return The pixel value
 * \ingroup getset
 */
float Image::getPix(int rows, int cols) {
  return image[rows * ncols + cols];
}


/**
 * Returns the image. 
 * @return a gray-scale image
 * \ingroup getset
 */
Image Image::getImage() const {
  Image temp;
  int rows, cols;
  
  temp.createImage(nrows, ncols);   // temp is a gray-scale image
  for (rows = 0; rows < nrows; rows++)
    for (cols = 0; cols < ncols; cols++)
      temp(rows, cols) = image[rows * ncols + cols];
      
  return temp;
}

/**
 * Sets the total number of rows in an image.
 * @param r Total number of rows.
 * \ingroup getset
 */
void Image::setRow(int numberOfRows) {
  nrows = numberOfRows;
}

/**
 * Sets the total number of columns in an image.
 * @param c Total number of columns.
 * \ingroup getset
 */
void Image::setCol(int numberOfColumns) {
  ncols = numberOfColumns;
}


/**
 * Sets the pixel value at rows,cols.
 * @param row and col index.
 * \ingroup getset
 */
void Image::setPix(int rows, int cols, float value) {
  image[rows * ncols + cols] = value;
}


/**
 * Sets the image given a grayscale image. 
 * \ingroup getset
 */
void Image::setImage(Image &img) {
  int rows, cols;

  for (rows = 0; rows < nrows; rows++)
    for (cols = 0; cols < ncols; cols++)
      image[rows * ncols + cols] = img(rows, cols);
}

/**
 * Overloading () operator
 * \ingroup overload
 * @param i Row
 * @param j Column
 */
float & Image::operator()(int rows, int cols) const {
  return image[rows * ncols + cols];
}

/**
 * Overloading = operator.
 * \ingroup overload
 * @param img Image to copy.
 * @return Newly copied image.
 */
const Image Image::operator=(const Image& img) {
  int rows, cols;

  if (this == &img)
    return *this;

  nrows = img.getRow();
  ncols = img.getCol();
  createImage(nrows, ncols);             

  for (rows = 0; rows < nrows; rows++)
    for (cols = 0; cols < ncols; cols++)
	(*this)(rows, cols) = img(rows, cols);

  return *this;
}

/**
 * Overloading + operator.
 * \ingroup overload
 * @param img Image to add to specified image.
 * @return Addition of the two images.
 */
Image Image::operator+(const Image& img) const {
  int i, j, nr, nc;
  Image temp;

  nr = img.getRow();
  nc = img.getCol();

  if (nr != nrows || nc != ncols) {
    cout << "operator+: "
         << "Images are not of the same size or type, can't do addition\n";
    exit(3);
  }
  temp.createImage(nrows, ncols);
  
  for (i=0; i<nrows; i++)
    for (j=0; j<ncols; j++)
        temp(i,j) = image[i*ncols+j] + img(i,j);

  return temp;
}

/**
 * Overloading - operator.
 * \ingroup overload
 * @param img Image to subtract from specified image.
 * @return Subtraction of the two images.
 */
Image Image::operator-(const Image &img) const {
   int i, j, nr, nc;
  Image temp;

  nr = img.getRow();
  nc = img.getCol();

  if (nr != nrows || nc != ncols) {
    cout << "operator-: "
         << "Images are not of the same size or type, can't do subtraction\n";
    exit(3);
  }
  temp.createImage(nrows, ncols);             
  
  for (i=0; i<nrows; i++)
    for (j=0; j<ncols; j++)
        temp(i,j) = image[i*ncols+j] - img(i,j);

  return temp;
}

/**
 * Overloading * operator.  This function does pixel by pixel multiplication.
 * \ingroup overload
 * @param img Image to multiply with specified image.
 * @return Multiplication of the two images.
 */
Image Image::operator*(const Image &img) const {
  int i, j, nr, nc;
  Image temp;

  nr = img.getRow();
  nc = img.getCol();

  if (nr != nrows || nc != ncols) {
    cout << "operator*: "
         << "Images are not of the same size or type, can't do multiplication\n";
    exit(3);
  }
  temp.createImage(nrows, ncols);             
  
  for (i=0; i<nrows; i++)
    for (j=0; j<ncols; j++)
        temp(i,j) = image[i*ncols+j] * img(i,j);

  return temp;
}

/**
 * Overloading / operator.  This function does pixel by pixel division.
 * Specified image is the dividend.
 * \ingroup overload
 * @param img Image to be divided (divisor).
 * @return Quotient of the two images.
 */
Image Image::operator/(const Image &img) const {
  int i, j, nr, nc;
  Image temp;

  nr = img.getRow();
  nc = img.getCol();

  if (nr != nrows || nc != ncols) {
    cout << "operator/: "
         << "Images are not of the same size or type, can't do division\n";
    exit(3);
  }
  temp.createImage(nrows, ncols);             
  
  for (i=0; i<nrows; i++)
    for (j=0; j<ncols; j++)
        temp(i,j) = image[i*ncols+j] / ( img(i,j) + 0.001 );

  return temp;
}


/**
 * Overloading << operator.  Output the image to the specified destination.
 * \ingroup overload
 * @param out The specified output stream (or output destination).
 * @param img Image to be output.
 * @result Output image to the specified file destination.
 */
ostream & operator<<(ostream &out, Image &img) {
  int rows, cols;
  

    for (rows = 0; rows < img.getRow(); rows++) {
      for (cols = 0; cols < img.getCol(); cols++)
        out << setw(4) << img(rows, cols) << ' ';
      out << endl;
    }

  return out; 
}

/**
 * Overloading / operator.  The left operand is the image and the right
 * is the dividend (a double point number). Each pixel in the image is 
 * divided by the double point number.
 * \ingroup overload
 * @param img Image as the left operand.
 * @param val A double point number as the right operand.
 * @result Image divided by a double point number.
 */
Image operator/(Image &img, double val) {
  int i, j, nr, nc;
  Image temp;
  
  nr = img.getRow();
  nc = img.getCol();
  temp.createImage(nr, nc);
  
  for (i=0; i<nr; i++)
    for (j=0; j<nc; j++)
        temp(i,j) = img(i,j) / val;
  
  return temp;
}

/**
 * Overloading * operator.  The left operand is the image and the right
 * is a double point number. Each pixel in the image is multiplied by the
 * double point number.
 * \ingroup overload
 * @param img Image as the left operand.
 * @param s A double point number as the right operand.
 * @result Image multiplied by a double point scalar.
 */
Image operator*(Image &img, double s) {
  int i, j, nr, nc;
  Image temp;
  
  nr = img.getRow();
  nc = img.getCol();
  temp.createImage(nr, nc);
  
  for (i=0; i<nr; i++)
    for (j=0; j<nc; j++)
        temp(i,j) = img(i,j) * s;
  
  return temp;
}


/**
 * Overloading + operator.  The left operand is the image and the right
 * is a double point number. Each pixel in the image is added by the
 * double point number.
 * \ingroup overload
 * @param img Image as the left operand.
 * @param s A double point number as the right operand.
 * @result Image add a double point scalar.
 */
Image operator+(Image &img, double s) {
  int i, j, nr, nc;
  Image temp;
  
  nr = img.getRow();
  nc = img.getCol();
  temp.createImage(nr, nc);
  
  for (i=0; i<nr; i++)
    for (j=0; j<nc; j++)
        temp(i,j) = img(i,j) + s;
  
  return temp;
}  
  
/**
 * Overloading - operator.  The left operand is the image and the right
 * is a double point number. Each pixel in the image is subtracted by the
 * double point number.
 * \ingroup overload
 * @param img Image as the left operand.
 * @param s A double point number as the right operand.
 * @result Image subtract a double point scalar.
 */
Image operator-(Image &img, double s) {
  int i, j, nr, nc;
  Image temp;
  
  nr = img.getRow();
  nc = img.getCol();
  temp.createImage(nr, nc);
  
  for (i=0; i<nr; i++)
    for (j=0; j<nc; j++)
        temp(i,j) = img(i,j) - s;
  
  return temp;
} 

/**
 * Read image from a file                     
 * @param fname The name of the file 
 * @return An Image object
 */
  void Image::readImage(char *fname) {
  ifstream ifp;
  char dummy[80];
  unsigned char *img;
  int rows, cols;
  int nRows, nCols, nt, maxi;

  ifp.open(fname, ios::in | ios::binary);

  if (!ifp) {
    cout << "readImage: Can't read image: " << fname << endl;
    exit(1);
  }

  // identify image format
  ifp.getline(dummy, 80, '\n');

  if (dummy[0] == 'P' && dummy[1] == '5') 
     ;
  else {
    cout << "readImage: Can't identify image format." << endl;
    exit(1);
  }

  // skip the comments
  ifp.getline(dummy, 80, '\n');

  while (dummy[0] == '#') {
    ifp.getline(dummy, 80, '\n');
  }

  // read the row number and column number
  sscanf(dummy, "%d %d", &nCols, &nRows);

  // read the maximum pixel value
  ifp.getline(dummy, 80, '\n');
  sscanf(dummy, "%d", &maxi); 
  if (maxi > 255) {
    cout << "Don't know what to do: maximum value is over 255.\n";
    exit(1);
  }

  if (image != NULL)
  delete [] image;
  
  nrows = nRows;
  ncols = nCols;
  maximum = 255;
  
  // read the image data
  img = (unsigned char *) new unsigned char [nRows * nCols];
  if (!img) {
    cout << "READIMAGE: Out of memory.\n";
    exit(1);
  }
  image = (float *) new float [nRows * nCols];
  if (!image) {
    cout << "READIMAGE: Out of memory.\n";
    exit(1);
  }

    ifp.read((char *)img, (nRows * nCols * sizeof(unsigned char)));
    
    for (rows = 0; rows < nRows; rows++)
      for (cols = 0; cols < nCols; cols++)
          image[rows * nCols + cols] = (float) img[rows * nCols + cols];
      
  ifp.close();
  
  delete [] img;
}


/**
 * Write image buffer to a file.
 * @param fname The output file name.
 */
void Image::writeImage(char *fname, bool flag) {
  ofstream ofp;
  int i, j;
  int nRows, nCols, nt;
  unsigned char *img;

  ofp.open(fname, ios::out | ios::binary);

  if (!ofp) {
    cout << "writeImage: Can't write image: " << fname << endl;
    exit(1);
  }


  ofp << "P5" << endl;
  ofp << ncols << " " << nrows << endl;

 
  ofp << 255 << endl;
  
  

  // convert the image data type back to unsigned char
  img = (unsigned char *) new unsigned char [nrows * ncols];
  if (!img) {
    cout << "WRITEIMAGE: Out of memory.\n";
    exit(1);
  }

  float maxi = getMaximum();
  float mini = getMinimum();
  
  
    for (i = 0; i< nrows; i++)
      for (j = 0; j < ncols; j++) {
	  // rescale if the flag is set
	  if ((maxi != mini) && flag == true)
	    img[i * ncols + j] = (unsigned char)  ((image[i * ncols + j]-mini)/(float)(maxi-mini)*255.0); 
	  // any intensity that is larger than the maximum would be set as maximum
	  else if (image[i * ncols + j] > 255)
	    img[i * ncols + j] = 255;
	  else if (image[i * ncols + j] < 0)
	    img[i * ncols + j] = 0;
	  else
	    img[i * ncols + j] = (unsigned char)  image[i * ncols + j]; 
      }
      
    ofp.write((char *)img, (nrows * ncols * sizeof(unsigned char)));


  ofp.close();
  delete [] img;
}




// YOUR FUNCTIONS

/**
 * Returns the image. 
 * @return a gray-scale image
 * \ingroup getset
 */
Image Image::thresholdImage(float thresholdValue, float lowValue, float highValue) {
  Image temp;
  int rows, cols;
  
  temp.createImage(nrows, ncols);   // temp is a gray-scale image
  for (rows = 0; rows < nrows; rows++)
    for (cols = 0; cols < ncols; cols++)
      if (image[rows * ncols + cols] <= thresholdValue) 
	temp(rows, cols) = lowValue;
      else
	temp(rows, cols) = highValue;
      
      
  return temp;
}


Image Image::ThresholdFunc(int th) {
  Image temp;
  temp.createImage(nrows,ncols);
  int rows,cols ;

  for (rows = 0; rows < nrows; rows++)
    for (cols = 0; cols < ncols; cols++)
      if(this->image[rows * ncols + cols]<=th)
          temp(rows,cols) = 0 ;
      else
          temp(rows,cols) = 255 ;
      
  return temp;
}

Image Image :: resizeImage(int row,int col){
  Image temp(row,col);
  //cross 1.00 to make float if dont it can be always 0  
  float row_ratio = (this->getRow()*1.00) / row ;
  float col_ratio = (this->getCol()*1.00) / col ;

  float original_row , original_col ;
  int i,j ;

  // These for genarating pixels from 1 pixel
  float partitions2Row,partitions2Col ;

  //look at all pixels and   
  for(i=0;i<row;i++){
    for(j=0;j<col;j++){
      partitions2Row = (int)floor(i*row_ratio);
      partitions2Col = (int)floor(j*col_ratio);
      temp(i,j) = this->getPix(partitions2Row,partitions2Col);
    }
  }
  return temp ;
}

Image Image :: HistogramEqualization(){
  
  float histogramGray[256] = {0};
  int i,j ;
  Image temp ;
  
  for(i=0;i<this->getRow();i++){
    for(j=0;j<this->getCol();j++){
      histogramGray[ (int)this->getPix(i,j)  ]++  ;
    }}
    
  int kumulatifHistogram[256] = {0};
  float sum = 0;
  for(i=0;i<256;i++){
    kumulatifHistogram[i] = sum + histogramGray[i];
    sum = kumulatifHistogram[i];
  }
  //Normalized values
  float NorKumulatifHistogram[256] = {0.0};
  for(i=0;i<256;i++){
    //can be changed brightness of image
    int maxPixelVal = 255 ;
    NorKumulatifHistogram[i] = (kumulatifHistogram[i]/sum)*maxPixelVal ; 
  }

  //copy 
  temp = *this ;

  //assign new values of pixels correspond to original pixels
  for(i=0;i<this->getRow();i++){
    for(j=0;j<this->getCol();j++){
      temp(i,j) =  NorKumulatifHistogram[(int)this->getPix(i,j)]; 
    }}
  return temp;
}
//This function apply the kernel matrix to one pixel which is on image.
//Implementation to 3x3 kernel
float Image :: PutFilterOnPoint_3x3(int PixelIndexX,int PixelIndexY,float KernelMatrix[3][3]){
  float neighborPixels[3][3] = {{0}} ;
  int i,j;
  for(i=-1;i<2;i++){
    for(j=-1;j<2;j++){    
      //when getting borders, algorithm add 0s for out of image
      if( ((PixelIndexX+i)>=0 && (PixelIndexY+j)>=0)     &&   ((PixelIndexX+i < this->getRow()) && (PixelIndexY+j < this->getCol())))
        neighborPixels[i+1][j+1] = this->getPix(PixelIndexX+i,PixelIndexY+j);
      else
        neighborPixels[i+1][j+1] = 0 ;
    }}

  //apply filter for the point-- cross filter and pixel values and sum up all of them 
  float sum = 0 ;
  for(i=0;i<3;i++){
    for(j=0;j<3;j++){
      sum += (neighborPixels[i][j] * KernelMatrix[i][j]);
    }}

  cout<<sum ; 

  // to test
  for(i=0;i<3;i++)
    for(j=0;j<3;j++)
      cout<<neighborPixels[i][j]<<"\n" ;


  return sum ;

}
//This function apply the kernel matrix to one pixel which is on image.
//Implementation to 5x5 kernel
float Image :: PutFilterOnPoint_5x5(int PixelIndexX,int PixelIndexY,float KernelMatrix[5][5]){
  float neighborPixels[5][5] = {{0}} ;
  int i,j;
  for(i=-1;i<4;i++){
    for(j=-1;j<4;j++){    
      //when getting borders, algorithm add 0s for out of image
      if( ((PixelIndexX+i)>=0 && (PixelIndexY+j)>=0)     &&   ((PixelIndexX+i < this->getRow()) && (PixelIndexY+j < this->getCol())))
        neighborPixels[i+1][j+1] = this->getPix(PixelIndexX+i,PixelIndexY+j);
      else
        neighborPixels[i+1][j+1] = 0 ;
    }}

  //apply filter for the point-- cross filter and pixel values and sum up all of them 
  float sum = 0 ;
  for(i=0;i<5;i++){
    for(j=0;j<5;j++){
      sum += (neighborPixels[i][j] * KernelMatrix[i][j]);
    }}

  cout<<sum ; 

  // to test
  for(i=0;i<5;i++)
    for(j=0;j<5;j++)
      cout<<neighborPixels[i][j]<<"\n" ;


  return sum ;

}
//I got from https://www.geeksforgeeks.org/gaussian-filter-generation-c/
//can be defined with hand but this is more flexible 
void CreateGaussFilter_5x5(float GKernel[][5])
{
    // initialising standard deviation to 1.0
    double sigma = 1.0;
    double r, s = 2.0 * sigma * sigma;
 
    // sum is for normalization
    double sum = 0.0;
  
    // generating 5x5 kernel
    for (int x = -2; x <= 2; x++) {
        for (int y = -2; y <= 2; y++) {
            r = sqrt(x * x + y * y);
            GKernel[x + 2][y + 2] = (exp(-(r * r) / s)) / (M_PI * s);
            sum += GKernel[x + 2][y + 2];
        }
    }
 
    // normalizing the Kernel
    for (int i = 0; i < 5; ++i)
        for (int j = 0; j < 5; ++j)
            GKernel[i][j] /= sum;
}
//Laplacian Filter can be used for sharping
//this is 3x3
Image Image :: LaplacianFilter(){
  
  Image temp(this->getRow(),this->getCol()) ;
  //Laplacian kernel
  float KernelMatrix[3][3] = {{1,1,1},{1,-8,1},{1,1,1}};
  int i,j ;
  float filteredValue ;
  //walk on each pixel and apply the filter with PutFilterOnPoint_5x5 
  for(i=0;i<this->getRow();i++){
    for(j=0;j<this->getCol();j++){
        filteredValue = this->PutFilterOnPoint_3x3(i,j,KernelMatrix);
        temp(i,j) = this->getPix(i,j) - filteredValue ;
    }}
  return temp ;
}
//Gaussian Filter can be used to blur an image.
//this is 5x5.But can implemented easily for different sizes with change into function
Image Image :: GaussFilt_5x5(){
  Image temp(this->getRow(),this->getCol()) ;
  float gKernel[5][5];
  //create an Gaussian kernel
  CreateGaussFilter_5x5(gKernel);
  int i,j ;
  float filteredValue ;
  //walk on each pixel and apply the filter with PutFilterOnPoint_5x5 
  for(i=0;i<this->getRow();i++){
    for(j=0;j<this->getCol();j++){
        filteredValue = this->PutFilterOnPoint_5x5(i,j,gKernel);
        temp(i,j) = filteredValue ;
    }}
  return temp ;

}

Image Image :: HighBoostFilter(int k){
  //if k == 1 called unsharp process
  //3 steps to create result image
  // result(x,y) = mask(x,y) + k*blured(x,y)
  Image blured(this->getRow(),this->getCol()) ;
  Image mask(this->getRow(),this->getCol()) ;
  Image result(this->getRow(),this->getCol()) ;
  //apply 5x5 gauss kernel
  blured = this->GaussFilt_5x5();
  int i,j ;
  for(i=0;i<this->getRow();i++){
    for(j=0;j<this->getCol();j++){
      mask(i,j) = this->getPix(i,j) -  blured.getPix(i,j);
      result(i,j) = this->getPix(i,j) + k*mask.getPix(i,j);

    }
  }
  return result;
}



  //END OF YOUR FUNCTIONS //
  
  
