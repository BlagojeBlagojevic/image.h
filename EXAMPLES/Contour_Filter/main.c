#define IMAGE_IMPLEMENTATION
#include "image.h"



int main(void){
	
	Image a = Image_Alloc_Name("5.jpg");
	Image b = Image_Alloc(IMAGE_PARAMETARS(a));
	Image_Black_White_Filtar(b,20);
	Image_Applay_Kernel(b,a,KERNEL_EDGE,3,3);
 	Image_Black_White_Filtar(b,40);
  	Image_Invert(b);
	Image_Save(b,"saved.jpg");
	printf("Nesto\n\n\n");
	system("pause");
	return 0;
}
