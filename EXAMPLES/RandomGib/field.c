#define IMAGE_IMPLEMENTATION
#define DYNAMIC
#define ARRAY_TYPE float
#include "image.h"




int main(void){
    Image a = Image_Alloc_Name("1.png");
    Image b = Image_Alloc_Name("2.png");
    Image_Applay_Kernel(a,a,KERNEL_SOBEL_Y,3,3);
    Image_Applay_Kernel(b,b,KERNEL_SOBEL_Y,3,3);
    Image32 distances = Image_Field(a, b, 50);
    Image32_Save(distances,"saved.png");
    //Image_Print(distances);
     
        
    //print_Array(&distances);


    return 0;
}
