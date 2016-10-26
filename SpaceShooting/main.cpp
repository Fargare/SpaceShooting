#include<windows.h>
#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>
#include<math.h>
#include<stdio.h>
#include <stdlib.h>

#include "init.h"
#include "draw.h"
#include "vector.h"
#include "raw.h"
#include "texture.h"

#define PI 3.141592

void display(void);
void key_down(unsigned char key, int x, int y);
void key_up(unsigned char key, int x, int y);
void special_down(int key, int x, int y);
void special_up(int key, int x, int y);
void missile_move();
void enemy_missile_move();
void target_move(void);
void hit_effect(void);
void idle();
void key_move();
void target_change(void);

GLubyte *texture_sky;//��̃e�N�X�`��
GLuint texture_id1;

GLubyte *texture_map;//�}�b�v�̃e�N�X�`��
GLuint texture_id2;

GLubyte *texture_sight;//�Ə��̃e�N�X�`��
GLuint texture_id3;

GLubyte *texture_bomb;//�����G�t�F�N�g�̃e�N�X�`��
GLuint texture_id4;

GLubyte *texture_logo;//�^�C�g�����S�̃e�N�X�`��
GLuint texture_id5;

GLubyte *texture_planet1;//�V�̂̃e�N�X�`��
GLuint texture_id6;

GLubyte *texture_planet2;//�����ЂƂ̓V�̂̃e�N�X�`��
GLuint texture_id7;

GLubyte *texture_alert1;//�~�T�C���A���[�g�̃e�N�X�`��
GLuint texture_id8;

GLubyte *texture_alert2;//�G���A�O�A���[�g�̃e�N�X�`��
GLuint texture_id9;

GLubyte *texture_num_yellow;//���F�������̃e�N�X�`��
GLuint texture_id10;

GLubyte *texture_num_red;//�Ԃ������̃e�N�X�`��
GLuint texture_id11;

GLubyte *texture_game_clear;//�N���A��ʂ̃e�N�X�`��
GLuint texture_id12;

GLubyte *texture_percent;//�p�[�Z���g�̃e�N�X�`��
GLuint texture_id13;

GLubyte *texture_game_over;//�Q�[���I�[�o�[��ʂ̃e�N�X�`��
GLuint texture_id14;

GLfloat height = 1.0;//�J�����̍���
GLfloat speed=0.25;//���@�֘A�̃X�s�[�h
int autorotate=0;//�I�u�W�F�N�g�̉�]��U���^�C�~���O���v��̂Ɏg���A���������鐔
GLfloat jikiLR=0;//���b�N�I�����̃J���������E�ɓ������o�̂��߂̕ϐ�

bool lockon=true;//���b�N�I��
bool fire=false;//���@�̍U���t���O
bool enemy_fire[10];//�G�@�̍U���t���O
bool next=true;//���b�N�I�������ɐ؂�ւ���t���O
bool prev=true;//���b�N�I����O�ɐ؂�ւ���t���O
bool game_clear=false;//�Q�[���N���A�̔���t���O
bool game_over=false;//�Q�[���I�[�o�[�̔���t���O

//�L�[�{�[�h����̐؂�ւ��t���O
bool forward=false;
bool backward=false;
bool left=false;
bool right=false;
bool seeleft=false;
bool seeright=false;

//�^�C�g����ʂƃQ�[����ʂ̐؂�ւ��t���O
int scene=0;

Vector enemy[5];//�G�@��5�Ƃ���
int enemy_num=5;
Vector jiki;
GLfloat vx[5];//�G�@�̈ړ������̏�����
GLfloat vy[5];

GLfloat fai=0;

Vector missile[10];//���@�̃~�T�C��
Vector enemy_missile[50];//�G�@�̃~�T�C��
Vector explosion[11];//�����G�t�F�N�g

int targetnum=1;//�^�[�Q�b�g�ԍ��̏����l

void main(int argc, char** argv)//���C����
{
	//�E�C���h�E�̕`��
	glutInit(&argc, argv);//glut�̏�����
	//Z�o�b�t�@���s���ꍇ�̃E�C���h�E���[�h��ݒ�
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(1900, 1000);//�E�C���h�E�T�C�Y
	glutCreateWindow("sample1.c");//�E�C���h�E�l�[��

	gl_init();//OpenGL�̏����ݒ�
	lighting_init();//���������̏����ݒ�

	//�e�N�X�`���̏�����

	texture_sky = (GLubyte *)malloc(sizeof(GLubyte) * 2048 * 2048 * 4);
	raw("starfield2.raw", texture_sky, 2048, 2048);
	set_texture(texture_sky, &texture_id1, 2048, 2048);

	texture_map = (GLubyte *)malloc(sizeof(GLubyte) * 512 * 512 * 4);
	raw("map.raw", texture_map, 512, 512);
	set_texture(texture_map, &texture_id2, 512, 512);

	texture_sight = (GLubyte *)malloc(sizeof(GLubyte) * 512 * 512 * 4);
	raw("sight.raw", texture_sight, 512, 512);
	set_texture(texture_sight, &texture_id3, 512, 512);

	texture_bomb = (GLubyte *)malloc(sizeof(GLubyte) * 1024 * 1024 * 4);
	raw("bomb.raw", texture_bomb, 1024, 1024);
	set_texture(texture_bomb, &texture_id4, 1024, 1024);

	texture_logo = (GLubyte *)malloc(sizeof(GLubyte) * 1024 * 512 * 4);
	raw("logo.raw", texture_logo, 1024, 512);
	set_texture(texture_logo, &texture_id5, 1024, 512);

	texture_planet1 = (GLubyte *)malloc(sizeof(GLubyte) * 512 * 512 * 4);
	raw("planet1.raw", texture_planet1, 512, 512);
	set_texture(texture_planet1, &texture_id6, 512, 512);

	texture_planet2 = (GLubyte *)malloc(sizeof(GLubyte) * 512 * 512 * 4);
	raw("jupiter.raw", texture_planet2, 512, 512);
	set_texture(texture_planet2, &texture_id7, 512, 512);

	texture_alert1 = (GLubyte *)malloc(sizeof(GLubyte) * 256 * 128 * 4);
	raw("missile_alert.raw", texture_alert1, 256,128);
	set_texture(texture_alert1, &texture_id8, 256, 128);

	texture_alert2 = (GLubyte *)malloc(sizeof(GLubyte) * 256 * 128 * 4);
	raw("area_alert.raw", texture_alert2, 256,128);
	set_texture(texture_alert2, &texture_id9, 256, 128);

	texture_num_yellow = (GLubyte *)malloc(sizeof(GLubyte) * 1024 * 256 * 4);
	raw("number_yellow.raw", texture_num_yellow, 1024,256);
	set_texture(texture_num_yellow, &texture_id10, 1024, 256);

	texture_num_red = (GLubyte *)malloc(sizeof(GLubyte) * 1024 * 256 * 4);
	raw("number_red.raw", texture_num_red, 1024,256);
	set_texture(texture_num_red, &texture_id11, 1024, 256);

	texture_game_clear = (GLubyte *)malloc(sizeof(GLubyte) * 512 * 128 * 4);
	raw("game_clear.raw", texture_game_clear, 512,128);
	set_texture(texture_game_clear, &texture_id12, 512, 128);

	texture_percent = (GLubyte *)malloc(sizeof(GLubyte) * 128 * 128 * 4);
	raw("percent.raw", texture_percent, 128,128);
	set_texture(texture_percent, &texture_id13, 128, 128);

	texture_game_over = (GLubyte *)malloc(sizeof(GLubyte) * 512 * 128 * 4);
	raw("game_over.raw", texture_game_over, 512,128);
	set_texture(texture_game_over, &texture_id14, 512, 128);


	//���@�̏�����
	jiki.counter=10;
	jiki.y=-20;
	//�~�T�C���┚���G�t�F�N�g�̏�����
	for(int i=0;i<10;i++){
		enemy_missile[i].exist=false;
		enemy_missile[i+10].exist=false;
		missile[i].exist=false;
		explosion[i].exist=false;
	}
	explosion[10].exist=false;
	//�G�̏�����
	srand(50);//�G�̈ړ������̓����_���Ɍ��肷��
	for(int i=0;i<enemy_num;i++){
		enemy[i].counter=7;
		enemy[i].theta=rand()/25;
		vx[i]=speed*sin(enemy[i].theta);
		vy[i]=speed*cos(enemy[i].theta);
		enemy[i].exist=true;
		enemy_fire[i]=false;
	}

	glutIdleFunc(idle);
	glutKeyboardFunc(key_down);//�L�[�{�[�h�C�x���g��o�^
	glutKeyboardUpFunc(key_up);//�L�[�{�[�h�C�x���g��o�^
	glutDisplayFunc(display);//�C�x���g�Ƃ���display��`��p�֐��Ƃ��ēo�^
	glutSpecialFunc(special_down);//�L�[�{�[�h�C�x���g��o�^
	glutSpecialUpFunc(special_up);//�L�[�{�[�h�C�x���g��o�^
	glutMainLoop();//�C�x���g�҂����[�v�ɓ���
}

void idle()
{
	if(jiki.counter==0)game_over=true;//�Q�[���I�[�o�[��Ԃ��ǂ����m�F
	autorotate+=1;//�����I�ɑ��������鐔��
	if(scene==1){//�Q�[����ʂł̏���
		target_move();
		missile_move();
		enemy_missile_move();
		hit_effect();
	}
	if(!game_over)key_move();//�Q�[���I�[�o�[�ɂȂ�����L�[����͌����Ȃ�
	target_change();

	glutPostRedisplay();
}


void display(void)//���
{
	//Z�o�b�t�@�𓱓������AOpenGL�̏�����
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

	glMatrixMode(GL_MODELVIEW);//���f���r���[�s��
	glLoadIdentity();//���e�ϊ���P�ʍs��ŏ�����
	glColor3f(1,1,1);

	glEnable(GL_BLEND);//����������K�p
	glBlendFunc(GL_ONE, GL_ZERO);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	gluPerspective(45.0, 1.9, 0.5,200.0);


	if(scene==0){//�^�C�g�����
		glDepthMask(GL_FALSE);
		glClear(GL_COLOR_BUFFER_BIT);

		glEnable(GL_TEXTURE_2D);//�e�N�X�`���ݒ��K�p

		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

		glPushMatrix();//�s��X�^�b�N���v�b�V��
		//////////////////////////�V��
		glDisable(GL_BLEND);//�����������͂���
		glBindTexture(GL_TEXTURE_2D, texture_id1); //��̃e�N�X�`���̐ݒ��K�p
		glRotatef(90,1,0,0);
		glRotatef(0.001*autorotate*180/pi,0,0,1);
		draw_sphere(72.0);
		glEnable(GL_BLEND);//�����������ēK�p
		////////////////////
		glPopMatrix();//�s��X�^�b�N���|�b�v


		glBindTexture(GL_TEXTURE_2D, texture_id5); //���S�̃e�N�X�`���̐ݒ��K�p
		draw_logo();//���S�̕`��


		glDisable(GL_TEXTURE_2D);//�e�N�X�`���ݒ���͂���

		glEnable(GL_LIGHTING);//����������K�p
		//�^�C�g����ʂł̉�]���鎩�@
		glPushMatrix();//�s��X�^�b�N���v�b�V��
		glTranslatef(0,-0.2,-1.0);
		glRotatef(-90,1,0,0);
		glRotatef(0.005*autorotate*180/pi,0,0,1);
		glTranslatef(0,0.0,-0.8);
		draw_jiki(autorotate);//���@�̕`��
		glPopMatrix();//�s��X�^�b�N���|�b�v

		glDisable(GL_LIGHTING);//�����������͂���
	}


	else if(scene==1){

		Vector target=enemy[targetnum];//�^�[�Q�b�g��ݒ�
		GLfloat d=2;//�J�����Ǝ��@�̂��炵����
		Vector r=target-jiki;//���@����W�I�܂ł̃x�N�g��
		GLfloat h=r.Magnitude();//���@�ƕW�I�̋���
		r.Normalize();//r�𐳋K��

		Vector ue(0,0,1.0);//�J�����ɑ΂�������ƂȂ�x�N�g��

		glClear(GL_COLOR_BUFFER_BIT);
		glPushMatrix();//�s��X�^�b�N���v�b�V��

		glEnable(GL_TEXTURE_2D);//�e�N�X�`���ݒ���ēK�p

		//////////////////////////�V��
		glPushMatrix();//�s��X�^�b�N���v�b�V��
		glDisable(GL_BLEND);//�����������͂���
		glBindTexture(GL_TEXTURE_2D, texture_id1); //��̃e�N�X�`���̐ݒ��K�p
		glRotatef(90,1,0,0);
		glRotatef(-jiki.theta*180/pi,0,0,1);
		draw_sphere(72.0);//�V���̕`��A���a��72
		glEnable(GL_BLEND);//�����������ēK�p
		glPopMatrix();//�s��X�^�b�N���|�b�v
		//////////////////////////////

		if(lockon){
			//���b�N�I�����̓L�[����ɂ���ăJ���������E�ɂ����
			gluLookAt(jiki.x-r.x*d-(r^ue).x*jikiLR/20,jiki.y-r.y*d-(r^ue).y*jikiLR/20,0.5+10/h,jiki.x+sin(jiki.theta),jiki.y+cos(jiki.theta),height,0.0,0.0,1.0);
			jiki.theta=atan2((target.x-jiki.x),(target.y-jiki.y));
		}
		else{
			gluLookAt(jiki.x-sin(jiki.theta)*d,jiki.y-cos(jiki.theta)*d,height,jiki.x+sin(jiki.theta),jiki.y+cos(jiki.theta),height,0.0,0.0,1.0);
		}


		glEnable(GL_TEXTURE_2D);//�e�N�X�`���ݒ���ēK�p


		//////////////////////////�V�̂̕`��
		glDisable(GL_BLEND);//�����������͂���

		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

		glPushMatrix();//�s��X�^�b�N���v�b�V��
		glTranslatef(-15,30,-12);
		glBindTexture(GL_TEXTURE_2D, texture_id7); //��̃e�N�X�`���̐ݒ��K�p
		draw_sphere(10.0);//�V�̂̕`��
		glPopMatrix();//�s��X�^�b�N���|�b�v

		glPushMatrix();//�s��X�^�b�N���v�b�V��
		glTranslatef(5,-20,-4);
		glBindTexture(GL_TEXTURE_2D, texture_id6); //��̃e�N�X�`���̐ݒ��K�p
		draw_sphere(2.0);//�V�̂̕`��
		glPopMatrix();//�s��X�^�b�N���|�b�v

		glEnable(GL_BLEND);//�����������ēK�p
		glDepthMask(GL_FALSE);
		////////////////////////////////

		glDisable(GL_TEXTURE_2D);//�e�N�X�`���ݒ���͂���

		draw_yuka();//����`��

		///////////////////////////�G�̕`��
		glEnable(GL_LIGHTING);//�����������ēK�p
		for(int i=0;i<enemy_num;i++){
			if(enemy[i].exist){
				glPushMatrix();//�s��X�^�b�N���v�b�V��
				glTranslatef(enemy[i].x, enemy[i].y, enemy[i].z);
				draw_enemy(autorotate);//�G�̕`��
				glPopMatrix();//�s��X�^�b�N���|�b�v
			}
		}
		glDisable(GL_LIGHTING);//�����������͂���
		glEnable(GL_TEXTURE_2D);//�e�N�X�`���ݒ���ēK�p
		///////////////////////////////////


		///////////////////////�����G�t�F�N�g�̕`��
		glBindTexture(GL_TEXTURE_2D, texture_id4);
		for(int i=0;i<10;i++){
			if(explosion[i].exist){
				glPushMatrix();//�s��X�^�b�N���v�b�V��
				glTranslatef(explosion[i].x, explosion[i].y, explosion[i].z);
				draw_explosion(explosion[i].counter);
				glPopMatrix();//�s��X�^�b�N���|�b�v
			}
		}
		////////////////////////////////////

		glDisable(GL_TEXTURE_2D);//�e�N�X�`���ݒ���͂���
		glEnable(GL_LIGHTING);//�����������ēK�p

		//////////////////////�~�T�C���̕`��
		for(int i=0;i<10;i++){
			if(missile[i].exist){
				glPushMatrix();//�s��X�^�b�N���v�b�V��
				glTranslatef(missile[i].x, missile[i].y, missile[i].z);
				glRotatef(90,-cos(missile[i].theta),sin(missile[i].theta),0);
				draw_missile(autorotate,false);
				glPopMatrix();//�s��X�^�b�N���|�b�v
			}
		}
		for(int i=0;i<enemy_num*10;i++){
			if(enemy_missile[i].exist){
				glPushMatrix();//�s��X�^�b�N���v�b�V��
				glTranslatef(enemy_missile[i].x, enemy_missile[i].y, enemy_missile[i].z);
				glRotatef(90,-cos(enemy_missile[i].theta),sin(enemy_missile[i].theta),0);
				draw_missile(autorotate,true);
				glPopMatrix();//�s��X�^�b�N���|�b�v
			}
		}
		///////////////////////////////

		if(game_over){
			for(int i=0;i<1;i++){
				if(autorotate%20){
					explosion[i].exist=true;
					explosion[i].x=jiki.x;
					explosion[i].y=jiki.y;
				}
			}
		}

		///////////////////////���@�̕`��
		glPushMatrix();//�s��X�^�b�N���v�b�V��
		glTranslatef(jiki.x, jiki.y, 0.0);
		glRotatef(-jiki.theta*180/pi+180,0,0,1);
		glRotatef(jikiLR,0,1,0);
		draw_jiki(autorotate);
		glPopMatrix();//�s��X�^�b�N���|�b�v
		////////////////////////////////

		glPopMatrix();//�s��X�^�b�N���|�b�v�A�����ŉ�ʈ�Ԏ�O�̕`�揇�Ɉړ��ł���

		glEnable(GL_TEXTURE_2D);//�e�N�X�`���ݒ���ēK�p
		glDisable(GL_LIGHTING);//�����������͂���

		//��������HUD�̕`��
		glPushMatrix();//�s��X�^�b�N���v�b�V��
		glTranslatef(0,0,-2);
		if(lockon){

			///////////////////////�Ə��̕`��
			glPushMatrix();//�s��X�^�b�N���v�b�V��
			glBindTexture(GL_TEXTURE_2D, texture_id3); //�}�b�v�̃e�N�X�`���̐ݒ��K�p
			glTranslatef(-jikiLR/30,-h/200+0.1,0);
			draw_sight();

			glBindTexture(GL_TEXTURE_2D, texture_id11); //�����̃e�N�X�`���̐ݒ��K�p
			glPushMatrix();//�s��X�^�b�N���v�b�V��
			glTranslatef(0.25,0.15,0);
			draw_number((int)h,0.2,3);//�^�[�Q�b�g�Ƃ̋�����`��
			glPopMatrix();//�s��X�^�b�N���|�b�v

			glPushMatrix();//�s��X�^�b�N���v�b�V��
			glTranslatef(0,0.32,0);
			draw_number(targetnum+1,0.4,1);//�^�[�Q�b�g�̓G�ԍ���`��
			glPopMatrix();//�s��X�^�b�N���|�b�v

			glPopMatrix();//�s��X�^�b�N���|�b�v
			/////////////////////////////////////
		}

		//////////////////////�G���A�[�̃A���[�g�`��
		if(jiki.x>40||jiki.y>40||jiki.x<-40||jiki.y<-40){
			if(autorotate%20!=0){
				glPushMatrix();//�s��X�^�b�N���v�b�V��
				glTranslatef(0,0.08,0);
				glBindTexture(GL_TEXTURE_2D, texture_id9); //�A���[�g�̃e�N�X�`���̐ݒ��K�p
				draw_alert();
				glPopMatrix();//�s��X�^�b�N���|�b�v
			}
		}
		////////////////////////////////////////

		///////////////////////�~�T�C�����߂Â��Ă����Ƃ��̃A���[�g�̕`��
		GLfloat dist=100;
		for(int i=0;i<enemy_num*10;i++){
			if(dist>(enemy_missile[i]-jiki).Magnitude())	dist=(enemy_missile[i]-jiki).Magnitude();
		}
		if(dist<8.0&&autorotate%((int)dist*2+1)!=0){
			glPushMatrix();//�s��X�^�b�N���v�b�V��
			glTranslatef(0,-0.05,0);
			glBindTexture(GL_TEXTURE_2D, texture_id8); //�A���[�g�̃e�N�X�`���̐ݒ��K�p
			draw_alert();
			glPopMatrix();//�s��X�^�b�N���|�b�v
		}
		///////////////////////////////////////////

		/////////////////////////////�Q�[���N���A���
		if(game_clear){
			glPushMatrix();//�s��X�^�b�N���v�b�V��
			glTranslatef(0,-0.2,0);
			glBindTexture(GL_TEXTURE_2D, texture_id12); //�A���[�g�̃e�N�X�`���̐ݒ��K�p
			draw_game_clear();
			glPopMatrix();//�s��X�^�b�N���|�b�v
		}
		///////////////////////////////////////////

		///////////////////////////�Q�[���I�[�o�[���
		if(game_over){
			glPushMatrix();//�s��X�^�b�N���v�b�V��
			glTranslatef(0,0.12,0);
			glBindTexture(GL_TEXTURE_2D, texture_id14); //�A���[�g�̃e�N�X�`���̐ݒ��K�p
			draw_game_clear();
			glPopMatrix();//�s��X�^�b�N���|�b�v
		}
		//////////////////////////////////////////////

		/////////////////////////HP�̕`��
		glPushMatrix();//�s��X�^�b�N���v�b�V��
		if(jiki.counter>3)glBindTexture(GL_TEXTURE_2D, texture_id10);
		else glBindTexture(GL_TEXTURE_2D, texture_id11);//�̗͂��c�菭�Ȃ��ƐԐF�ɂȂ�
		glTranslatef(0.5,0.3,0.7);
		glRotatef(-30,0,1,0);
		if(!game_over)draw_number(jiki.counter*10,1.0,3);
		else draw_number(0,1.0,3);//�̗͂��Ȃ��Ȃ�����0��\��
		glTranslatef(0.2,-0.05,0);
		glBindTexture(GL_TEXTURE_2D, texture_id13); 
		draw_percent();
		glPopMatrix();//�s��X�^�b�N���|�b�v
		///////////////////////////////////

		////////////////////////////�}�b�v�̕\��
		glPushMatrix();//�s��X�^�b�N���v�b�V��
		glBindTexture(GL_TEXTURE_2D, texture_id2); 
		glTranslatef(0,0,-0.7);
		glRotatef(30,0,1,0);
		draw_map(jiki,missile,enemy,enemy_missile,targetnum,enemy_num);//�r���Ńe�N�X�`���[�ݒ����
		glPopMatrix();//�s��X�^�b�N���|�b�v
		///////////////////////////////////////////////

		glPopMatrix();//�s��X�^�b�N���|�b�v
		glDepthMask(GL_TRUE);
	}

	glDisable(GL_LIGHTING);//�����������͂���

	glFlush();//����܂ł̖��߂�����

	glDisable(GL_BLEND);//�����������͂���


	glutSwapBuffers();//�o�b�t�@�̓���ւ�
}
void target_move(void)//�G�̈ړ�����
{
	//�G�͏��߂Ɍ��߂��p�x�ɑ΂��ĕǂɒ��˕Ԃ�Ȃ���ړ�����
	for(int i=0;i<enemy_num;i++){
		if(enemy[i].x>30||enemy[i].x<-30)vx[i]*=(-1);
		if(enemy[i].y>30||enemy[i].y<-30)vy[i]*=(-1);
		enemy[i].x+=vx[i];
		enemy[i].y+=vy[i];

		if(autorotate%100==0){
			enemy_fire[i]=true;//��莞�Ԃ��ƂɍU������
		}
	}
}
void hit_effect(void)//�����G�t�F�N�g����
{
	for(int i=0;i<10;i++){
		if(explosion[i].exist){
			explosion[i].counter+=1;
			if(explosion[i].counter>15)//�����A�j���[�V�������I�������
			{
				explosion[i].exist=false;//����������
				explosion[i].counter=0;
			}
		}
	}
}
void missile_move()//���@�̃~�T�C���̋���
{
	Vector attacker=jiki;
	for(int i=0;i<10;i++){

		Vector m=enemy[targetnum]-missile[i];
		Vector v=missile[i];
		m.Normalize();

		//�~�T�C�����ˎ��̐ݒ�
		if(fire&&missile[i].exist==false){
			missile[i].x=attacker.x+sin(jiki.theta)*0.5;
			missile[i].y=attacker.y+cos(jiki.theta)*0.5;
			missile[i].z=attacker.z;
			missile[i].exist=true;
			fire=false;
			break;
		}

		if(missile[i].exist&&missile[i].counter<150){

			fai=atan2(m.x,m.y)-atan2(sin(missile[i].theta),cos(missile[i].theta));
			missile[i].theta+=fai;//�~�T�C�����猩���W�I�ւ̊p�x�ɋȂ���
			missile[i].x+=m.x*speed*1.3;
			missile[i].y+=m.y*speed*1.3;

			missile[i].counter++;

			for(int j=0;j<enemy_num;j++){
				if((enemy[j]-missile[i]).Magnitude()<1.5){//�~�T�C���ƕW�I���߂Â�����
					if(enemy[j].counter==0)enemy[j].exist=false;
					enemy[j].counter-=1;
					explosion[i].exist=true;//�������N����
					explosion[i].x=missile[i].x;
					explosion[i].y=missile[i].y;
					missile[i].exist=false;	
				}
			}
		}
		else{//���ɓ����炸��ё������Ƃ��̏���
			missile[i].x=100;
			missile[i].y=100;
			missile[i].counter=0;
			missile[i].exist=false;
		}
	}
}
void enemy_missile_move()//�G�@�̃~�T�C���̋���
{
	for(int n=0;n<enemy_num;n++){
		Vector attacker=enemy[n];
		for(int i=0;i<10;i++){
			Vector m=jiki-enemy_missile[i+10*n];
			Vector v=enemy_missile[i+10*n];
			m.Normalize();

			//�~�T�C�����ˎ��̐ݒ�
			if(enemy[n].exist&&enemy_fire[n]&&enemy_missile[i+10*n].exist==false){
				enemy_missile[i+10*n].x=attacker.x+sin(jiki.theta)*0.5;
				enemy_missile[i+10*n].y=attacker.y+cos(jiki.theta)*0.5;
				enemy_missile[i+10*n].z=attacker.z;
				enemy_missile[i+10*n].exist=true;
				enemy_fire[n]=false;
				break;
			}

			if(enemy_missile[i+10*n].exist&&enemy_missile[i+10*n].counter<300){
				fai=atan2(m.x,m.y)-atan2(sin(enemy_missile[i+10*n].theta),cos(enemy_missile[i+10*n].theta));
				enemy_missile[i+10*n].theta+=fai;//�~�T�C�����猩���W�I�ւ̊p�x�ɋȂ���
				enemy_missile[i+10*n].x+=m.x*speed*0.5;
				enemy_missile[i+10*n].y+=m.y*speed*0.5;
				enemy_missile[i+10*n].counter++;

				if((jiki-enemy_missile[i+10*n]).Magnitude()<1.5){//�~�T�C���ƕW�I���߂Â�����
					jiki.counter-=1;
					explosion[i].exist=true;//�������N����
					explosion[i].x=enemy_missile[i+10*n].x;
					explosion[i].y=enemy_missile[i+10*n].y;
					enemy_missile[i+10*n].exist=false;	
				}
			}
			else{
				enemy_missile[i+10*n].x=100;
				enemy_missile[i+10*n].y=100;
				enemy_missile[i+10*n].counter=0;
				enemy_missile[i+10*n].exist=false;
			}
		}
	}
}

void key_move(void){//�L�[����

	if(forward){
		jiki.y+=speed*cos(jiki.theta);
		jiki.x+=speed*sin(jiki.theta);

		GLfloat dist=100;
		for(int i=0;i<enemy_num;i++){
			if(dist>(enemy[i]-jiki).Magnitude())dist=(enemy[i]-jiki).Magnitude();
		}

		if(dist<1||jiki.x>50||jiki.y>50||jiki.x<-50||jiki.y<-50){//�G��ǂɂ߂荞�܂Ȃ����߂̏���
			jiki.y-=speed*cos(jiki.theta);
			jiki.x-=speed*sin(jiki.theta);
		}
	}
	else if(backward){

		jiki.y-=speed*cos(jiki.theta);
		jiki.x-=speed*sin(jiki.theta);

		GLfloat dist=100;
		for(int i=0;i<enemy_num;i++){
			if(dist>(enemy[i]-jiki).Magnitude())	dist=(enemy[i]-jiki).Magnitude();
		}

		if(dist<1||jiki.x>50||jiki.y>50||jiki.x<-50||jiki.y<-50){//�G��ǂɂ߂荞�܂Ȃ����߂̏���
			jiki.y+=speed*cos(jiki.theta);
			jiki.x+=speed*sin(jiki.theta);
		}
	}

	if(right){

		jiki.y-=speed*sin(jiki.theta);
		jiki.x+=speed*cos(jiki.theta);

		GLfloat dist=100;
		for(int i=0;i<enemy_num;i++){
			if(dist>(enemy[i]-jiki).Magnitude())	dist=(enemy[i]-jiki).Magnitude();
		}

		if(dist<1||jiki.x>50||jiki.y>50||jiki.x<-50||jiki.y<-50){//�G��ǂɂ߂荞�܂Ȃ����߂̏���
			jiki.y+=speed*sin(jiki.theta);
			jiki.x-=speed*cos(jiki.theta);
		}

		if(jikiLR<12){
			jikiLR+=1;
		}
	}
	else if(left){
		jiki.y+=speed*sin(jiki.theta);
		jiki.x-=speed*cos(jiki.theta);

		GLfloat dist=100;
		for(int i=0;i<enemy_num;i++){
			if(dist>(enemy[i]-jiki).Magnitude())	dist=(enemy[i]-jiki).Magnitude();
		}

		if(dist<1||jiki.x>50||jiki.y>50||jiki.x<-50||jiki.y<-50){//�G��ǂɂ߂荞�܂Ȃ����߂̏���
			jiki.y-=speed*sin(jiki.theta);
			jiki.x+=speed*cos(jiki.theta);
		}

		if(jikiLR>-12){
			jikiLR-=1;

		}
	}
	else{
		if(jikiLR>0)jikiLR-=0.5;
		else if(jikiLR<0)jikiLR+=0.5;
	}
	if(seeright){
		jiki.theta += 1.0*pi/180;
	}
	else if(seeleft){
		jiki.theta -= 1.0*pi/180;
	}

}
void special_down(int key, int x, int y)
{
	if(key==GLUT_KEY_RIGHT){
		if(!lockon)seeright=true; 
		else next=true;
	}
	if(key==GLUT_KEY_LEFT)
	{
		if(!lockon)seeleft=true; 
		else prev=true;
	}
}
void special_up(int key, int x, int y)
{
	if(key==GLUT_KEY_RIGHT) seeright=false;

	if(key==GLUT_KEY_LEFT) seeleft=false;
}
void key_down(unsigned char key, int x, int y)//�L�[�{�[�h�C�x���g
{
	if(key=='q')targetnum=(targetnum+9)%10;

	// w�L�[�F�O�i
	if(key=='w')forward=true;
	// a�L�[�F��
	if(key=='a')left=true;
	// s�L�[�F��i
	if(key=='s')backward=true;
	// x�L�[�F�E
	if(key=='d')right=true;

	// f�L�[�F���b�N�I���؂�ւ�
	if(key=='f'){ 
		if(!lockon&&!game_clear)lockon=true;
		else {
			lockon=false;
		}
	}
	//�X�y�[�X�L�[�F�U��
	if(key==' '){
		if(lockon)if(!fire)fire=true;
	}

	// Esc�L�[�F�����I��
	if(key==27){
		exit(0);
	}

	if(key==13){//�Q�[���X�^�[�g
		scene=(scene+=1)%2;
	}

}
void key_up(unsigned char key, int x, int y)//�L�[�{�[�h�C�x���g
{
	if(key=='w')forward=false;

	if(key=='a')left=seeleft=false;

	if(key=='s')backward=false;

	if(key=='d')right=seeright=false;
}

void target_change(){
	int gekiha=0;
	for(int i=0;i<enemy_num;i++){
		if(!enemy[targetnum].exist){//���W�I�Ƃ��Ă���G���j�󂳂ꂽ��
			targetnum=(targetnum+1)%enemy_num;//���̑��݂��Ă���W�I�ɐ؂�ւ���
			gekiha++;
		}
		else{
			break;
		}
	}
	if(gekiha==enemy_num){//�G��S�Ĕj�󂵂���
		game_clear=true;//�Q�[���N���A
		lockon=false;
	}

	if(!game_clear){
		if(next||prev){//���b�N�I�����ɍ��E�L�[�������ꂽ��
			//���̑��݂��Ă���W�I�܂ŕW�I�ԍ��𑝂₷�i���炷�j
			if(prev)targetnum=(targetnum+enemy_num-1)%enemy_num;
			else targetnum=(targetnum+1)%enemy_num;

			for(int i=0;i<enemy_num;i++){
				if(!enemy[targetnum].exist){
					if(prev)targetnum=(targetnum+enemy_num-1)%enemy_num;
					else targetnum=(targetnum+1)%enemy_num;
				}
				else{
					next=false;
					prev=false;
					break;
				}
			}
		}
	}
}