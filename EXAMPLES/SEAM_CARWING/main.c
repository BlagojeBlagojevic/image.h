#define IMAGE_IMPLEMENTATION
#include "image.h"
#include <math.h>
#include <string.h>

Image Image_To_Lum(Image i ,Image a){
	
	
	for(size_t y = 0; y < i.height; y++){
		for(size_t x = 0, x_cou = 0; x < i.width; x+=3){
			float lum = 0.2126*PIXEL_AT(i, y, x) + 0.7152*PIXEL_AT(i, y, x + 1) + 0.0722*PIXEL_AT(i, y, x + 2);
			PIXEL_AT(a, y, x_cou++) = (uint8_t)lum;
	}
	
}
}





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

void Image_Copy_Stop(Image dest, Image source){
	//IMAGE_ASSERT(dest.width  >= source.width);
	//IMAGE_ASSERT(dest.height >= source.height);
	for(size_t y = 0; y < dest.height; y++) {
		for(size_t x = 0; x < dest.width; x++) {
			PIXEL_AT(dest,y,x) = PIXEL_AT(source,y,x);
			}
		}
	
	
}



int main() {
	Image i = Image_Alloc_Name("3.jpg");

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

	E_treshold = 255;
	//Image_Save(c, "saved.jpg");
	//return 0;	
	//Image_Black_White_Filtar(c, 0);
	//Image_Invert(c);
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
	
	//Image save = Image_Alloc(IMAGE_PARAMETARS(i));
	
	Image_Dec(c, a);
	size_t counter = 0;
	for(size_t y = 0; y < c.height;y++){
		counter = 0;
		for(size_t x = 0; x < c.width; x++){
			
			if(PIXEL_AT(c, y, x)){
				
				memcpy(&PIXEL_AT(i, y, x * 3),&PIXEL_AT(i, y, x * 3 + 3), i.width - (x * 3 + 3));
				//memcpy(&PIXEL_AT(i, y, x*3), &PIXEL_AT(i, y, x*3 + 3), 3);
				counter++;
				//PIXEL_AT(i ,y ,x) = 
			}
			
		}

	}
	printf("Counter %d\n", counter);
	
	Image i_save = Image_Alloc(i.width/3 - counter, i.height,i.chanels);
	//system("pause");
	Image_Copy(i_save, i);
	Image_Save(i, "saved.jpg");
	
	Image_Free(a);
	Image_Free(b);
	Image_Free(c);
	Image_Free(c_copy);
	Image_Free(i);
	Image_Free(i_save);
	
	
	printf("Nesto\n");
	return 0;
	}
