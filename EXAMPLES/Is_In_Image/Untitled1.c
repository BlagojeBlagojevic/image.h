#define IMAGE_IMPLEMENTATION
#include "image.h"

int main(void){

	
	Image a = Image_Alloc_Name("2.jpg");
	Image b = Image_Alloc_Name("1.jpg");
	Image c = Image_Alloc(300,590,3);
	Image d = Image_Alloc_Name("2.jpg");
	Image f = Image_Alloc(300,590,3);
	Image_Dec(d,d);
	Image_Dec(a,b);
  Image_Black_White_Filtar(a,60);
	Image_Set(c,1);
	Image_Mul_Shift(c,a,1190,0);
	Image_Set(f,1);
	Image_Mul_Shift(f,d,1190,0);
	size_t yx[2];
	yx[0] = 0;
	yx[1] = 1200;
	size_t yx1[2];
	yx1[0] = 0;
	yx1[1] = 1200;
  Image_Center_Of_Mass(c,yx);
  Image_Center_Of_Mass(f,yx1);
	Image_Draw_Rect(a,yx[1],yx[0],30,30,100);	
	Image_Draw_Rect(d,yx1[1],yx1[0],30,30,100);
	Image_Save(d,"saved1.jpg");	
	Image_Save(a,"saved2.jpg");
	system("pause");
	
	Image_Free(a);
	Image_Free(b);
	Image_Free(c);
	Image_Free(d);
	Image_Free(f);
	system("pause");
	return 0;
	
}
