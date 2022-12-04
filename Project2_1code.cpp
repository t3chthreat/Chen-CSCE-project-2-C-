#include <iostream>
 #include <fstream>
 #include <string>
 #include <stdlib.h>
 using namespace std;
 class image
{
 private: uint8_t ***img; size_t nrows, ncols; 
string filename; 
public: image();
 image(size_t, size_t);
 image(string);
 ~image();
 void pixColor(size_t, size_t);
 void imagePatch(size_t, size_t, size_t);
 void writePatch(size_t, size_t, size_t, string); 
void pixAvg(image, image);
 size_t get_nrows();
 size_t get_ncols();
 };
 image::image()
{
 img = new uint8_t** [1];
 img[0] = new uint8_t* [1];
 img[0][0] = new uint8_t [3];
img[0][0][0] = 0;
 img[0][0][1] = 0;
 img[0][0][2] = 0;
 nrows = 1;
 ncols = 1; 
filename = "default";
}
 image::image(size_t nr, size_t nc)
 { 
 img = new uint8_t** [nr]; 
 for(size_t i=0; i<nr; i++)
 { 
 img[i] = new uint8_t* [nc];
 for(size_t j=0; j<nc; j++)
 { 
 img[i][j] = new uint8_t [3];
  img[i][j][0] = 0;
   img[i][j][1] = 0;
    img[i][j][2] = 0;
	 } 
	 } 
	 nrows = nr; ncols = nc; 
	 filename = "default"; 
	 } 
	 image::image(string fn)
	 { 
	 filename = fn; 
	 ifstream inFile;
	  inFile.open(filename);
	   if(!inFile)
	   { 
	   cerr << "Unable to open file";
	    exit(1);
		 } 
		 string garbage; 
		 inFile >> garbage >> nrows >> ncols >> garbage; 
		 img = new uint8_t** [nrows]; 
		 for(size_t i=0; i<nrows; i++)
		 { 
		 img[i] = new uint8_t* [ncols];
		  for(size_t j=0; j<ncols; j++)
		  {
		   img[i][j] = new uint8_t [3];
		    inFile >> img[i][j][0] >> img[i][j][1] >> img[i][j][2];
			 }
			  
			  } 
			  } 
			  image::~image()
			  { 
			  for(size_t i=0; i<nrows; i++)
			  { 
			  for(size_t j=0; j<ncols; j++)
			  { 
			  delete[] img[i][j]; 
			  }
			   delete[] img[i]; 
			   } 
			   delete[] img;
			    } 
				void image::pixColor(size_t i, size_t j)
				{ 
				cout << (int)img[i][j][0] << " " << (int)img[i][j][1] << " " << (int)img[i][j][2] << endl; 
				} 
				void image::imagePatch(size_t i, size_t j, size_t sz)
				{ 
				image img_patch(2*sz+1, 2*sz+1); 
				for(size_t r=0; r<2*sz+1; r++)
				{ 
				for(size_t c=0; c<2*sz+1; c++)
				{ 
				for(size_t k=0; k<3; k++)
				{ 
				img_patch.img[r][c][k] = img[i-sz+r][j-sz+c][k]; 
				} 
				} 
				} 
				} 
				void image::writePatch(size_t i, size_t j, size_t sz, string fn)
				{
				 image img_patch(2*sz+1, 2*sz+1);
				  for(size_t r=0; r<2*sz+1; r++)
				  { for(size_t c=0; c<2*sz+1; c++)
				  { for(size_t k=0; k<3; k++)
				  { 
				  img_patch.img[r][c][k] = img[i-sz+r][j-sz+c][k];
				   }
				    }
					 } 
					 ofstream outFile; 
					 outFile.open(fn); 
					 outFile << "P3" << endl;
					  outFile << 2*sz+1 << " " << 2*sz+1 << endl; 
					  outFile << 255 << endl; 
					  for(size_t r=0;r<2*sz+1; r++)
					  { 
					  for(size_t c=0; c<2*sz+1; c++)
					  { 
					  outFile << (int)img_patch.img[r][c][0] << " " << (int)img_patch.img[r][c][1] << " " << (int)img_patch.img[r][c][2] << endl; 
					  } 
					  } 
					  outFile.close();
					   } 
					   void image::pixAvg(image img1, image img2)
					   { 
					   image average(nrows, ncols);
					    for(size_t i=0; i<nrows; i++)
						{ 
						for(size_t j=0; j<ncols; j++)
						{ 
						for(size_t k=0; k<3; k++)
						{ 
						average.img[i][j][k] = (img1.img[i][j][k] + img2.img[i][j][k])/2;
						 } 
						 }
						  } 
						  ofstream outFile; outFile.open("average.ppm"); 
						  outFile << "P3" << endl;
						   outFile << nrows << " " << ncols << endl; 
						   outFile << 255 << endl; 
						   for(size_t i=0; i<nrows; i++)
						   { 
						   for(size_t j=0; j<ncols; j++)
						   {
						    outFile << (int)average.img[i][j][0] << " " << (int)average.img[i][j][1] << " " << (int)average.img[i][j][2] << endl;
							 } 
							 }
							  outFile.close();
							   } 
							   size_t image::get_nrows()
							   { 
							   return nrows;
							    }
								 size_t image::get_ncols()
								 { 
								 return ncols;
								  }
								   int main()
								   {
								    image img1("testImage2.ppm");
									image topLeft(nrows/2, ncols/2); 
									image topRight(nrows/2, ncols/2); 
									for(size_t i=0; i<nrows/2; i++)
									{ 
									for(size_t j=0; j<ncols/2; j++)
									{ 
									topLeft.img[i][j][0] = img1.img[i][j][0]; 
									topLeft.img[i][j][1] = img1.img[i][j][1];
									 topLeft.img[i][j][2] = img1.img[i][j][2];
									  } 
									  } 
									  ofstream outFile; 
									  outFile.open("topLeft.ppm"); 
									  outFile << "P3" << endl; 
									  outFile << nrows/2 << " " << ncols/2 << endl;
									   outFile << 255 << endl; 
									   for(size_t i=0; i<nrows/2; i++)
									   {
									    for(size_t j=0; j<ncols/2; j++)
										{ 
										outFile << (int)topLeft.img[i][j][0] << " " << (int)topLeft.img[i][j][1] << " " << (int)topLeft.img[i][j][2] << endl; 
										} 
										} 
										outFile.close(); 
										for(size_t i=0; i<nrows/2; i++)
										{ 
										for(size_t j=ncols/2; j<ncols; j++)
										{ 
										topRight.img[i][j-ncols/2][0] = img1.img[i][j][0]; 
										topRight.img[i][j-ncols/2][1] = img1.img[i][j][1];
										 topRight.img[i][j-ncols/2][2] = img1.img[i][j][2]; 
										 } 
										 } 
										 outFile.open("topRight.ppm");
										  outFile << "P3" << endl;
										   outFile << nrows/2 << " " << ncols/2 << endl;
										    outFile << 255 << endl; 
											for(size_t i=0; i<nrows/2; i++)
											{ 
											for(size_t j=0;j<ncols/2; j++)
											{ 
											outFile << (int)topRight.img[i][j][0] << " " << (int)topRight.img[i][j][1] << " " << (int)topRight.img[i][j][2] << endl; 
											}
											 }
											  outFile.close(); 
											  image img2("testImage4.ppm");
  image avgImg(nrows, ncols); avgImg.pixAvg(topLeft, topRight); 
  return 0;
   }