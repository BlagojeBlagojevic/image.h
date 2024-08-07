#ifndef IMAGE_H
#define IMAGE_H
#include<assert.h>
#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<complex.h>
//LETS BE INCLUDED BY DEFAULT
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

//MACRO USED FOR GETING PIXEL IN A MATRIX LIKE STRUCTURE
#define PIXEL_AT(image,y,x) (image).pixels[(y)*(image).width + (x)]


//IMAGE PARAMETAR MACRO USED FOR LOADING IMAGE PATAMETARS IF IMAGE IS ALRREDY ALOCATED FROM STB IMAGE
#define IMAGE_PARAMETARS(i) (i).width/(i).chanels,(i).height,(i).chanels



#define IMAGE_ASSERT assert

#define IMAGE_CALLOC calloc

#include<complex.h>

typedef struct {

	int width;       //WIDTH  OF IMAGE IN PIXELS
	int height;      //HEIGHT OF IMAGE IN PIXELS*NUMBER OF CHANELS
	int chanels;     //HOW    MUTCH PIXEL IS USED TO REPRESENT THE IMAGE
	uint8_t *pixels; //ROW PIXELS

	} Image;

typedef struct {
	int width;
	int height;
	uint32_t *pixels;
	} Image32;



Image Image_Alloc(int width,int height,int chanels);  //ALLOCATE IMAGE FULL OF ZEROS

Image Image_Alloc_Name(const char* name);   //DYNAMICLY ALLOCATE IMAGE ALLOCATION IS IN STB_IMAGE
Image Image_Alloc_Name_Fft(const char* name,int xd,int yd);
void Image_Alloc_Grey(Image i, Image *a);
void Image_Free(Image i);

Image   Image32_to_Image(Image32);
Image32 Image_to_Image32(Image i);
Image32 Image32_Alloc_Name(const char* name);
Image32 Image_Alloc32_t(int width, int height); // 32 BIT IMAGE
void Image32_Save(Image32 i, const char* name); //WRITE IMAGE AS JPG
void Image32_Free(Image32 i);
Image32 Image_Field(Image a, Image b, int r);
void Image32_Applay_Kernel(Image32 a,Image32 i,float *kernel,int width,int height);

void Image_Set(Image i, uint8_t number);

void Image_Save(Image i, const char* name); //WRITE IMAGE AS JPG
void Image_Print(Image i);                  //PRINT THE IMAGE WIDTH HEIGHT, CHANELS TO CONSOL NOT USE

void Image_Sum(Image a, Image b);           //SUM TWO IMAGES IN IMAGE ASSERT A MUST BE BIGER OR EQUAL
void Image_Dec(Image a, Image b);           //SUB TWO IMAGES IN IMAGE ASSERT A MUST BE BIGER OR EQUAL
void Image_Mul(Image a, Image b);           //MUL TWO IMAGES IN IMAGE ASSERT A MUST BE BIGER OR EQUAL
void Image_Div(Image a, Image b);           //DIV TWO IMAGES IN IMAGE ASSERT A MUST BE BIGER OR EQUAL
void Image_Sum_Shift(Image a, Image b,size_t startX,size_t startY); //SUM OF 2 IMAGES FROM START  IN A
void Image_Dec_Shift(Image a, Image b,size_t startX,size_t startY); //SUB OF 2 IMAGES FROM START  IN A
void Image_Mul_Shift(Image a, Image b,size_t startX,size_t startY); //MUL OF 2 IMAGES FROM START  IN A
void Image_Div_Shift(Image a, Image b,size_t startX,size_t startY); //DIV OF 2 IMAGES FROM START  IN A

void Image_Copy(Image dest, Image source);  //COPY IMAGE FROM SOURCE TO DEST
void Image_Copy_Shift(Image dest, Image source,size_t startX,size_t startY);   //COPY IMAGE FROM SOURCE TO DEST STARTING FROM STARTX STARTY
void Image_Shift_Stop(Image dest, Image source,size_t stopX,size_t stopY);

void Image_Applay_Kernel(Image a,Image i,float *kernel,int width,int height);//APPLAY CONVOLUTION TO IMAGE
float KERNEL_IDENTITY[] = {0,0,0,0,1,0,0,0,0};
float KERNEL_SHARPEN[] = {0,-1,0,-1,5,-1,-0,-1,-0,};
float KERNEL_BLURE[] = {0.11,0.11,0.11,0.11,0.11,0.11,0.11,0.11,0.11,};
float KERNEL_EDGE[] = {0,-1,0,-1,4,-1,-0,-1,-0,};
float KERNEL_RIDGE[] = {-1,-1,-1,-1,8,-1,-1,-1,-1,};
float KERNEL_BL[]= {0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,};
float KERNEL_BOXBLURE[]= {1,1,1,1,1,1,1,1,1,};
float KERNEL_SOBEL_X[] = {1, 0, -1,2,0,-2,1,0,-1};
float KERNEL_SOBEL_Y[] = {1, 2, 1,0,0,0,-1,-2,-1};
float KERNEL_WHITE[] = {1,1,1,1,10,1,1,1,1};
void Image_Black_White_Filtar(Image i, int Pixel_Treshold);  //MAKE IMAGE BLACK AND WHITE
void Image_Zero_Chanel(Image i, int chanel);                 //REMOVE R,G,B,A CHANEL(COLOR)
void Image_Invert(Image i);         //CHANGE IMAGE PIXELS INTO (INVERT) 255 - img.pixels[i]

void Image_Center_Of_Mass(Image i,size_t *yx);  //FUNCTION USED TO CALCULATE CENTER OF MASS IN IMAGE THIS IS UDED TO DESIDE IS SOMTETHING IN IMAGE, SUBIMAGE
void Image_Histogram(Image i, int histogram[255]);
float Image_Similarity(Image i, Image b);


void Image_Draw_Rect(Image i, size_t startX,size_t startY,size_t h,size_t w,uint8_t pixel);
void Image_Draw_Point(Image i, size_t startX,size_t startY, uint8_t r, uint8_t g, uint8_t b);

size_t Load_Binary_To_Image(Image i,char *name);
void Image_To_Binary(Image i,size_t bin_size,char *name);


//FFT
void fft(uint8_t *in,size_t pivot,int complex *out,size_t n);

//SEAM_CARVING
Image Image_Seam_Carving(const char* name);

#endif

#ifdef IMAGE_IMPLEMENTATION

Image Image_Alloc(int width,int height,int chanels) { //ALLOCATE IMAGE FULL OF ZEROS
	Image i;
	i.chanels = chanels;
	i.width   = chanels * width; //MULTIPLAY WITH NUMBER OF CHANELS
	i.height  = height;
	i.pixels = (uint8_t*) IMAGE_CALLOC(chanels * width * height,sizeof(*i.pixels));
	return i;
	}



Image Image_Alloc_Name(const char* name) {  //DYNAMICLY ALLOCATE IMAGE ALLOCATION IS IN STB_IMAGE
	Image i;
	i.pixels = stbi_load(name,&i.width,&i.height,&i.chanels,0);
	i.width  = i.chanels * i.width; //MULTIPLAY WITH NUMBER OF CHANELS
	return i;
	}



void Image_Alloc_Grey(Image i, Image *a) {


	*a = Image_Alloc(i.width / i.chanels,i.height,1);
	size_t counter = 0;
	for(size_t y = 0; y < i.height; y++) {
		for (size_t x = 0; x < i.width; x+=i.chanels) {
			uint32_t sum = 0;
			for (size_t z = 0; z < i.chanels; z++) {
				sum+=PIXEL_AT(i,y,x+z);
				}
			PIXEL_AT(*a, y, counter++) = sum / 3;
			if(counter == a->width)
				counter = 0;

			}

		}

	}




void Image_Save(Image i, const char* name) { //WRITE IMAGE AS JPG

	stbi_write_jpg(name,(int)(i.width / i.chanels),i.height,i.chanels,i.pixels, 100);
	}


void Image_Print(Image i) { //PRINT THE IMAGE WIDTH HEIGHT, CHANELS TO CONSOL NOT USE

	printf("__________________________________________________________________\n");

	printf("width %d height: %d chanels :%d\n",i.height,(int)(i.width/i.chanels),i.chanels);

	printf("\n__________________________________________________________________\n");
	}
void Image_Sum(Image a, Image b) {   //SUM TOW IMAGES IN IMAGE ASSERT A MUST BE BIGER OR EQUAL

	IMAGE_ASSERT(a.width  >=  b.width);
	IMAGE_ASSERT(a.height >=  b.height);


	for(size_t y = 0; (y < a.height) && (y < b.height); y++) {
		for(size_t x = 0; (x < a.width) && (x < b.width); x++) {

			PIXEL_AT(a,y,x) += PIXEL_AT(b,y,x);
			}
		}
	}

void Image_Dec(Image a, Image b) {   //SUM TOW IMAGES IN IMAGE ASSERT A MUST BE BIGER OR EQUAL

	IMAGE_ASSERT(a.width  >=  b.width);
	IMAGE_ASSERT(a.height >= b.height);


	for(size_t y = 0; (y < a.height) && (y < b.height); y++) {
		for(size_t x = 0; (x < a.width) && (x < b.width); x++) {

			PIXEL_AT(a,y,x) -= PIXEL_AT(b,y,x);
			}
		}
	}

void Image_Mul(Image a, Image b) {   //SUM TOW IMAGES IN IMAGE ASSERT A MUST BE BIGER OR EQUAL

	IMAGE_ASSERT(a.width  >=  b.width);
	IMAGE_ASSERT(a.height >= b.height);


	for(size_t y = 0; (y < a.height) && (y < b.height); y++) {
		for(size_t x = 0; (x < a.width) && (x < b.width); x++) {
			PIXEL_AT(a,y,x) *= PIXEL_AT(b,y,x);
			}
		}
	}

void Image_Div(Image a, Image b) {   //SUM TOW IMAGES IN IMAGE ASSERT A MUST BE BIGER OR EQUAL

	IMAGE_ASSERT(a.width  >=  b.width);
	IMAGE_ASSERT(a.height >= b.height);


	for(size_t y = 0; (y < a.height) && (y < b.height); y++) {

		for(size_t x = 0; (x < a.width) && (x < b.width); x++) {
			//IMAGE_ASSERT(PIXEL_AT(b,y,x) != 0);
			if(PIXEL_AT(b,y,x)!=0)
				PIXEL_AT(a,y,x) /= PIXEL_AT(b,y,x);
			}
		}
	}

void Image_Copy(Image dest, Image source) {
//	IMAGE_ASSERT(dest.width  >= source.width);
	//IMAGE_ASSERT(dest.height >= source.height);
	for(size_t y = 0; (y < dest.height) && (y < source.height); y++) {
		for(size_t x = 0; (x < dest.width) && (x < source.width); x++) {
			PIXEL_AT(dest,y,x) = PIXEL_AT(source,y,x);
			}
		}
	}
void Image_Set(Image i, uint8_t number) {

	for(size_t y = 0; y < i.height; y++) {
		for(size_t x = 0; x < i.width; x++) {
			PIXEL_AT(i,y,x) = number;
			}
		}
	}

void Image_Applay_Kernel(Image a,Image i, float  *kernel, int width,int height) {
	//IMAGE_ASSERT(1);
	//IMAGE_ASSERT(1);
	//Image a = Image_Alloc(IMAGE_PARAMETARS(i));
	for(size_t y = 0; y < i.height - height ; y++) {
		for(size_t z = 0; z < i.chanels; z++)
			for(size_t x = 0; x < i.width - width; x+=i.chanels) {
				float sum = 0.0f;
				//printf("sum %d\n",sum);
				for(size_t j = 0; j < height; j++) {
					for(size_t k = 0; k < width; k++) {

						sum+=(float)(kernel[j*height + k]*(float)PIXEL_AT(i,y+j,x+(k)*z));

						//printf("sum %d\n",sum);
						}
					}
				//sum = (uint8_t)sum;
				if(sum  > 255.0f) {
					sum = 255.0f;
					}

				if(sum < 0.0f) {
					sum = 0.0f;
					}

				//printf("sum %u\n",(uint8_t)sum);
				PIXEL_AT(a,y,x + z) = (uint8_t)sum;
				}
		}
	//return a;

	}
void Image_Black_White_Filtar(Image img, int Pixel_Treshold) {
	for(size_t i = 0; i < img.width*img.height-3; i+=img.chanels) {
		float sum = img.pixels[i]+img.pixels[i+1]+img.pixels[i+2];
		sum/=img.chanels;
		if(sum > Pixel_Treshold) {
			for(size_t j = 0; j < img.chanels; j++)
				img.pixels[i + j]   = 255;
			}
		else {
			for(size_t j = 0; j < img.chanels; j++)
				img.pixels[i+j]   = 0;
			}
		}
	}

void Image_Zero_Chanel(Image i, int chanel) {
	for(size_t y = 0; y < i.height*i.width-3; y+=i.chanels) {
		i.pixels[y + chanel] = 0;

		}
	}
void Image_Invert(Image i) {
	for(size_t y = 0; y < i.height*i.width-3; y++)
		i.pixels[y] = 255 - i.pixels[y];
	}
void Image_Center_Of_Mass(Image i,size_t *yx) {
	Image_Black_White_Filtar(i,60);  // That Image is Allredy Black and White
	size_t xc = 0,yc = 0,nyc=0;
	for(size_t y = 0; y < i.height - 1; y++) {
		for(size_t x = 0,counter = 0; x < i.width; x+=i.chanels,counter++) {
			//printf("x %d y %d\n",x,y);
			if(PIXEL_AT(i,y,x) >= 10) {
				xc+=counter;
				yc+=y;
				nyc++;
				}
			}

		}
	if(nyc!=0) {
		yx[0] += yc / nyc;
		yx[1] += xc / nyc;
		//printf("y %d x %d",yc ,xc);
		}
	//printf("y %d x %d",yc ,xc);
	//system("pause");
	}

void Image_Mul_Shift(Image a, Image b,size_t startX,size_t startY) {
	IMAGE_ASSERT((startY + a.height) < b.height);
	IMAGE_ASSERT((startX*a.chanels + a.width) < b.width);
	for(size_t y = 0; y <a.height; y++) {
		for(size_t x = 0; x <a.width; x++) {
			//printf("x %d y %d\n",x,y);
			PIXEL_AT(a,y,x) *= PIXEL_AT(b,y+startY,x+(startX*a.chanels));
			//printf("Pixel %d\n",PIXEL_AT(a,(y-startY),(x - startX)));
			}
		}
	}
void Image_Sum_Shift(Image a, Image b,size_t startX,size_t startY) {
	IMAGE_ASSERT((startY + a.height) < b.height);
	IMAGE_ASSERT((startX*a.chanels + a.width) < b.width);
	for(size_t y = 0; y <a.height; y++) {
		for(size_t x = 0; x <a.width; x++) {
			//printf("x %d y %d\n",x,y);
			PIXEL_AT(a,y,x) += PIXEL_AT(b,y+startY,x+(startX*a.chanels));
			//printf("Pixel %d\n",PIXEL_AT(a,(y-startY),(x - startX)));
			}
		}


	}

void Image_Dec_Shift(Image a, Image b,size_t startX,size_t startY) {
	IMAGE_ASSERT((startY + a.height) < b.height);
	IMAGE_ASSERT((startX*a.chanels + a.width) < b.width);
	for(size_t y = 0; y <a.height; y++) {
		for(size_t x = 0; x <a.width; x++) {
			//printf("x %d y %d\n",x,y);
			PIXEL_AT(a,y,x) -= PIXEL_AT(b,y+startY,x+(startX*a.chanels));
			//printf("Pixel %d\n",PIXEL_AT(a,(y-startY),(x - startX)));
			}
		}


	}

void Image_Div_Shift(Image a, Image b,size_t startX,size_t startY) {
	IMAGE_ASSERT((startY + a.height) < b.height);
	IMAGE_ASSERT((startX*a.chanels + a.width) < b.width);
	for(size_t y = 0; y <a.height; y++) {
		for(size_t x = 0; x <a.width; x++) {
			IMAGE_ASSERT(PIXEL_AT(b,y+startY,x+(startX*a.chanels))!=0);
			PIXEL_AT(a,y,x) /= PIXEL_AT(b,y+startY,x+(startX*a.chanels));
			//printf("Pixel %d\n",PIXEL_AT(a,(y-startY),(x - startX)));
			}
		}


	}

void Image_Copy_Shift(Image dest, Image source,size_t startX,size_t startY) {
	IMAGE_ASSERT(dest.width  >= source.width);
	IMAGE_ASSERT(dest.height >= source.height);
	IMAGE_ASSERT((startY + dest.height) < source.height);
	IMAGE_ASSERT((startY*dest.chanels + dest.width) < source.width);
	for(size_t y = 0; y < dest.height; y++) {
		for(size_t x = 0; x < dest.width; x++) {
			PIXEL_AT(dest,y,x) = PIXEL_AT(source,y+startY,x+(startX*dest.chanels));
			}
		}
	}

void Image_Draw_Rect(Image i, size_t startX,size_t startY,size_t h,size_t w,uint8_t pixel) {
	IMAGE_ASSERT((startY + h) <= i.height);
	IMAGE_ASSERT((startX + w) <= i.width);
	for(size_t y = startY; y < startY + h; y++) {
		for(size_t x = (startX*i.chanels); x < (startX + w)*i.chanels; x++) {
			PIXEL_AT(i,y,x) = pixel;
			}
		}
	}


void Image_Draw_Point(Image i, size_t startX,size_t startY, uint8_t r, uint8_t g, uint8_t b) {
	IMAGE_ASSERT((startY) <= i.height);
	IMAGE_ASSERT((startX) <= i.width);
	if(startX%3!=0)
		startX-=startX%3;
	PIXEL_AT(i, startY, startX)      = r;
	PIXEL_AT(i,startY,startX + 1)    = g;
	PIXEL_AT(i,startY,startX + 2)    = b;
	}


void Image_Free(Image i) {
	free(i.pixels);
	}

size_t Load_Binary_To_Image(Image i,char *name) {
	FILE *f = fopen(name,"rb");
	if(f==NULL)
		IMAGE_ASSERT(0 && " FILE IS NOT LOADED !!! ");
	for(size_t y = 0; y < i.height; y++) {
		for(size_t x = 0; x < i.width; x++) {
			if(feof(f) != 0) {
				fclose(f);
				return x+y*i.width-1;
				}
			else {
				fread(&PIXEL_AT(i,y,x),sizeof(uint8_t),1,f);
				//printf("%d\n",PIXEL_AT(i,y,x));
				}
			}
		}

	}
void Image_To_Binary(Image i,size_t bin_size,char *name) {
	FILE *f = fopen(name,"wb+");
	//for(size_t y = 0;y < bin_size;y++){
	fwrite(i.pixels,sizeof(uint8_t),bin_size,f);
	printf("Nesto");
	//}
	fclose(f);

	}

void fft(uint8_t *in,size_t pivot,int complex *out,size_t n) { //coll
	float pi=3.141569;
	assert(n > 0);
	//printf("nesto");
	if(n==1) {
		out[0]=in[0];
		return; //braking assert error
		}
	fft(in,pivot*2,out,n/2);//even
	fft(in+pivot,pivot*2,n/2+out,n/2);//odd
	for (size_t k = 0; k < n/2; k++) {
		float t=(float)k/n;
		float complex e = out[k];
		float complex v = cexp(-2*pi*I*t)*out[k+n/2];
		out[k]=e+v;
		out[k+n/2]=e-v;
		}



	}


Image Image_Alloc_Name_Fft(const char* name,int xd,int yd) {
	Image ia = Image_Alloc_Name(name);
	IMAGE_ASSERT(xd <= 500 && yd <= 500);
	int complex mag[xd*yd];
	fft(ia.pixels,0,mag,xd*yd);
	//system("pause");
	int max_r = 0,max_i = 0;
	for(size_t i = 0; i < xd*yd; i++) {
		if(creal(mag[i]) > max_r) {
			max_r = (int)creal(mag[i]);
			}
		if(cimag(mag[i]) > max_i) {
			max_i = (int)cimag(mag[i]);
			}
		}


	Image b = Image_Alloc(xd,yd,1);
	size_t z = 0;
	for(size_t y = 0; y < yd; y++) {
		for(size_t x = 0; x < xd; x++) {
			float real = (creal(mag[z])); // max_r;
			float imag = (cimag(mag[z])); // max_i;
			uint8_t magnitude = (uint8_t)(sqrt(real*real + imag*imag)); //* 255;
			PIXEL_AT(b,y,x) = magnitude;
			z++;
			}
		}
	free(ia.pixels);
	return b;


	}




void Image_Histogram(Image i, int histogram[255]) { // PROVIDE grey scale image
	IMAGE_ASSERT(i.chanels == 1);
	for (size_t x = 0; x < 255; x++) {
		histogram[x] = 0;
		}

	for(size_t y = 0; y < i.height; y++) {

		for (size_t x = 0; x < i.width; x++) {
			histogram[PIXEL_AT(i,y,x)]++;
			}

		}

	}


float Image_Similarity(Image i, Image b) {

	int histogram_x[255], histogram_y[255];
	Image grey_x, grey_y;
	Image_Alloc_Grey(i, &grey_x);
	Image_Alloc_Grey(b,&grey_y);
	Image_Histogram(grey_y,histogram_y);
	Image_Histogram(grey_x,histogram_x);
	double sum = 0,sum_y = 0, sum_x = 0;
	for (size_t x = 0; x < 255; x++) {
		sum_x += histogram_x[x];
		sum_y += histogram_y[x];

		}
	//printf("sum_y %d sum_y %d",sum_x, sum_y);
	for (size_t x = 0; x < 255; x++) {
		sum+=fabs(((double)histogram_x[x] / (double)sum_x - (double)histogram_y[x] / (double)sum_y));

		}

	sum = 1.0f - sum;

	printf("Percent of simaliriti betwen images is %f \n", sum);

	Image_Free(grey_x);
	Image_Free(grey_y);
	return sum;


	}


Image32 Image_Alloc32_t(int width,int height) { //ALLOCATE IMAGE FULL OF ZEROS
	Image32 i;
	i.width   = width; //MULTIPLAY WITH NUMBER OF CHANELS
	i.height  = height;
	i.pixels = (uint32_t*) IMAGE_CALLOC(width * height,sizeof(uint32_t));
	return i;
	}

void Image32_Free(Image32 i) {
	free(i.pixels);
	}
void Image32_Save(Image32 i, const char* name) { //WRITE IMAGE AS JPG

	stbi_write_jpg(name,(int)(i.width),i.height,4,i.pixels, 100);
	}

Image32 Image_Field(Image a, Image b, int r) {
	Image grey1, grey2;
	Image_Alloc_Grey(a, &grey1);
	Image_Alloc_Grey(b, &grey2);
	Image32 distances = Image_Alloc32_t(grey1.width,grey1.height);
	//init_Array(&distances, 1000);
	for (size_t y = 0; y < grey1.height; y++) {
		for (size_t x = 0; x < grey2.width; x++) {
			if(PIXEL_AT(grey1, y, x) != PIXEL_AT(grey2, y, x)) {
				int start_x = x - r, start_y = y - r, stop_x = x + r, stop_y = y + r;
				if(start_x <= 0)
					start_x = 0;
				if(stop_x >= grey1.width)
					stop_x = grey1.width - 1;
				if(start_y <= 0)
					start_y = 0;
				if(stop_y >= grey1.height)
					stop_y = grey1.height - 1;
				float min_distance = 0xFFFFFF,distance;
				for(size_t i = start_y; i < stop_y; i++) {
					for (size_t j = start_x; j < stop_x; j++) {
						if(PIXEL_AT(grey1, i, j) == PIXEL_AT(grey2, i, j)) {
							distance = sqrt(i*i + j*j);
							if(distance < min_distance) {
								min_distance = distance;
								}
							}
						}
					}
				PIXEL_AT(distances, y, x) = (uint32_t)min_distance;
				}

			else {
				PIXEL_AT(distances, y, x) = (uint32_t)0;

				}
			}
		}

	//Image32_Free(distances)
	Image_Free(grey1);
	Image_Free(grey2);
	return distances;

	}
void Image32_Applay_Kernel(Image32 a,Image32 i,float *kernel,int width,int height) {

	IMAGE_ASSERT(a.height <= i.height);
	IMAGE_ASSERT(a.width <= i.width);

	for (size_t y = 0; y < a.height - height; y++) {
		for (size_t x = 0; x < a.width - width; x++) {

			int64_t sum = 0;
			for (size_t z = 0; z < height; z++) {
				for (size_t j = 0; j < width; j++) {
					//printf("x %d y%d\n",j,z);
					sum+= PIXEL_AT(i,y+z,x+j)*kernel[y*z + j];
					}

				}
			PIXEL_AT(a,y, x) = (uint32_t)sum;
			//printf("%d\n",PIXEL_AT(a,y,x));
			}

		}

	}



Image32 Image_to_Image32(Image i) {
	IMAGE_ASSERT(i.chanels >= 3);
	Image32 b = Image_Alloc32_t( (uint32_t)i.width / (uint32_t)i.chanels, i.height);
	memcpy(b.pixels,i.pixels,i.width*i.height);


	return b;

	}

Image Image32_to_Image(Image32 i) {
	//IMAGE_ASSERT(i.chanels > 3);
	Image b = Image_Alloc(i.width, i.height, 3);
	memcpy(b.pixels,i.pixels,i.width*i.height*3);
	return b;
	}


Image32 Image32_Alloc_Name(const char* name) {  //DYNAMICLY ALLOCATE IMAGE ALLOCATION IS IN STB_IMAGE

	Image a = Image_Alloc_Name(name);
	printf("nESTO\n");
	Image32 i = Image_to_Image32(a);
	Image_Free(a);
	return i;



	}
//UTILITI FUNCTIONS
size_t min_index(float *arr, size_t size){
	float min = arr[0];
	size_t index = 0;
	for(size_t i = 0; i < size; i++){
		if(min > arr[i]){
			min = arr[i];
			index = i;
		}
		
	}
	return index;
}

//SEAM CARVING
Image Image_Seam_Carving(const char* name){
	Image i = Image_Alloc_Name("ajn.jpg");

	Image a, b, c;
	Image_Alloc_Grey(i, &a);
	Image_Alloc_Grey(i, &b);
	Image_Alloc_Grey(i, &c);

	Image_Applay_Kernel(a, c, KERNEL_EDGE, 3, 3);
	Image_Applay_Kernel(b, c, KERNEL_EDGE, 3, 3);
	Image_Applay_Kernel(a, c, KERNEL_WHITE, 3, 3);
	Image_Applay_Kernel(b, c, KERNEL_WHITE, 3, 3);

	float E_treshold = 0;

	for(size_t y = 0; y < a.height; y++) {
		for(size_t x = 0; x < a.width; x++) {
			PIXEL_AT(c, y, x) = atan2(PIXEL_AT(a, y, x),PIXEL_AT(b, y, x))*180.0f/3.14f;
				E_treshold+= PIXEL_AT(c, y, x);
			}
		}
	E_treshold/= (a.height*a.width);
	E_treshold *= 3.0f;

	Image c_copy = Image_Alloc(IMAGE_PARAMETARS(c)); 
	Image_Copy(a, c);
	Image_Copy(c_copy, c);
	//Search minimum energy in function
	for(size_t x = 1; x < c.width; x++){
		int index = x;
		float E[3];
		float E_total = 0;
		for(size_t y = 0; y < c.height; y++){
			for(int z = -1; z <= 1; z++){
				E[z+1] = PIXEL_AT(c, y, index + z);
			}
			size_t min_inde = min_index(E, 3);
			if(E[min_inde] < E_treshold)
				E_total += E[min_inde];
			else{
				E_total = 0;
				break;
			}
			index+=min_inde;
			PIXEL_AT(c, y, index) = 250;
		}
		//CHECK IS E < THEN TRESHOLD
		E_total/= c.height;
		if((E_total < E_treshold) && E_total!=0){
			Image_Copy(c_copy, c);
		}
		else{
			Image_Copy(c, c_copy);
		}
		
		
	}
	
	Image_Dec(c, a);
	size_t counter = 0;
	for(size_t y = 0; y < c.height;y++){
		counter = 0;
		for(size_t x = 0; x < c.width; x++){
			
			if(PIXEL_AT(c, y, x)){
				
				memcpy(&PIXEL_AT(i, y, x * 3),&PIXEL_AT(i, y, x * 3 + 3), i.width - (x * 3 + 3));
				counter++;
			
			}
			
		}

	}
	//printf("Width %d\n", (i.width )/3 - counter);
	
	Image i_save = Image_Alloc((i.width)/3 - counter + 50, i.height,i.chanels);
	//system("pause");
	Image_Copy(i_save, i);
	Image_Free(i);
	Image_Free(a);
	Image_Free(b);
	Image_Free(c);
	Image_Free(c_copy);
	//Image_Free(i);
	return i_save;
}






#endif




#ifdef DYNAMIC

#ifndef ARRAY_TYPE
#define ARRAY_TYPE uint32_t
#endif

typedef struct d {

	ARRAY_TYPE *array;
	size_t index_of_last;  //INDEX OF LAST ELEMET
	size_t _size;          //DEFINE THIS SIZE(IN INIT OF ARRAY)

	} D_ARRAY;



void init_Array(D_ARRAY *array,size_t initialSize) {

	array->array = calloc(initialSize,sizeof(ARRAY_TYPE));
	array->_size = initialSize;
	array->index_of_last = 0;


	}
void insert_Array(D_ARRAY *array,ARRAY_TYPE elem) {

	if(array->index_of_last == array->_size) {
		array->_size *= 2;
		array->array = realloc(array->array,sizeof(ARRAY_TYPE)*array->_size);
		if(array->array == NULL)
			assert(0 && "REALOC FAIL!!! ");
		printf("Realloc!!!\n");

		}
	array->array[array->index_of_last++] = elem;

	}

void print_Array(D_ARRAY *array) {
	for(size_t i = 0; i < array->index_of_last; i++) {
		printf("%d\n", (int)array->array[i]);

		}

	}


#endif
