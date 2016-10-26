#include<windows.h>
#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>
#include<math.h>
#include<stdio.h>
#include "vector.h"

void draw_jiki(int r){//���@�̕`��	�����Ƃ���r���󂯎�藃����]������
	//�����̐ݒ�
	GLfloat specular[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat cube[] = {1.0, 1.0, 0.0, 1.0};//���F�̃��C���[�t���[��	
	GLfloat cubealfa[] = {1.0, 1.0, 0.0, 0.2};//�������̉��F�Ŗʂ�`��	
	GLfloat shininess[] = {50.0};

	//�e�ݒ��K�p
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cube);//�܂����C���[�t���[���̐F�Őݒ�
	int t=1;//���E�ɑΏ̂ɓ������̂��������ߐ؂�ւ��ׂ̈̕ϐ���錾

	////////////////////////////////////////////////////////////���C���[�t���[����������
	//����
	glPushMatrix();//�s��X�^�b�N���v�b�V��
	glTranslatef(0,0,0.5);
	glRotatef(80,1.0,0.0,0.0);
	glutWireCone(0.08,0.3,5,3);
	glPopMatrix();//�s��X�^�b�N���|�b�v
	//����
	glPushMatrix();//�s��X�^�b�N���v�b�V��
	glTranslatef(0,-0.3,0.55);
	glRotatef(90,1.0,0.0,0.0);
	glutWireCone(0.06,0.2,5,3);
	glPopMatrix();//�s��X�^�b�N���|�b�v
	//���S�̔���
	glPushMatrix();//�s��X�^�b�N���v�b�V��
	glTranslatef(0,0.43,0.25);
	glRotatef(60,1.0,0.0,0.0);
	glRotatef(r,0.0,0.0,1.0);
	glutWireCone(0.05,0.5,3,3);
	glPopMatrix();//�s��X�^�b�N���|�b�v
	//���E�̗���`��
	for(int i=0;i<2;i++){
		//������1�{��
		glPushMatrix();//�s��X�^�b�N���v�b�V��
		glTranslatef(-0.23*t,0.38,0.25);
		glRotatef(30*t,0.0,0.0,1.0);
		glRotatef(60,1.0,0.0,0.0);
		glRotatef(r,0.0,0.0,1.0);
		glutWireCone(0.05,0.5,3,3);
		glPopMatrix();//�s��X�^�b�N���|�b�v
		//������2�{��
		glPushMatrix();//�s��X�^�b�N���v�b�V��
		glTranslatef(-0.4*t,0.22,0.25);
		glRotatef(60*t,0.0,0.0,1.0);
		glRotatef(60,1.0,0.0,0.0);
		glRotatef(r,0.0,0.0,1.0);
		glutWireCone(0.05,0.5,3,3);
		glPopMatrix();//�s��X�^�b�N���|�b�v
		//���̍��{
		glPushMatrix();//�s��X�^�b�N���v�b�V��
		glBegin(GL_LINE_LOOP);
		glVertex3f(t*0.04, -0.2, 0.53);
		glVertex3f(t*0.12, -0.23, 0.58);
		glVertex3f(t*0.12, -0.17, 0.58);
		glEnd();
		glPopMatrix();//�s��X�^�b�N���|�b�v

		//2�i�ڑO���̗�
		glPushMatrix();//�s��X�^�b�N���v�b�V��
		glBegin(GL_LINE_LOOP);
		glVertex3f(t*0.12, -0.23, 0.58);
		glVertex3f(t*0.23, -0.3, 0.57);
		glVertex3f(t*0.24, -0.21, 0.6);
		glEnd();
		glPopMatrix();//�s��X�^�b�N���|�b�v
		//2�i�ڌ���̗�
		glPushMatrix();//�s��X�^�b�N���v�b�V��
		glBegin(GL_LINE_LOOP);
		glVertex3f(t*0.12, -0.17, 0.58);
		glVertex3f(t*0.24, -0.19, 0.6);
		glVertex3f(t*0.23, -0.11, 0.57);
		glEnd();
		glPopMatrix();//�s��X�^�b�N���|�b�v
		//3�i�ڌ���O���̗�
		glPushMatrix();//�s��X�^�b�N���v�b�V��
		glBegin(GL_LINE_LOOP);
		glVertex3f(t*0.24, -0.18, 0.6);
		glVertex3f(t*0.53, -0.19, 0.59);
		glVertex3f(t*0.5, -0.08, 0.57);
		glEnd();
		glPopMatrix();//�s��X�^�b�N���|�b�v
		//3�i�ڌ���㑤�̗�
		glPushMatrix();//�s��X�^�b�N���v�b�V��
		glBegin(GL_LINE_LOOP);
		glVertex3f(t*0.24, -0.12, 0.57);
		glVertex3f(t*0.5, -0.07, 0.57);
		glVertex3f(t*0.45, 0.04, 0.54);
		glEnd();
		glPopMatrix();//�s��X�^�b�N���|�b�v
		//3�i�ڑO���㑤�̗�
		glPushMatrix();//�s��X�^�b�N���v�b�V��
		glBegin(GL_LINE_LOOP);
		glVertex3f(t*0.24, -0.22, 0.6);
		glVertex3f(t*0.53, -0.21, 0.59);
		glVertex3f(t*0.5, -0.32, 0.6);
		glEnd();
		glPopMatrix();//�s��X�^�b�N���|�b�v
		//3�i�ڑO���O���̗�
		glPushMatrix();//�s��X�^�b�N���v�b�V��
		glBegin(GL_LINE_LOOP);
		glVertex3f(t*0.24, -0.29, 0.57);
		glVertex3f(t*0.5, -0.33, 0.6);
		glVertex3f(t*0.45, -0.44, 0.57);
		glEnd();
		glPopMatrix();//�s��X�^�b�N���|�b�v
		t*=-1;
	}
	/////////////////////////////////////////////////////////���C���[�t���[�������܂�
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cubealfa);//�������̎��@�F�ɕύX
	//////////////////////////////////////////////////////////�������̖ʂ�������
	//����
	glPushMatrix();//�s��X�^�b�N���v�b�V��
	glTranslatef(0,0,0.5);
	glRotatef(80,1.0,0.0,0.0);
	glutSolidCone(0.08,0.3,5,3);
	glPopMatrix();//�s��X�^�b�N���|�b�v
	//����
	glPushMatrix();//�s��X�^�b�N���v�b�V��
	glTranslatef(0,-0.3,0.55);
	glRotatef(90,1.0,0.0,0.0);
	glutSolidCone(0.06,0.2,5,3);
	glPopMatrix();//�s��X�^�b�N���|�b�v
	//�����̔���
	glPushMatrix();//�s��X�^�b�N���v�b�V��
	glTranslatef(0,0.43,0.25);
	glRotatef(60,1.0,0.0,0.0);
	glRotatef(r,0.0,0.0,1.0);
	glutSolidCone(0.05,0.5,3,3);
	glPopMatrix();//�s��X�^�b�N���|�b�v
	//���E�̗���`��
	for(int i=0;i<2;i++){
		//������1�{��
		glPushMatrix();//�s��X�^�b�N���v�b�V��
		glTranslatef(-0.23*t,0.38,0.25);
		glRotatef(30*t,0.0,0.0,1.0);
		glRotatef(60,1.0,0.0,0.0);
		glRotatef(r,0.0,0.0,1.0);
		glutSolidCone(0.05,0.5,3,3);
		glPopMatrix();//�s��X�^�b�N���|�b�v
		//������2�{��
		glPushMatrix();//�s��X�^�b�N���v�b�V��
		glTranslatef(-0.4*t,0.22,0.25);
		glRotatef(60*t,0.0,0.0,1.0);
		glRotatef(60,1.0,0.0,0.0);
		glRotatef(r,0.0,0.0,1.0);
		glutSolidCone(0.05,0.5,3,3);
		glPopMatrix();//�s��X�^�b�N���|�b�v
		////���̍��{
		glPushMatrix();//�s��X�^�b�N���v�b�V��
		glBegin(GL_TRIANGLES);
		glVertex3f(t*0.04, -0.2, 0.53);
		glVertex3f(t*0.12, -0.23, 0.58);
		glVertex3f(t*0.12, -0.17, 0.58);
		glEnd();
		glPopMatrix();//�s��X�^�b�N���|�b�v

		//2�i�ڑO���̗�
		glPushMatrix();//�s��X�^�b�N���v�b�V��
		glBegin(GL_TRIANGLES);
		glVertex3f(t*0.12, -0.23, 0.58);
		glVertex3f(t*0.23, -0.3, 0.57);
		glVertex3f(t*0.24, -0.21, 0.6);
		glEnd();
		glPopMatrix();//�s��X�^�b�N���|�b�v
		//2�i�ڌ���̗�
		glPushMatrix();//�s��X�^�b�N���v�b�V��
		glBegin(GL_TRIANGLES);
		glVertex3f(t*0.12, -0.17, 0.58);
		glVertex3f(t*0.24, -0.19, 0.6);
		glVertex3f(t*0.23, -0.11, 0.57);
		glEnd();
		glPopMatrix();//�s��X�^�b�N���|�b�v
		//3�i�ڌ���O���̗�
		glPushMatrix();//�s��X�^�b�N���v�b�V��
		glBegin(GL_TRIANGLES);
		glVertex3f(t*0.24, -0.18, 0.6);
		glVertex3f(t*0.53, -0.19, 0.59);
		glVertex3f(t*0.5, -0.08, 0.57);
		glEnd();
		glPopMatrix();//�s��X�^�b�N���|�b�v
		//3�i�ڌ���㑤�̗�
		glPushMatrix();//�s��X�^�b�N���v�b�V��
		glBegin(GL_TRIANGLES);
		glVertex3f(t*0.24, -0.12, 0.57);
		glVertex3f(t*0.5, -0.07, 0.57);
		glVertex3f(t*0.45, 0.04, 0.54);
		glEnd();
		glPopMatrix();//�s��X�^�b�N���|�b�v
		//3�i�ڑO���㑤�̗�
		glPushMatrix();//�s��X�^�b�N���v�b�V��
		glBegin(GL_TRIANGLES);
		glVertex3f(t*0.24, -0.22, 0.6);
		glVertex3f(t*0.53, -0.21, 0.59);
		glVertex3f(t*0.5, -0.32, 0.6);
		glEnd();
		glPopMatrix();//�s��X�^�b�N���|�b�v
		//3�i�ڑO���O���̗�
		glPushMatrix();//�s��X�^�b�N���v�b�V��
		glBegin(GL_TRIANGLES);
		glVertex3f(t*0.24, -0.29, 0.57);
		glVertex3f(t*0.5, -0.33, 0.6);
		glVertex3f(t*0.45, -0.44, 0.57);
		glEnd();
		glPopMatrix();//�s��X�^�b�N���|�b�v
		t*=-1;
	}
	/////////////////////////////////////////////////////////�������̖ʂ����܂�
}

void draw_missile(int r,bool e){//�~�T�C���̕`��	�����Ƃ��āA�����ɉ�]���邽�߂̕ϐ��ƓG�̃~�T�C�����ǂ�����n��bool�^��p��
	//�����̐ݒ�
	GLfloat specular[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat enemy[] = {1.0, 0.0, 0.0, 1.0};//�G�̐F�͐�
	GLfloat enemyalfa[] = {1.0, 0.0, 0.0, 0.2};
	GLfloat missile[] = {1.0, 1.0, 1.0, 1.0};//�����̃~�T�C���͔��F
	GLfloat missilealfa[] = {1.0, 1.0, 1.0, 0.2};
	GLfloat shininess[] = {50.0};

	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
	if(e)glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, enemy);//�~�T�C�����G�̂��̂Ȃ�Ԃ�ݒ�
	else glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, missile);//�����łȂ��Ȃ甒��ݒ�
	//���C���[�t���[���ł̕`��
	glPushMatrix();//�s��X�^�b�N���v�b�V��
	glRotatef(r*5,0,0.0,1.0);//�~�T�C���͑S�̂���]����

	glPushMatrix();//�s��X�^�b�N���v�b�V��
	glTranslatef(0,0,0.5);
	glutWireCone(0.1,0.5,3,5);//�O�p���Ń~�T�C����\������
	glRotatef(180,0,1.0,0.0);
	glutWireCone(0.03,0.5,3,5);
	for(int i=0;i<3;i++){
		glPushMatrix();//�s��X�^�b�N���v�b�V��
		glRotatef(120*i,0,0.0,1.0);
		glTranslatef(0,0.07,0.0);
		glutWireCone(0.02,0.3,3,5);
		glPopMatrix();//�s��X�^�b�N���|�b�v
	}
	glPopMatrix();//�s��X�^�b�N���|�b�v

	/////////////////////////////////�������Ȗʂ̕`��
	if(e)glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, enemyalfa);
	else glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, missilealfa);

	glPushMatrix();//�s��X�^�b�N���v�b�V��
	glTranslatef(0,0,0.5);
	glutSolidCone(0.1,0.5,3,5);
	glRotatef(180,0,1.0,0.0);
	glutSolidCone(0.03,0.5,3,5);
	for(int i=0;i<3;i++){
		glPushMatrix();//�s��X�^�b�N���v�b�V��
		glRotatef(120*i,0,0.0,1.0);
		glTranslatef(0,0.07,0.0);
		glutSolidCone(0.02,0.3,3,5);
		glPopMatrix();//�s��X�^�b�N���|�b�v
	}
	glPopMatrix();//�s��X�^�b�N���|�b�v
	glPopMatrix();//�s��X�^�b�N���|�b�v
}

void draw_map(Vector jiki,Vector missile[],Vector enemy[],Vector enemy_missile[],int targetnum,int enemy_num)//�}�b�v�Ɉʒu��`�悷�邽�߂ɁA���@��~�T�C���A�G�̈ʒu�␔��n��
{


	GLfloat pointer_jiki[] = {1.0, 1.0, 0.0, 1.0};
	GLfloat pointer_missile[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat pointer_enemy[] = {1.0, 0.0, 0.0, 1.0};

	//�}�b�v�̃e�N�X�`����K�p������Ԃł��̏������Ăяo�����

	glBegin(GL_QUADS);
	glTexCoord2f(0,0); 
	glVertex3f(-1.4, 0.8,0.0);
	glTexCoord2f(1,0);
	glVertex3f(-0.8, 0.8,0.0);
	glTexCoord2f(1,1);
	glVertex3f(-0.8, 0.2,0.0);
	glTexCoord2f(0,1);
	glVertex3f(-1.4, 0.2,0.0);
	glEnd();

	glDisable(GL_TEXTURE_2D);//�e�N�X�`���̐ݒ������

	///////////////////�|�C���^�[�̕`��
	//���@�̃|�C���^�[��`��
	glColor4fv(pointer_jiki);
	glPushMatrix();//�s��X�^�b�N���v�b�V��
	glTranslatef(-1.1+jiki.x/50*0.3,0.5+jiki.y/50*0.3,0);
	glRotatef(-jiki.theta*180/pi,0,0.0,1.0);
	glBegin(GL_TRIANGLES);
	glVertex3f(-0.01, -0.01,0.0);
	glVertex3f(0.01, -0.01,0.0);
	glVertex3f(0.0,0.02,0.0);
	glEnd();
	glPopMatrix();//�s��X�^�b�N���|�b�v

	//���@�̃~�T�C���̃|�C���^
	glColor4fv(pointer_missile);
	for(int i=0;i<10;i++){
		if(missile[i].exist){
			glPushMatrix();//�s��X�^�b�N���v�b�V��
			glTranslatef(-1.1+missile[i].x/50*0.3,0.5+missile[i].y/50*0.3,0);
			glRotatef(-missile[i].theta*180/pi,0,0,1);
			glBegin(GL_TRIANGLES);
			glVertex3f(-0.005, -0.005,0.0);
			glVertex3f(0.005, -0.005,0.0);
			glVertex3f(0.0,0.01,0.0);

			glEnd();
			glPopMatrix();//�s��X�^�b�N���|�b�v
		}
	}
	//�G�̃~�T�C���̃|�C���^
	glColor4fv(pointer_enemy);
	for(int i=0;i<enemy_num*10;i++){

		//	for(int j=0;j<1;j++){
		if(enemy_missile[i].exist){
			glPushMatrix();//�s��X�^�b�N���v�b�V��
			glTranslatef(-1.1+enemy_missile[i].x/50*0.3,0.5+enemy_missile[i].y/50*0.3,0);
			glRotatef(-enemy_missile[i].theta*180/pi,0,0.0,1);
			glBegin(GL_TRIANGLES);

			glVertex3f(-0.005, -0.005,0.0);
			glVertex3f(0.005, -0.005,0.0);
			glVertex3f(0.0,0.01,0.0);

			glEnd();
			glPopMatrix();//�s��X�^�b�N���|�b�v
		}
		//		}
	}

	//�G�̃|�C���^
	for(int i=0;i<enemy_num;i++){
		if(enemy[i].exist){
			glPushMatrix();//�s��X�^�b�N���v�b�V��
			glTranslatef(-1.1+enemy[i].x/50*0.3,0.5+enemy[i].y/50*0.3,0);
			int n=10;
			int j=0;
			for(j=0;j<n;j++){
				glPushMatrix();//�s��X�^�b�N���v�b�V��

				glBegin(GL_TRIANGLES);
				glVertex3f(0.01*cos(2*pi*j/n),0.01*sin(2*pi*j/n),0.0);
				glVertex3f(0.01*cos(2*pi*(j+1)/n),0.01*sin(2*pi*(j+1)/n),0.0);
				glVertex3f(0.0,0.0,0.0);
				glEnd();
				glPopMatrix();//�s��X�^�b�N���|�b�v
			}
			//�^�[�Q�b�g����Ă���G�͓��ʂɈ������
			if(i==targetnum){
				glBegin(GL_LINE_LOOP);
				for(j=0;j<n;j++){
					glVertex3f(0.015*cos(2*pi*j/n),0.015*sin(2*pi*j/n),0.0);
					glVertex3f(0.015*cos(2*pi*(j+1)/n),0.015*sin(2*pi*(j+1)/n),0.0);
				}
				glEnd();
			}

			glPopMatrix();//�s��X�^�b�N���|�b�v
		}
	}
}

void draw_explosion(GLint r){//�����G�t�F�N�g�̕`��B�A�j���[�V�����p�ɑ���������lr��n��
	//�����̃A�j���[�V�������܂񂾈ꖇ�̃e�N�X�`����r�̒l�ɂ���ē\��t����ꏊ��؂�ւ���
	glBegin(GL_QUADS);
	glTexCoord2f((double)((r-1)%5)/5,(double)((int)((r-1)/5))/5); 
	glVertex3f(-1.5, 0.0,1.8);
	glTexCoord2f((double)((r-1)%5+1)/5,(double)((int)((r-1)/5))/5);
	glVertex3f(1.5, 0.0,1.8);
	glTexCoord2f((double)((r-1)%5+1)/5,(double)((int)((r-1)/5)+1)/5);
	glVertex3f(1.5, 0.0,-1.2);
	glTexCoord2f((double)((r-1)%5)/5,(double)((int)((r-1)/5)+1)/5);
	glVertex3f(-1.5,0.0,-1.2);
	glEnd();
	//�������̂��\���ɓ\���ė��̓I�Ɍ�����悤�ɂ���
	glBegin(GL_QUADS);
	glTexCoord2f((double)((r-1)%5)/5,(double)((int)((r-1)/5))/5); 
	glVertex3f(0,-1.5,1.8);
	glTexCoord2f((double)((r-1)%5+1)/5,(double)((int)((r-1)/5))/5);
	glVertex3f(0,1.5,1.8);
	glTexCoord2f((double)((r-1)%5+1)/5,(double)((int)((r-1)/5)+1)/5);
	glVertex3f(0,1.5,-1.2);
	glTexCoord2f((double)((r-1)%5)/5,(double)((int)((r-1)/5)+1)/5);
	glVertex3f(0,-1.5,-1.2);
	glEnd();
}

void draw_yuka(void){//���̕`��
	glColor4f(0.8,0.8,1,0.2);//�e�N�X�`���ł͂Ȃ��������̐��ŕ`��
	//���b�V����`��
	for(int i=-50;i<50;i++){
		glBegin(GL_LINES);
		glVertex3f(-50, i, 0.0);
		glVertex3f(50, i, 0.0);
		glEnd();
		glBegin(GL_LINES);
		glVertex3f(i, -50, 0.0);
		glVertex3f(i, 50, 0.0);
		glEnd();

	}

}

void draw_enemy(int r)//�G�̕`��B�����������]���镔�ʂ��񂷂��߂̑���������lr��n��
{
	GLfloat specular[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat enemy[] = {1.0, 0.0, 0.0, 1.0};	
	GLfloat enemyalfa[] = {1.0, 0.0, 0.0, 0.2};	
	GLfloat shininess[] = {50.0};

	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, enemy);
	//�G�@�̃��C���[�t���[����`��
	glPushMatrix();//�s��X�^�b�N���v�b�V��
	glRotatef(-r*5,0.0,0.0,1.0);

	glPushMatrix();//�s��X�^�b�N���v�b�V��
	glTranslatef(0,0,0.3);
	glRotatef(180,1.0,0.0,0.0);
	glutWireCone(0.12,0.3,7,3);
	glPopMatrix();//�s��X�^�b�N���|�b�v

	glPushMatrix();//�s��X�^�b�N���v�b�V��
	glTranslatef(0,0,0.7);
	glutWireCone(0.12,0.3,7,3);
	glPopMatrix();//�s��X�^�b�N���|�b�v

	glPushMatrix();//�s��X�^�b�N���v�b�V��
	glTranslatef(0,0,0.5);
	glutWireSphere(0.15,7,7);//�G�̊j����
	glPopMatrix();//�s��X�^�b�N���|�b�v
	glPopMatrix();//�s��X�^�b�N���|�b�v

	int t=1;
	for(int i=0;i<7;i++)//�@�̂̎������]����j�̕`��
	{
		glPushMatrix();//�s��X�^�b�N���v�b�V��
		glRotatef((double)i/7*360,0.0,0.0,1.0);

		for(int j=0;j<2;j++){
			glPushMatrix();//�s��X�^�b�N���v�b�V��
			glRotatef(r*5*t,0.0,0.0,1.0);
			glTranslatef(0,0,0.5);
			glRotatef(90,1.0,0.0,0.0);

			glRotatef(20*t,1.0,0.0,0.0);
			glTranslatef(0,0,0.3);
			glutWireCone(0.05,0.4,7,3);
			glPopMatrix();//�s��X�^�b�N���|�b�v

			t*=-1;
		}
		glPopMatrix();//�s��X�^�b�N���|�b�v
	}
	///////////////////////////////////////////
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, enemyalfa);
	//�������Ŗʂ�`��
	///////////////////////////////////////////////////////
	glPushMatrix();//�s��X�^�b�N���v�b�V��
	glRotatef(-r*5,0.0,0.0,1.0);

	glPushMatrix();//�s��X�^�b�N���v�b�V��
	glTranslatef(0,0,0.3);
	glRotatef(180,1.0,0.0,0.0);
	glutSolidCone(0.12,0.3,7,3);
	glPopMatrix();//�s��X�^�b�N���|�b�v

	glPushMatrix();//�s��X�^�b�N���v�b�V��
	glTranslatef(0,0,0.7);
	glutSolidCone(0.12,0.3,7,3);
	glPopMatrix();//�s��X�^�b�N���|�b�v

	glPushMatrix();//�s��X�^�b�N���v�b�V��
	glTranslatef(0,0,0.5);
	glutSolidSphere(0.15,7,7);
	glPopMatrix();//�s��X�^�b�N���|�b�v

	glPopMatrix();//�s��X�^�b�N���|�b�v
	for(int i=0;i<7;i++)
	{
		glPushMatrix();//�s��X�^�b�N���v�b�V��
		glRotatef((double)i/7*360,0.0,0.0,1.0);

		for(int j=0;j<2;j++){
			glPushMatrix();//�s��X�^�b�N���v�b�V��
			glRotatef(r*5*t,0.0,0.0,1.0);
			glTranslatef(0,0,0.5);
			glRotatef(90,1.0,0.0,0.0);

			glRotatef(20*t,1.0,0.0,0.0);
			glTranslatef(0,0,0.3);
			glutSolidCone(0.05,0.4,7,3);
			glPopMatrix();//�s��X�^�b�N���|�b�v

			t*=-1;
		}
		glPopMatrix();//�s��X�^�b�N���|�b�v
	}

}

void draw_sphere(GLfloat dist)//�V�̂�F���̕`����܂Ƃ߂Đ����������\�b�h�B���̂̔��a�������Ƃ��ēn��
{
	int N=100;//����100�����ŕ`��
	GLfloat PI = 3.14159265358979323846264338327950;//�~����

	for(int i=0; i<N; i++){
		for(int j=0;j<(N/2);j++){

			glBegin(GL_QUADS);
			glTexCoord2f((double)i/N,(double)j/(N/2)); 
			glVertex3f(dist*cos(2*PI*i/N)*sin(2*PI*j/N),dist*sin(2*PI*i/N)*sin(2*PI*j/N),dist*cos(2*PI*j/N));
			glTexCoord2f(((double)(i+1)/N),(double)j/(N/2)); 
			glVertex3f(dist*cos(2*PI*(double)((i+1)%N)/N)*sin(2*PI*j/N),dist*sin(2*PI*(double)((i+1)%N)/N)*sin(2*PI*j/N),dist*cos(2*PI*j/N));
			glTexCoord2f(((double)(i+1)/N),((double)(j+1)/(N/2))); 
			glVertex3f(dist*cos(2*PI*(double)((i+1)%N)/N)*sin(2*PI*(j+1)/N),dist*sin(2*PI*(double)((i+1)%N)/N)*sin(2*PI*(j+1)/N),dist*cos(2*PI*(j+1)/N));
			glTexCoord2f((double)i/N,((double)(j+1)/(N/2))); 
			glVertex3f(dist*cos(2*PI*i/N)*sin(2*PI*(j+1)/N),dist*sin(2*PI*i/N)*sin(2*PI*(j+1)/N),dist*cos(2*PI*(j+1)/N));

			glEnd(); 
		}
	} 

}

void draw_sight(void)//���b�N�I�����ɉ�ʒ����ɕ`���Ə�
{

	glBegin(GL_QUADS);
	glTexCoord2f(0,0); 
	glVertex3f(-0.3, 0.4,0.0);
	glTexCoord2f(1,0);
	glVertex3f(0.3, 0.4,0.0);
	glTexCoord2f(1,1);
	glVertex3f(0.3, -0.2,0.0);
	glTexCoord2f(0,1);
	glVertex3f(-0.3, -0.2,0.0);
	glEnd();
}

void draw_logo(void)//�^�C�g����ʂł̃��S�̕`��
{
	glTranslatef(0,0,-2.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0,0); 
	glVertex3f(-1, 0.75,0.0);
	glTexCoord2f(1,0);
	glVertex3f(1, 0.75,0.0);
	glTexCoord2f(1,1);
	glVertex3f(1, -0.25,0.0);
	glTexCoord2f(0,1);
	glVertex3f(-1, -0.25,0.0);
	glEnd();
}

void draw_alert(void)//�~�T�C�����߂Â��Ă�����A�G���A�̒[�ɋ߂Â����Ƃ��ɔ�������A���[�g�̕`��
{
	glBegin(GL_QUADS);
	glTexCoord2f(0,0); 
	glVertex3f(-0.2, 0.6,0.0);
	glTexCoord2f(1,0);
	glVertex3f(0.2, 0.6,0.0);
	glTexCoord2f(1,1);
	glVertex3f(0.2, 0.4,0.0);
	glTexCoord2f(0,1);
	glVertex3f(-0.2, 0.4,0.0);
	glEnd();
}

void draw_number(int n,double d,int keta)//�����̕`��
	//�e�N�X�`���̒���0����9�܂ł̉摜���ϓ��ɕ���ł���A���������Ƃ��Ďg��
	//�����Ƃ��āA�\�����鐔���E�����̑傫���E������n���Ă���
{
	int num[3];//����3�P�^�܂őΉ�
	num[0]=n%10;//1����
	num[1]=(int)((double)n/10)%10;//2����
	num[2]=(int)((double)n/100)%10;//3����
	for(int i=0;i<keta;i++){

		glBegin(GL_QUADS);
		glTexCoord2f((double)num[i]/10,0); 
		glVertex3f((0.05-(double)i/10)*d, 0.15*d,0.0);
		glTexCoord2f((double)(num[i]+1)/10,0);
		glVertex3f((0.15-(double)i/10)*d, 0.15*d,0.0);
		glTexCoord2f((double)(num[i]+1)/10,1);
		glVertex3f((0.15-(double)i/10)*d, -0.15*d,0.0);
		glTexCoord2f((double)num[i]/10,1);
		glVertex3f((0.05-(double)i/10)*d, -0.15*d,0.0);
		glEnd();
	}

}

void draw_game_clear(void)//�Q�[���I�[�o�[����Q�[���N���A���ɌĂяo����郁�\�b�h
{
	glBegin(GL_QUADS);
	glTexCoord2f(0,0); 
	glVertex3f(-0.4, 0.15,0.0);
	glTexCoord2f(1,0);
	glVertex3f(0.4, 0.15,0.0);
	glTexCoord2f(1,1);
	glVertex3f(0.4, -0.15,0.0);
	glTexCoord2f(0,1);
	glVertex3f(-0.4, -0.15,0.0);
	glEnd();
}

void draw_percent(void)//���@��HP�\���Ŏg�����\��
{
	glBegin(GL_QUADS);
	glTexCoord2f(0,0); 
	glVertex3f(-0.06, 0.06,0.0);
	glTexCoord2f(1,0);
	glVertex3f(0.06, 0.06,0.0);
	glTexCoord2f(1,1);
	glVertex3f(0.06, -0.06,0.0);
	glTexCoord2f(0,1);
	glVertex3f(-0.06, -0.06,0.0);
	glEnd();
}
