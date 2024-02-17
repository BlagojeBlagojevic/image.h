#define IMAGE_IMPLEMENTATION
#include "image.h"
void Data_Encription(void){
	
	system("cls");
	printf("\n________________________________________________________\n\n");
  printf("Input Location of Image Used AS Key:\n>");
  char key[30];
  scanf("%s",key);
  Image iKey = Image_Alloc_Name(key);
  printf("Input File You Want To encrypt:\n>");
  char fileName[30];
  scanf("%s",fileName);
  Image iData = Image_Alloc(IMAGE_PARAMETARS(iKey));
  int sizeData = Load_Binary_To_Image(iData,fileName);
  printf("Input the Name of Image You Want to Encrypt to:\n>");
  char name[30];
  scanf("%s",name);
  Image_Sum(iData,iKey);
  stbi_write_png(name,iData.width/iData.chanels,iData.height,iData.chanels,iData.pixels,0);
	//Image_Save(iKey,name);
	Image_Free(iKey);
	Image_Free(iData);
	printf("SIZE_OF_DATA_IS : %d\n",sizeData);
	system("pause");
}

void Data_Decription(void){
	
	system("cls");
	printf("\n________________________________________________________\n\n");
  printf("Input Location of Image in Witch Data are Store:\n>");
  char key[30];
  scanf("%s",key);
  Image iData = Image_Alloc_Name(key);
  printf("Input Location of Image Used as Key:\n>");
  char fileName[30];
  scanf("%s",fileName);
  Image iKey = Image_Alloc_Name(fileName);
  printf("Input The Number of Bytes you Encripted:\n>");
  size_t nBytes;
  scanf("%lld",&nBytes);
  printf("Input the Name of File:\n>");
  char name[30];
  scanf("%s",name);
  Image_Dec(iData,iKey);
  //Image_Save(iData,"bin.jpg");
  Image_To_Binary(iData,nBytes,name);
  Image_Free(iData);
  Image_Free(iKey); 
	
}


int main(void){
	
	
	while(1){
	system("cls");
	printf("\t\tENCRYPT FILES IN IMAGE\n");
	printf("\n________________________________________________________\n\n");
	printf("Input What you Want to Do(1 - encrypt, 2 - decrypt, 0 - EXIT):\n>");
	int what;
	scanf("%d",&what);
	if(what == 1)
		Data_Encription();
	if(what == 2)
		Data_Decription();
  if(what == 0)
  	return 0;
  }
	return 0;
}
