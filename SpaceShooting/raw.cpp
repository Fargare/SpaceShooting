#include<windows.h> 
#include<GL/gl.h>
#include<stdio.h>
#include<stdlib.h>

/*  rawフォーマットのRGBA画像を読み込みます */
void raw(char file_name[], GLubyte image[],int x_size, int y_size)
{
	FILE *fp;

	if((fp = fopen(file_name , "rb")) != NULL){
		fread(image,x_size*y_size*4,1,fp);
		fclose(fp);
	}

	else{
		printf("Cannot open RAW file\n");//エラー表示
		exit(0);//終了
	}
}