#include<windows.h> 
#include<GL/gl.h>
#include<stdio.h>
#include<stdlib.h>

/*  raw�t�H�[�}�b�g��RGBA�摜��ǂݍ��݂܂� */
void raw(char file_name[], GLubyte image[],int x_size, int y_size)
{
	FILE *fp;

	if((fp = fopen(file_name , "rb")) != NULL){
		fread(image,x_size*y_size*4,1,fp);
		fclose(fp);
	}

	else{
		printf("Cannot open RAW file\n");//�G���[�\��
		exit(0);//�I��
	}
}