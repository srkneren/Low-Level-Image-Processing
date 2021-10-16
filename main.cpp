/**************************************
 The original copy of the code can be found at http://web.eecs.utk.edu/~mkarakay/courses_files/testfiles.zip 
 and it is modified for ELM463/667
 **************************************/

#include "Image.h"

using namespace std;

int main(int argc, char **argv)
{
  
  
   
  
  
  
  
  
  char inputFileName[] = "Fig0338(a)(blurry_moon).pgm" ;
  char outputFileName[] = "histogramli.pgm";
  Image inputImage ;
  Image outputImage ;
  inputImage.readImage(inputFileName);
  outputImage =  inputImage.HighBoostFilter(5);
  outputImage.writeImage(outputFileName);



  // char inputFileName[] = "lena.pgm" ;
  // char outputFileName[] = "resized-lena.pgm";
  // Image inputImage ;
  // Image outputImage ;
  // inputImage.readImage(inputFileName);
  // outputImage =  inputImage.resizeImage(inputImage.getRow()*5,inputImage.getCol());
  // outputImage.writeImage(outputFileName);
  
  
  
  
  // char outputFileName[] = "createdImage2.pgm" ;
  // char resizedImageName[] = "resized.pgm" ;
  // Image createImage(10,15) ;
  // Image resizedImage ;
  
  // int rows =0  ;
  // int cols = 0 ;

  // //set pixels of the image
  // int initValue = 50 ;
  // for(rows =0 ;rows<createImage.getRow(); rows++){
    
  //   initValue = 50+rows ;

  //   for(cols=0;cols<createImage.getCol();cols++){
  //     createImage(rows,cols) = initValue;
  //     cout<<initValue<<"\n";
  //     initValue +=1 ;
  // }
  // }
   
 
  // int i,j ;
  // for(i =0;i<createImage.getRow();i++){
  //   for(j =0;j<createImage.getCol();j++){
  //     cout<<(int)createImage.getPix(i,j)<<"  " ;
  //   }
  //   cout<<"\n" ;
  // }

  // float a[3][3] = {{1,1,1},{1,-8,1},{1,1,1}};
  // createImage.PutFilterOnPoint(createImage.getRow()-1,createImage.getCol()-1,a);

  // createImage.writeImage(outputFileName);
  // resizedImage = createImage.resizeImage(20,30);
  // resizedImage.writeImage(resizedImageName) ;







 /* 
  char inputFileName[] = "lena.pgm";
  char outputFileName[] = "output.pgm";
  Image inputImage,Output ;
  inputImage.readImage(inputFileName);
  int th = 135 ;
  Output = inputImage.ThresholdFunc(135);
  Output.writeImage(outputFileName);
  */
  
  /*Image inputImage; 
  Image copyOfTheOriginalImage, copyOfTheOriginalImage2, copyOfTheOriginalImage3;
  Image thresholdedImage2, sumImage;


  
  char inputFileName[] = "lena.pgm";
  char outputFileName[] = "outLena.pgm";
  char outCopyOfOriginal[] = "copyOfTheOriginal.pgm";
  char outCopyOfOriginal2[] = "copyOfTheOriginal2.pgm";
  char outCopyOfOriginal3[] = "copyOfTheOriginal3.pgm";
  char outThresholdedImage[] = "thresholdedImage.pgm";
  char outThresholdedImage2[] = "thresholdedImage2_T100.pgm";
  char outConstantSumdImage[] = "constantSumdImage.pgm";
  
  
  // read the input image file
  inputImage.readImage(inputFileName);
  
  // write the input image to see if we can read and write it correctly
  inputImage.writeImage(outputFileName);
  

  // Create a copy of the input image - METHOD 1
  copyOfTheOriginalImage = inputImage; // you created one! see const Image operator=(const Image &);    // = operator overloading
  cout << "You copied the image.\n"; 
  
  // Write it out and see if it is correct
  copyOfTheOriginalImage.writeImage(outCopyOfOriginal);  
  
  // Create a copy of the input image - METHOD 2  
  copyOfTheOriginalImage2 = Image(inputImage); // see the constructor Image(const Image &);
   // Write it out and see if it is correct
  copyOfTheOriginalImage2.writeImage(outCopyOfOriginal2);  
  
  // Create a copy of the input image - METHOD 3  
  copyOfTheOriginalImage3 = inputImage.getImage(); // see the constructor Image(const Image &);
   // Write it out and see if it is correct
  copyOfTheOriginalImage3.writeImage(outCopyOfOriginal3);  
  
  
  // THRESHOLD THE IMAGE -- do it in MAIN -- the LONG WAY
  // create a new image with the same size as the inputImage
  // + declare thresholdedImage the first time!
  Image thresholdedImage(inputImage.getRow(), inputImage.getCol());
  
  // copy all the contents of the input image to thresholdedImage
  for (int rows = 0; rows < inputImage.getRow(); rows++)
     for (int cols = 0; cols < inputImage.getCol(); cols++)
         thresholdedImage(rows, cols) = inputImage(rows, cols);

  // and then, threshold it!
  for (int rows = 0; rows < inputImage.getRow(); rows++)
     for (int cols = 0; cols < inputImage.getCol(); cols++)
         if (thresholdedImage(rows, cols) > 100)
            thresholdedImage(rows, cols) = 255;
            else
            thresholdedImage(rows, cols) = 0;
            
  // write the thresholded image to a file called "thresholdedImage.pgm"
  thresholdedImage.writeImage(outThresholdedImage);
    cout << "You thresholded the image and wrote it to a file called thresholdedImage.pgm.\n";  
    
    
   // THRESHOLD THE IMAGE -- do it using a method -- the PREFERRED METHOD  
   thresholdedImage2 = inputImage.thresholdImage(100.0);
   // write the thresholded image to a file called "thresholdedImage2.pgm"
  thresholdedImage2.writeImage(outThresholdedImage2);
    cout << "You thresholded the image and wrote it to a file called thresholdedImage2.pgm.\n";  
   
  // summing with a constant
  sumImage = inputImage + 300;
  // rescaling when writing to a file
  sumImage.writeImage(outConstantSumdImage, true);
  // NOW, write a new method to take the negative of an image and then write it to a file!
   
   */

}
