#include<windows.h>
#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>
#include<math.h>
#include<stdio.h>
#include "vector.h"

void draw_jiki(int r){//自機の描画	引数としてrを受け取り翼を回転させる
	//光源の設定
	GLfloat specular[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat cube[] = {1.0, 1.0, 0.0, 1.0};//黄色のワイヤーフレーム	
	GLfloat cubealfa[] = {1.0, 1.0, 0.0, 0.2};//半透明の黄色で面を描画	
	GLfloat shininess[] = {50.0};

	//各設定を適用
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cube);//まずワイヤーフレームの色で設定
	int t=1;//左右に対称に同じものを書くため切り替えの為の変数を宣言

	////////////////////////////////////////////////////////////ワイヤーフレームここから
	//胴体
	glPushMatrix();//行列スタックをプッシュ
	glTranslatef(0,0,0.5);
	glRotatef(80,1.0,0.0,0.0);
	glutWireCone(0.08,0.3,5,3);
	glPopMatrix();//行列スタックをポップ
	//頭部
	glPushMatrix();//行列スタックをプッシュ
	glTranslatef(0,-0.3,0.55);
	glRotatef(90,1.0,0.0,0.0);
	glutWireCone(0.06,0.2,5,3);
	glPopMatrix();//行列スタックをポップ
	//中心の尾翼
	glPushMatrix();//行列スタックをプッシュ
	glTranslatef(0,0.43,0.25);
	glRotatef(60,1.0,0.0,0.0);
	glRotatef(r,0.0,0.0,1.0);
	glutWireCone(0.05,0.5,3,3);
	glPopMatrix();//行列スタックをポップ
	//左右の翼を描画
	for(int i=0;i<2;i++){
		//尾翼の1本目
		glPushMatrix();//行列スタックをプッシュ
		glTranslatef(-0.23*t,0.38,0.25);
		glRotatef(30*t,0.0,0.0,1.0);
		glRotatef(60,1.0,0.0,0.0);
		glRotatef(r,0.0,0.0,1.0);
		glutWireCone(0.05,0.5,3,3);
		glPopMatrix();//行列スタックをポップ
		//尾翼の2本目
		glPushMatrix();//行列スタックをプッシュ
		glTranslatef(-0.4*t,0.22,0.25);
		glRotatef(60*t,0.0,0.0,1.0);
		glRotatef(60,1.0,0.0,0.0);
		glRotatef(r,0.0,0.0,1.0);
		glutWireCone(0.05,0.5,3,3);
		glPopMatrix();//行列スタックをポップ
		//翼の根本
		glPushMatrix();//行列スタックをプッシュ
		glBegin(GL_LINE_LOOP);
		glVertex3f(t*0.04, -0.2, 0.53);
		glVertex3f(t*0.12, -0.23, 0.58);
		glVertex3f(t*0.12, -0.17, 0.58);
		glEnd();
		glPopMatrix();//行列スタックをポップ

		//2段目前方の翼
		glPushMatrix();//行列スタックをプッシュ
		glBegin(GL_LINE_LOOP);
		glVertex3f(t*0.12, -0.23, 0.58);
		glVertex3f(t*0.23, -0.3, 0.57);
		glVertex3f(t*0.24, -0.21, 0.6);
		glEnd();
		glPopMatrix();//行列スタックをポップ
		//2段目後方の翼
		glPushMatrix();//行列スタックをプッシュ
		glBegin(GL_LINE_LOOP);
		glVertex3f(t*0.12, -0.17, 0.58);
		glVertex3f(t*0.24, -0.19, 0.6);
		glVertex3f(t*0.23, -0.11, 0.57);
		glEnd();
		glPopMatrix();//行列スタックをポップ
		//3段目後方前側の翼
		glPushMatrix();//行列スタックをプッシュ
		glBegin(GL_LINE_LOOP);
		glVertex3f(t*0.24, -0.18, 0.6);
		glVertex3f(t*0.53, -0.19, 0.59);
		glVertex3f(t*0.5, -0.08, 0.57);
		glEnd();
		glPopMatrix();//行列スタックをポップ
		//3段目後方後側の翼
		glPushMatrix();//行列スタックをプッシュ
		glBegin(GL_LINE_LOOP);
		glVertex3f(t*0.24, -0.12, 0.57);
		glVertex3f(t*0.5, -0.07, 0.57);
		glVertex3f(t*0.45, 0.04, 0.54);
		glEnd();
		glPopMatrix();//行列スタックをポップ
		//3段目前方後側の翼
		glPushMatrix();//行列スタックをプッシュ
		glBegin(GL_LINE_LOOP);
		glVertex3f(t*0.24, -0.22, 0.6);
		glVertex3f(t*0.53, -0.21, 0.59);
		glVertex3f(t*0.5, -0.32, 0.6);
		glEnd();
		glPopMatrix();//行列スタックをポップ
		//3段目前方前側の翼
		glPushMatrix();//行列スタックをプッシュ
		glBegin(GL_LINE_LOOP);
		glVertex3f(t*0.24, -0.29, 0.57);
		glVertex3f(t*0.5, -0.33, 0.6);
		glVertex3f(t*0.45, -0.44, 0.57);
		glEnd();
		glPopMatrix();//行列スタックをポップ
		t*=-1;
	}
	/////////////////////////////////////////////////////////ワイヤーフレームここまで
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cubealfa);//半透明の自機色に変更
	//////////////////////////////////////////////////////////半透明の面ここから
	//胴体
	glPushMatrix();//行列スタックをプッシュ
	glTranslatef(0,0,0.5);
	glRotatef(80,1.0,0.0,0.0);
	glutSolidCone(0.08,0.3,5,3);
	glPopMatrix();//行列スタックをポップ
	//頭部
	glPushMatrix();//行列スタックをプッシュ
	glTranslatef(0,-0.3,0.55);
	glRotatef(90,1.0,0.0,0.0);
	glutSolidCone(0.06,0.2,5,3);
	glPopMatrix();//行列スタックをポップ
	//中央の尾翼
	glPushMatrix();//行列スタックをプッシュ
	glTranslatef(0,0.43,0.25);
	glRotatef(60,1.0,0.0,0.0);
	glRotatef(r,0.0,0.0,1.0);
	glutSolidCone(0.05,0.5,3,3);
	glPopMatrix();//行列スタックをポップ
	//左右の翼を描画
	for(int i=0;i<2;i++){
		//尾翼の1本目
		glPushMatrix();//行列スタックをプッシュ
		glTranslatef(-0.23*t,0.38,0.25);
		glRotatef(30*t,0.0,0.0,1.0);
		glRotatef(60,1.0,0.0,0.0);
		glRotatef(r,0.0,0.0,1.0);
		glutSolidCone(0.05,0.5,3,3);
		glPopMatrix();//行列スタックをポップ
		//尾翼の2本目
		glPushMatrix();//行列スタックをプッシュ
		glTranslatef(-0.4*t,0.22,0.25);
		glRotatef(60*t,0.0,0.0,1.0);
		glRotatef(60,1.0,0.0,0.0);
		glRotatef(r,0.0,0.0,1.0);
		glutSolidCone(0.05,0.5,3,3);
		glPopMatrix();//行列スタックをポップ
		////翼の根本
		glPushMatrix();//行列スタックをプッシュ
		glBegin(GL_TRIANGLES);
		glVertex3f(t*0.04, -0.2, 0.53);
		glVertex3f(t*0.12, -0.23, 0.58);
		glVertex3f(t*0.12, -0.17, 0.58);
		glEnd();
		glPopMatrix();//行列スタックをポップ

		//2段目前方の翼
		glPushMatrix();//行列スタックをプッシュ
		glBegin(GL_TRIANGLES);
		glVertex3f(t*0.12, -0.23, 0.58);
		glVertex3f(t*0.23, -0.3, 0.57);
		glVertex3f(t*0.24, -0.21, 0.6);
		glEnd();
		glPopMatrix();//行列スタックをポップ
		//2段目後方の翼
		glPushMatrix();//行列スタックをプッシュ
		glBegin(GL_TRIANGLES);
		glVertex3f(t*0.12, -0.17, 0.58);
		glVertex3f(t*0.24, -0.19, 0.6);
		glVertex3f(t*0.23, -0.11, 0.57);
		glEnd();
		glPopMatrix();//行列スタックをポップ
		//3段目後方前側の翼
		glPushMatrix();//行列スタックをプッシュ
		glBegin(GL_TRIANGLES);
		glVertex3f(t*0.24, -0.18, 0.6);
		glVertex3f(t*0.53, -0.19, 0.59);
		glVertex3f(t*0.5, -0.08, 0.57);
		glEnd();
		glPopMatrix();//行列スタックをポップ
		//3段目後方後側の翼
		glPushMatrix();//行列スタックをプッシュ
		glBegin(GL_TRIANGLES);
		glVertex3f(t*0.24, -0.12, 0.57);
		glVertex3f(t*0.5, -0.07, 0.57);
		glVertex3f(t*0.45, 0.04, 0.54);
		glEnd();
		glPopMatrix();//行列スタックをポップ
		//3段目前方後側の翼
		glPushMatrix();//行列スタックをプッシュ
		glBegin(GL_TRIANGLES);
		glVertex3f(t*0.24, -0.22, 0.6);
		glVertex3f(t*0.53, -0.21, 0.59);
		glVertex3f(t*0.5, -0.32, 0.6);
		glEnd();
		glPopMatrix();//行列スタックをポップ
		//3段目前方前側の翼
		glPushMatrix();//行列スタックをプッシュ
		glBegin(GL_TRIANGLES);
		glVertex3f(t*0.24, -0.29, 0.57);
		glVertex3f(t*0.5, -0.33, 0.6);
		glVertex3f(t*0.45, -0.44, 0.57);
		glEnd();
		glPopMatrix();//行列スタックをポップ
		t*=-1;
	}
	/////////////////////////////////////////////////////////半透明の面ここまで
}

void draw_missile(int r,bool e){//ミサイルの描画	引数として、自動に回転するための変数と敵のミサイルかどうかを渡すbool型を用意
	//光源の設定
	GLfloat specular[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat enemy[] = {1.0, 0.0, 0.0, 1.0};//敵の色は赤
	GLfloat enemyalfa[] = {1.0, 0.0, 0.0, 0.2};
	GLfloat missile[] = {1.0, 1.0, 1.0, 1.0};//味方のミサイルは白色
	GLfloat missilealfa[] = {1.0, 1.0, 1.0, 0.2};
	GLfloat shininess[] = {50.0};

	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
	if(e)glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, enemy);//ミサイルが敵のものなら赤を設定
	else glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, missile);//そうでないなら白を設定
	//ワイヤーフレームでの描画
	glPushMatrix();//行列スタックをプッシュ
	glRotatef(r*5,0,0.0,1.0);//ミサイルは全体が回転する

	glPushMatrix();//行列スタックをプッシュ
	glTranslatef(0,0,0.5);
	glutWireCone(0.1,0.5,3,5);//三角錐でミサイルを表現する
	glRotatef(180,0,1.0,0.0);
	glutWireCone(0.03,0.5,3,5);
	for(int i=0;i<3;i++){
		glPushMatrix();//行列スタックをプッシュ
		glRotatef(120*i,0,0.0,1.0);
		glTranslatef(0,0.07,0.0);
		glutWireCone(0.02,0.3,3,5);
		glPopMatrix();//行列スタックをポップ
	}
	glPopMatrix();//行列スタックをポップ

	/////////////////////////////////半透明な面の描画
	if(e)glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, enemyalfa);
	else glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, missilealfa);

	glPushMatrix();//行列スタックをプッシュ
	glTranslatef(0,0,0.5);
	glutSolidCone(0.1,0.5,3,5);
	glRotatef(180,0,1.0,0.0);
	glutSolidCone(0.03,0.5,3,5);
	for(int i=0;i<3;i++){
		glPushMatrix();//行列スタックをプッシュ
		glRotatef(120*i,0,0.0,1.0);
		glTranslatef(0,0.07,0.0);
		glutSolidCone(0.02,0.3,3,5);
		glPopMatrix();//行列スタックをポップ
	}
	glPopMatrix();//行列スタックをポップ
	glPopMatrix();//行列スタックをポップ
}

void draw_map(Vector jiki,Vector missile[],Vector enemy[],Vector enemy_missile[],int targetnum,int enemy_num)//マップに位置を描画するために、自機やミサイル、敵の位置や数を渡す
{


	GLfloat pointer_jiki[] = {1.0, 1.0, 0.0, 1.0};
	GLfloat pointer_missile[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat pointer_enemy[] = {1.0, 0.0, 0.0, 1.0};

	//マップのテクスチャを適用した状態でこの処理が呼び出される

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

	glDisable(GL_TEXTURE_2D);//テクスチャの設定を解除

	///////////////////ポインターの描画
	//自機のポインターを描画
	glColor4fv(pointer_jiki);
	glPushMatrix();//行列スタックをプッシュ
	glTranslatef(-1.1+jiki.x/50*0.3,0.5+jiki.y/50*0.3,0);
	glRotatef(-jiki.theta*180/pi,0,0.0,1.0);
	glBegin(GL_TRIANGLES);
	glVertex3f(-0.01, -0.01,0.0);
	glVertex3f(0.01, -0.01,0.0);
	glVertex3f(0.0,0.02,0.0);
	glEnd();
	glPopMatrix();//行列スタックをポップ

	//自機のミサイルのポインタ
	glColor4fv(pointer_missile);
	for(int i=0;i<10;i++){
		if(missile[i].exist){
			glPushMatrix();//行列スタックをプッシュ
			glTranslatef(-1.1+missile[i].x/50*0.3,0.5+missile[i].y/50*0.3,0);
			glRotatef(-missile[i].theta*180/pi,0,0,1);
			glBegin(GL_TRIANGLES);
			glVertex3f(-0.005, -0.005,0.0);
			glVertex3f(0.005, -0.005,0.0);
			glVertex3f(0.0,0.01,0.0);

			glEnd();
			glPopMatrix();//行列スタックをポップ
		}
	}
	//敵のミサイルのポインタ
	glColor4fv(pointer_enemy);
	for(int i=0;i<enemy_num*10;i++){

		//	for(int j=0;j<1;j++){
		if(enemy_missile[i].exist){
			glPushMatrix();//行列スタックをプッシュ
			glTranslatef(-1.1+enemy_missile[i].x/50*0.3,0.5+enemy_missile[i].y/50*0.3,0);
			glRotatef(-enemy_missile[i].theta*180/pi,0,0.0,1);
			glBegin(GL_TRIANGLES);

			glVertex3f(-0.005, -0.005,0.0);
			glVertex3f(0.005, -0.005,0.0);
			glVertex3f(0.0,0.01,0.0);

			glEnd();
			glPopMatrix();//行列スタックをポップ
		}
		//		}
	}

	//敵のポインタ
	for(int i=0;i<enemy_num;i++){
		if(enemy[i].exist){
			glPushMatrix();//行列スタックをプッシュ
			glTranslatef(-1.1+enemy[i].x/50*0.3,0.5+enemy[i].y/50*0.3,0);
			int n=10;
			int j=0;
			for(j=0;j<n;j++){
				glPushMatrix();//行列スタックをプッシュ

				glBegin(GL_TRIANGLES);
				glVertex3f(0.01*cos(2*pi*j/n),0.01*sin(2*pi*j/n),0.0);
				glVertex3f(0.01*cos(2*pi*(j+1)/n),0.01*sin(2*pi*(j+1)/n),0.0);
				glVertex3f(0.0,0.0,0.0);
				glEnd();
				glPopMatrix();//行列スタックをポップ
			}
			//ターゲットされている敵は特別に印をつける
			if(i==targetnum){
				glBegin(GL_LINE_LOOP);
				for(j=0;j<n;j++){
					glVertex3f(0.015*cos(2*pi*j/n),0.015*sin(2*pi*j/n),0.0);
					glVertex3f(0.015*cos(2*pi*(j+1)/n),0.015*sin(2*pi*(j+1)/n),0.0);
				}
				glEnd();
			}

			glPopMatrix();//行列スタックをポップ
		}
	}
}

void draw_explosion(GLint r){//爆発エフェクトの描画。アニメーション用に増え続ける値rを渡す
	//爆発のアニメーションを含んだ一枚のテクスチャをrの値によって貼り付ける場所を切り替える
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
	//同じものを十字に貼って立体的に見えるようにする
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

void draw_yuka(void){//床の描画
	glColor4f(0.8,0.8,1,0.2);//テクスチャではなく半透明の線で描く
	//メッシュを描く
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

void draw_enemy(int r)//敵の描画。これも自動回転する部位を回すための増え続ける値rを渡す
{
	GLfloat specular[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat enemy[] = {1.0, 0.0, 0.0, 1.0};	
	GLfloat enemyalfa[] = {1.0, 0.0, 0.0, 0.2};	
	GLfloat shininess[] = {50.0};

	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, enemy);
	//敵機のワイヤーフレームを描画
	glPushMatrix();//行列スタックをプッシュ
	glRotatef(-r*5,0.0,0.0,1.0);

	glPushMatrix();//行列スタックをプッシュ
	glTranslatef(0,0,0.3);
	glRotatef(180,1.0,0.0,0.0);
	glutWireCone(0.12,0.3,7,3);
	glPopMatrix();//行列スタックをポップ

	glPushMatrix();//行列スタックをプッシュ
	glTranslatef(0,0,0.7);
	glutWireCone(0.12,0.3,7,3);
	glPopMatrix();//行列スタックをポップ

	glPushMatrix();//行列スタックをプッシュ
	glTranslatef(0,0,0.5);
	glutWireSphere(0.15,7,7);//敵の核部分
	glPopMatrix();//行列スタックをポップ
	glPopMatrix();//行列スタックをポップ

	int t=1;
	for(int i=0;i<7;i++)//機体の周りを回転する針の描画
	{
		glPushMatrix();//行列スタックをプッシュ
		glRotatef((double)i/7*360,0.0,0.0,1.0);

		for(int j=0;j<2;j++){
			glPushMatrix();//行列スタックをプッシュ
			glRotatef(r*5*t,0.0,0.0,1.0);
			glTranslatef(0,0,0.5);
			glRotatef(90,1.0,0.0,0.0);

			glRotatef(20*t,1.0,0.0,0.0);
			glTranslatef(0,0,0.3);
			glutWireCone(0.05,0.4,7,3);
			glPopMatrix();//行列スタックをポップ

			t*=-1;
		}
		glPopMatrix();//行列スタックをポップ
	}
	///////////////////////////////////////////
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, enemyalfa);
	//半透明で面を描く
	///////////////////////////////////////////////////////
	glPushMatrix();//行列スタックをプッシュ
	glRotatef(-r*5,0.0,0.0,1.0);

	glPushMatrix();//行列スタックをプッシュ
	glTranslatef(0,0,0.3);
	glRotatef(180,1.0,0.0,0.0);
	glutSolidCone(0.12,0.3,7,3);
	glPopMatrix();//行列スタックをポップ

	glPushMatrix();//行列スタックをプッシュ
	glTranslatef(0,0,0.7);
	glutSolidCone(0.12,0.3,7,3);
	glPopMatrix();//行列スタックをポップ

	glPushMatrix();//行列スタックをプッシュ
	glTranslatef(0,0,0.5);
	glutSolidSphere(0.15,7,7);
	glPopMatrix();//行列スタックをポップ

	glPopMatrix();//行列スタックをポップ
	for(int i=0;i<7;i++)
	{
		glPushMatrix();//行列スタックをプッシュ
		glRotatef((double)i/7*360,0.0,0.0,1.0);

		for(int j=0;j<2;j++){
			glPushMatrix();//行列スタックをプッシュ
			glRotatef(r*5*t,0.0,0.0,1.0);
			glTranslatef(0,0,0.5);
			glRotatef(90,1.0,0.0,0.0);

			glRotatef(20*t,1.0,0.0,0.0);
			glTranslatef(0,0,0.3);
			glutSolidCone(0.05,0.4,7,3);
			glPopMatrix();//行列スタックをポップ

			t*=-1;
		}
		glPopMatrix();//行列スタックをポップ
	}

}

void draw_sphere(GLfloat dist)//天体や宇宙の描画をまとめて請け負うメソッド。球体の半径を引数として渡す
{
	int N=100;//球は100分割で描く
	GLfloat PI = 3.14159265358979323846264338327950;//円周率

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

void draw_sight(void)//ロックオン時に画面中央に描く照準
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

void draw_logo(void)//タイトル画面でのロゴの描画
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

void draw_alert(void)//ミサイルが近づいていたり、エリアの端に近づいたときに発生するアラートの描画
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

void draw_number(int n,double d,int keta)//数字の描画
	//テクスチャの中に0から9までの画像が均等に並んでおり、それをきりとって使う
	//引数として、表示する数字・数字の大きさ・桁数を渡している
{
	int num[3];//桁は3ケタまで対応
	num[0]=n%10;//1桁目
	num[1]=(int)((double)n/10)%10;//2桁目
	num[2]=(int)((double)n/100)%10;//3桁目
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

void draw_game_clear(void)//ゲームオーバー時やゲームクリア時に呼び出されるメソッド
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

void draw_percent(void)//自機のHP表示で使う％表示
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
