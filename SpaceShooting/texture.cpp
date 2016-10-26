#include<windows.h>
#include<GL/gl.h>


void set_texture(GLubyte texture_image[], GLuint *texture_id, int x_size, int y_size)
{
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4); 

	// �|�C���^�̈����ɒ���
	glGenTextures(1, texture_id);

	// �|�C���^�̈����ɒ���
	glBindTexture(GL_TEXTURE_2D, *texture_id); 

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 
		x_size, 
		y_size, 0, 
		GL_RGBA, GL_UNSIGNED_BYTE, 
		texture_image); 

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

	/* �A���t�@�e�X�g�̔�r�֐�*/
	glAlphaFunc(GL_GREATER, 0.7);//�A���t�@�l��0.7���傫����Ε`��


	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);

	glFrontFace(GL_CW);
}