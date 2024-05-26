#define IMAGE_IMPLEMENTATION
#include "image.h"
#include <math.h>
#include <string.h>



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



int main() {
	Image i = Image_Alloc_Name("12.jpg");
	Image i_copy = Image_Alloc(IMAGE_PARAMETARS(i));
	Image_Copy(i_copy, i);
	//Image a = Image_Alloc(IMAGE_PARAMETARS(i));
	//Image b = Image_Alloc(IMAGE_PARAMETARS(i));
	//Image c = Image_Alloc(IMAGE_PARAMETARS(i));
	Image a, b, c;
	Image_Alloc_Grey(i, &a);
	Image_Alloc_Grey(i, &b);
	Image_Alloc_Grey(i, &c);
	Image_Applay_Kernel(b, c, KERNEL_SOBEL_X, 3, 3);
	Image_Applay_Kernel(a, c, KERNEL_SOBEL_Y, 3, 3);
	float E_treshold = 0;
	for(size_t y = 0; y < a.height; y++) {
		for(size_t x = 0; x < a.width; x++) {
		//	PIXEL_AT(c, y, x) = (uint8_t)sqrt(PIXEL_AT(a,y,x) * PIXEL_AT(a,y,x)
			//                                  + PIXEL_AT(b,y,x) * PIXEL_AT(b,y,x));
			PIXEL_AT(c, y, x) = atan2(PIXEL_AT(a, y, x),PIXEL_AT(b, y, x));
				E_treshold+= PIXEL_AT(c, y, x);
			}
		}
		E_treshold/= (a.width * a.height);
		//E_treshold = 230;
	//Image_Save(c, "saved.jpg");
	//return 0;	
	//Image_Black_White_Filtar(c, 0);
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
			E_total += E[min_inde];
			
			index+=min_inde;
			PIXEL_AT(c, y, index) = 120;
		}
		//CHECK IS E < THEN TRESHOLD
		E_total/= c.height;
		if(E_total < E_treshold){
			Image_Copy(c_copy, c);
		}
		else{
			Image_Copy(c, c_copy);
		}
		
		
	}
	
	Image save = Image_Alloc(IMAGE_PARAMETARS(i));
	
	Image_Dec(c, a);
	for(size_t y = 0; y < c.height;y++){
		for(size_t x = 0; x < c.width; x++){
			if(PIXEL_AT(c, y, x)){
				
				memcpy(&PIXEL_AT(i, y, x * 3),&PIXEL_AT(i, y, x * 3 + 3), i.width - (x * 3 + 3));
				//c
				//PIXEL_AT(i ,y ,x) = 
			}
			
		}
	}

  //Image_Dec(i, i_copy);
	Image_Save(c_copy, "carve.jpg");
	Image_Save(i, "saved.jpg");
	
	printf("Nesto\n");
	return 0;
	}