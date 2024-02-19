#define IMAGE_IMPLEMENTATION
#include"image.h"



int main(void) {
	
	Image i = Image_Alloc_Name("12.jpg");
	//Image i = Image_Alloc_Name("source.png");
	Image a = Image_Alloc(IMAGE_PARAMETARS(i));
	//Image b = Image_Alloc_Name("12.jpg");

	//uint32_t *image = stbi_load("12.jpg",);	
	float KERNEL_BL[]={0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,};
	Image_Applay_Kernel(a,i,KERNEL_EDGE,3,3);
	Image_Black_White_Filtar(a,5);
	Image_Invert(a); 
	//Image_Zero_Chanel(a,2);
	Image_Save(a,"saved.jpg");

	return 0;
	}
