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

GLubyte *texture_sky;//空のテクスチャ
GLuint texture_id1;

GLubyte *texture_map;//マップのテクスチャ
GLuint texture_id2;

GLubyte *texture_sight;//照準のテクスチャ
GLuint texture_id3;

GLubyte *texture_bomb;//爆発エフェクトのテクスチャ
GLuint texture_id4;

GLubyte *texture_logo;//タイトルロゴのテクスチャ
GLuint texture_id5;

GLubyte *texture_planet1;//天体のテクスチャ
GLuint texture_id6;

GLubyte *texture_planet2;//もうひとつの天体のテクスチャ
GLuint texture_id7;

GLubyte *texture_alert1;//ミサイルアラートのテクスチャ
GLuint texture_id8;

GLubyte *texture_alert2;//エリア外アラートのテクスチャ
GLuint texture_id9;

GLubyte *texture_num_yellow;//黄色い数字のテクスチャ
GLuint texture_id10;

GLubyte *texture_num_red;//赤い数字のテクスチャ
GLuint texture_id11;

GLubyte *texture_game_clear;//クリア画面のテクスチャ
GLuint texture_id12;

GLubyte *texture_percent;//パーセントのテクスチャ
GLuint texture_id13;

GLubyte *texture_game_over;//ゲームオーバー画面のテクスチャ
GLuint texture_id14;

GLfloat height = 1.0;//カメラの高さ
GLfloat speed=0.25;//自機関連のスピード
int autorotate=0;//オブジェクトの回転や攻撃タイミングを計るのに使う、増え続ける数
GLfloat jikiLR=0;//ロックオン時のカメラが左右に動く演出のための変数

bool lockon=true;//ロックオン
bool fire=false;//自機の攻撃フラグ
bool enemy_fire[10];//敵機の攻撃フラグ
bool next=true;//ロックオンを次に切り替えるフラグ
bool prev=true;//ロックオンを前に切り替えるフラグ
bool game_clear=false;//ゲームクリアの判定フラグ
bool game_over=false;//ゲームオーバーの判定フラグ

//キーボード操作の切り替えフラグ
bool forward=false;
bool backward=false;
bool left=false;
bool right=false;
bool seeleft=false;
bool seeright=false;

//タイトル画面とゲーム画面の切り替えフラグ
int scene=0;

Vector enemy[5];//敵機は5とする
int enemy_num=5;
Vector jiki;
GLfloat vx[5];//敵機の移動方向の初期化
GLfloat vy[5];

GLfloat fai=0;

Vector missile[10];//自機のミサイル
Vector enemy_missile[50];//敵機のミサイル
Vector explosion[11];//爆発エフェクト

int targetnum=1;//ターゲット番号の初期値

void main(int argc, char** argv)//メイン文
{
	//ウインドウの描写
	glutInit(&argc, argv);//glutの初期化
	//Zバッファを行う場合のウインドウモードを設定
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(1900, 1000);//ウインドウサイズ
	glutCreateWindow("sample1.c");//ウインドウネーム

	gl_init();//OpenGLの初期設定
	lighting_init();//光源処理の初期設定

	//テクスチャの初期化

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


	//自機の初期化
	jiki.counter=10;
	jiki.y=-20;
	//ミサイルや爆発エフェクトの初期化
	for(int i=0;i<10;i++){
		enemy_missile[i].exist=false;
		enemy_missile[i+10].exist=false;
		missile[i].exist=false;
		explosion[i].exist=false;
	}
	explosion[10].exist=false;
	//敵の初期化
	srand(50);//敵の移動方向はランダムに決定する
	for(int i=0;i<enemy_num;i++){
		enemy[i].counter=7;
		enemy[i].theta=rand()/25;
		vx[i]=speed*sin(enemy[i].theta);
		vy[i]=speed*cos(enemy[i].theta);
		enemy[i].exist=true;
		enemy_fire[i]=false;
	}

	glutIdleFunc(idle);
	glutKeyboardFunc(key_down);//キーボードイベントを登録
	glutKeyboardUpFunc(key_up);//キーボードイベントを登録
	glutDisplayFunc(display);//イベントとしてdisplayを描画用関数として登録
	glutSpecialFunc(special_down);//キーボードイベントを登録
	glutSpecialUpFunc(special_up);//キーボードイベントを登録
	glutMainLoop();//イベント待ちループに入る
}

void idle()
{
	if(jiki.counter==0)game_over=true;//ゲームオーバー状態かどうか確認
	autorotate+=1;//自動的に増え続ける数字
	if(scene==1){//ゲーム画面での処理
		target_move();
		missile_move();
		enemy_missile_move();
		hit_effect();
	}
	if(!game_over)key_move();//ゲームオーバーになったらキー操作は効かない
	target_change();

	glutPostRedisplay();
}


void display(void)//画面
{
	//Zバッファを導入した、OpenGLの初期化
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

	glMatrixMode(GL_MODELVIEW);//モデルビュー行列
	glLoadIdentity();//投影変換を単位行列で初期化
	glColor3f(1,1,1);

	glEnable(GL_BLEND);//混合処理を適用
	glBlendFunc(GL_ONE, GL_ZERO);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	gluPerspective(45.0, 1.9, 0.5,200.0);


	if(scene==0){//タイトル画面
		glDepthMask(GL_FALSE);
		glClear(GL_COLOR_BUFFER_BIT);

		glEnable(GL_TEXTURE_2D);//テクスチャ設定を適用

		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

		glPushMatrix();//行列スタックをプッシュ
		//////////////////////////天球
		glDisable(GL_BLEND);//混合処理をはずす
		glBindTexture(GL_TEXTURE_2D, texture_id1); //空のテクスチャの設定を適用
		glRotatef(90,1,0,0);
		glRotatef(0.001*autorotate*180/pi,0,0,1);
		draw_sphere(72.0);
		glEnable(GL_BLEND);//混合処理を再適用
		////////////////////
		glPopMatrix();//行列スタックをポップ


		glBindTexture(GL_TEXTURE_2D, texture_id5); //ロゴのテクスチャの設定を適用
		draw_logo();//ロゴの描画


		glDisable(GL_TEXTURE_2D);//テクスチャ設定をはずす

		glEnable(GL_LIGHTING);//光源処理を適用
		//タイトル画面での回転する自機
		glPushMatrix();//行列スタックをプッシュ
		glTranslatef(0,-0.2,-1.0);
		glRotatef(-90,1,0,0);
		glRotatef(0.005*autorotate*180/pi,0,0,1);
		glTranslatef(0,0.0,-0.8);
		draw_jiki(autorotate);//自機の描画
		glPopMatrix();//行列スタックをポップ

		glDisable(GL_LIGHTING);//光源処理をはずす
	}


	else if(scene==1){

		Vector target=enemy[targetnum];//ターゲットを設定
		GLfloat d=2;//カメラと自機のずらし距離
		Vector r=target-jiki;//自機から標的までのベクトル
		GLfloat h=r.Magnitude();//自機と標的の距離
		r.Normalize();//rを正規化

		Vector ue(0,0,1.0);//カメラに対し上方向となるベクトル

		glClear(GL_COLOR_BUFFER_BIT);
		glPushMatrix();//行列スタックをプッシュ

		glEnable(GL_TEXTURE_2D);//テクスチャ設定を再適用

		//////////////////////////天球
		glPushMatrix();//行列スタックをプッシュ
		glDisable(GL_BLEND);//混合処理をはずす
		glBindTexture(GL_TEXTURE_2D, texture_id1); //空のテクスチャの設定を適用
		glRotatef(90,1,0,0);
		glRotatef(-jiki.theta*180/pi,0,0,1);
		draw_sphere(72.0);//天球の描画、半径は72
		glEnable(GL_BLEND);//混合処理を再適用
		glPopMatrix();//行列スタックをポップ
		//////////////////////////////

		if(lockon){
			//ロックオン時はキー操作によってカメラが左右にずれる
			gluLookAt(jiki.x-r.x*d-(r^ue).x*jikiLR/20,jiki.y-r.y*d-(r^ue).y*jikiLR/20,0.5+10/h,jiki.x+sin(jiki.theta),jiki.y+cos(jiki.theta),height,0.0,0.0,1.0);
			jiki.theta=atan2((target.x-jiki.x),(target.y-jiki.y));
		}
		else{
			gluLookAt(jiki.x-sin(jiki.theta)*d,jiki.y-cos(jiki.theta)*d,height,jiki.x+sin(jiki.theta),jiki.y+cos(jiki.theta),height,0.0,0.0,1.0);
		}


		glEnable(GL_TEXTURE_2D);//テクスチャ設定を再適用


		//////////////////////////天体の描画
		glDisable(GL_BLEND);//混合処理をはずす

		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

		glPushMatrix();//行列スタックをプッシュ
		glTranslatef(-15,30,-12);
		glBindTexture(GL_TEXTURE_2D, texture_id7); //空のテクスチャの設定を適用
		draw_sphere(10.0);//天体の描画
		glPopMatrix();//行列スタックをポップ

		glPushMatrix();//行列スタックをプッシュ
		glTranslatef(5,-20,-4);
		glBindTexture(GL_TEXTURE_2D, texture_id6); //空のテクスチャの設定を適用
		draw_sphere(2.0);//天体の描画
		glPopMatrix();//行列スタックをポップ

		glEnable(GL_BLEND);//混合処理を再適用
		glDepthMask(GL_FALSE);
		////////////////////////////////

		glDisable(GL_TEXTURE_2D);//テクスチャ設定をはずす

		draw_yuka();//箱を描画

		///////////////////////////敵の描画
		glEnable(GL_LIGHTING);//光源処理を再適用
		for(int i=0;i<enemy_num;i++){
			if(enemy[i].exist){
				glPushMatrix();//行列スタックをプッシュ
				glTranslatef(enemy[i].x, enemy[i].y, enemy[i].z);
				draw_enemy(autorotate);//敵の描画
				glPopMatrix();//行列スタックをポップ
			}
		}
		glDisable(GL_LIGHTING);//光源処理をはずす
		glEnable(GL_TEXTURE_2D);//テクスチャ設定を再適用
		///////////////////////////////////


		///////////////////////爆発エフェクトの描画
		glBindTexture(GL_TEXTURE_2D, texture_id4);
		for(int i=0;i<10;i++){
			if(explosion[i].exist){
				glPushMatrix();//行列スタックをプッシュ
				glTranslatef(explosion[i].x, explosion[i].y, explosion[i].z);
				draw_explosion(explosion[i].counter);
				glPopMatrix();//行列スタックをポップ
			}
		}
		////////////////////////////////////

		glDisable(GL_TEXTURE_2D);//テクスチャ設定をはずす
		glEnable(GL_LIGHTING);//光源処理を再適用

		//////////////////////ミサイルの描画
		for(int i=0;i<10;i++){
			if(missile[i].exist){
				glPushMatrix();//行列スタックをプッシュ
				glTranslatef(missile[i].x, missile[i].y, missile[i].z);
				glRotatef(90,-cos(missile[i].theta),sin(missile[i].theta),0);
				draw_missile(autorotate,false);
				glPopMatrix();//行列スタックをポップ
			}
		}
		for(int i=0;i<enemy_num*10;i++){
			if(enemy_missile[i].exist){
				glPushMatrix();//行列スタックをプッシュ
				glTranslatef(enemy_missile[i].x, enemy_missile[i].y, enemy_missile[i].z);
				glRotatef(90,-cos(enemy_missile[i].theta),sin(enemy_missile[i].theta),0);
				draw_missile(autorotate,true);
				glPopMatrix();//行列スタックをポップ
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

		///////////////////////自機の描画
		glPushMatrix();//行列スタックをプッシュ
		glTranslatef(jiki.x, jiki.y, 0.0);
		glRotatef(-jiki.theta*180/pi+180,0,0,1);
		glRotatef(jikiLR,0,1,0);
		draw_jiki(autorotate);
		glPopMatrix();//行列スタックをポップ
		////////////////////////////////

		glPopMatrix();//行列スタックをポップ、ここで画面一番手前の描画順に移動できる

		glEnable(GL_TEXTURE_2D);//テクスチャ設定を再適用
		glDisable(GL_LIGHTING);//光源処理をはずす

		//ここからHUDの描画
		glPushMatrix();//行列スタックをプッシュ
		glTranslatef(0,0,-2);
		if(lockon){

			///////////////////////照準の描画
			glPushMatrix();//行列スタックをプッシュ
			glBindTexture(GL_TEXTURE_2D, texture_id3); //マップのテクスチャの設定を適用
			glTranslatef(-jikiLR/30,-h/200+0.1,0);
			draw_sight();

			glBindTexture(GL_TEXTURE_2D, texture_id11); //数字のテクスチャの設定を適用
			glPushMatrix();//行列スタックをプッシュ
			glTranslatef(0.25,0.15,0);
			draw_number((int)h,0.2,3);//ターゲットとの距離を描画
			glPopMatrix();//行列スタックをポップ

			glPushMatrix();//行列スタックをプッシュ
			glTranslatef(0,0.32,0);
			draw_number(targetnum+1,0.4,1);//ターゲットの敵番号を描画
			glPopMatrix();//行列スタックをポップ

			glPopMatrix();//行列スタックをポップ
			/////////////////////////////////////
		}

		//////////////////////エリア端のアラート描画
		if(jiki.x>40||jiki.y>40||jiki.x<-40||jiki.y<-40){
			if(autorotate%20!=0){
				glPushMatrix();//行列スタックをプッシュ
				glTranslatef(0,0.08,0);
				glBindTexture(GL_TEXTURE_2D, texture_id9); //アラートのテクスチャの設定を適用
				draw_alert();
				glPopMatrix();//行列スタックをポップ
			}
		}
		////////////////////////////////////////

		///////////////////////ミサイルが近づいてきたときのアラートの描画
		GLfloat dist=100;
		for(int i=0;i<enemy_num*10;i++){
			if(dist>(enemy_missile[i]-jiki).Magnitude())	dist=(enemy_missile[i]-jiki).Magnitude();
		}
		if(dist<8.0&&autorotate%((int)dist*2+1)!=0){
			glPushMatrix();//行列スタックをプッシュ
			glTranslatef(0,-0.05,0);
			glBindTexture(GL_TEXTURE_2D, texture_id8); //アラートのテクスチャの設定を適用
			draw_alert();
			glPopMatrix();//行列スタックをポップ
		}
		///////////////////////////////////////////

		/////////////////////////////ゲームクリア画面
		if(game_clear){
			glPushMatrix();//行列スタックをプッシュ
			glTranslatef(0,-0.2,0);
			glBindTexture(GL_TEXTURE_2D, texture_id12); //アラートのテクスチャの設定を適用
			draw_game_clear();
			glPopMatrix();//行列スタックをポップ
		}
		///////////////////////////////////////////

		///////////////////////////ゲームオーバー画面
		if(game_over){
			glPushMatrix();//行列スタックをプッシュ
			glTranslatef(0,0.12,0);
			glBindTexture(GL_TEXTURE_2D, texture_id14); //アラートのテクスチャの設定を適用
			draw_game_clear();
			glPopMatrix();//行列スタックをポップ
		}
		//////////////////////////////////////////////

		/////////////////////////HPの描画
		glPushMatrix();//行列スタックをプッシュ
		if(jiki.counter>3)glBindTexture(GL_TEXTURE_2D, texture_id10);
		else glBindTexture(GL_TEXTURE_2D, texture_id11);//体力が残り少ないと赤色になる
		glTranslatef(0.5,0.3,0.7);
		glRotatef(-30,0,1,0);
		if(!game_over)draw_number(jiki.counter*10,1.0,3);
		else draw_number(0,1.0,3);//体力がなくなったら0を表示
		glTranslatef(0.2,-0.05,0);
		glBindTexture(GL_TEXTURE_2D, texture_id13); 
		draw_percent();
		glPopMatrix();//行列スタックをポップ
		///////////////////////////////////

		////////////////////////////マップの表示
		glPushMatrix();//行列スタックをプッシュ
		glBindTexture(GL_TEXTURE_2D, texture_id2); 
		glTranslatef(0,0,-0.7);
		glRotatef(30,0,1,0);
		draw_map(jiki,missile,enemy,enemy_missile,targetnum,enemy_num);//途中でテクスチャー設定解除
		glPopMatrix();//行列スタックをポップ
		///////////////////////////////////////////////

		glPopMatrix();//行列スタックをポップ
		glDepthMask(GL_TRUE);
	}

	glDisable(GL_LIGHTING);//光源処理をはずす

	glFlush();//それまでの命令を処理

	glDisable(GL_BLEND);//混合処理をはずす


	glutSwapBuffers();//バッファの入れ替え
}
void target_move(void)//敵の移動処理
{
	//敵は初めに決めた角度に対して壁に跳ね返りながら移動する
	for(int i=0;i<enemy_num;i++){
		if(enemy[i].x>30||enemy[i].x<-30)vx[i]*=(-1);
		if(enemy[i].y>30||enemy[i].y<-30)vy[i]*=(-1);
		enemy[i].x+=vx[i];
		enemy[i].y+=vy[i];

		if(autorotate%100==0){
			enemy_fire[i]=true;//一定時間ごとに攻撃する
		}
	}
}
void hit_effect(void)//爆発エフェクト処理
{
	for(int i=0;i<10;i++){
		if(explosion[i].exist){
			explosion[i].counter+=1;
			if(explosion[i].counter>15)//爆発アニメーションが終わったら
			{
				explosion[i].exist=false;//爆発を消す
				explosion[i].counter=0;
			}
		}
	}
}
void missile_move()//自機のミサイルの挙動
{
	Vector attacker=jiki;
	for(int i=0;i<10;i++){

		Vector m=enemy[targetnum]-missile[i];
		Vector v=missile[i];
		m.Normalize();

		//ミサイル発射時の設定
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
			missile[i].theta+=fai;//ミサイルから見た標的への角度に曲げる
			missile[i].x+=m.x*speed*1.3;
			missile[i].y+=m.y*speed*1.3;

			missile[i].counter++;

			for(int j=0;j<enemy_num;j++){
				if((enemy[j]-missile[i]).Magnitude()<1.5){//ミサイルと標的が近づいたら
					if(enemy[j].counter==0)enemy[j].exist=false;
					enemy[j].counter-=1;
					explosion[i].exist=true;//爆発が起きる
					explosion[i].x=missile[i].x;
					explosion[i].y=missile[i].y;
					missile[i].exist=false;	
				}
			}
		}
		else{//何に当たらず飛び続けたときの処理
			missile[i].x=100;
			missile[i].y=100;
			missile[i].counter=0;
			missile[i].exist=false;
		}
	}
}
void enemy_missile_move()//敵機のミサイルの挙動
{
	for(int n=0;n<enemy_num;n++){
		Vector attacker=enemy[n];
		for(int i=0;i<10;i++){
			Vector m=jiki-enemy_missile[i+10*n];
			Vector v=enemy_missile[i+10*n];
			m.Normalize();

			//ミサイル発射時の設定
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
				enemy_missile[i+10*n].theta+=fai;//ミサイルから見た標的への角度に曲げる
				enemy_missile[i+10*n].x+=m.x*speed*0.5;
				enemy_missile[i+10*n].y+=m.y*speed*0.5;
				enemy_missile[i+10*n].counter++;

				if((jiki-enemy_missile[i+10*n]).Magnitude()<1.5){//ミサイルと標的が近づいたら
					jiki.counter-=1;
					explosion[i].exist=true;//爆発が起きる
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

void key_move(void){//キー操作

	if(forward){
		jiki.y+=speed*cos(jiki.theta);
		jiki.x+=speed*sin(jiki.theta);

		GLfloat dist=100;
		for(int i=0;i<enemy_num;i++){
			if(dist>(enemy[i]-jiki).Magnitude())dist=(enemy[i]-jiki).Magnitude();
		}

		if(dist<1||jiki.x>50||jiki.y>50||jiki.x<-50||jiki.y<-50){//敵や壁にめり込まないための処理
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

		if(dist<1||jiki.x>50||jiki.y>50||jiki.x<-50||jiki.y<-50){//敵や壁にめり込まないための処理
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

		if(dist<1||jiki.x>50||jiki.y>50||jiki.x<-50||jiki.y<-50){//敵や壁にめり込まないための処理
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

		if(dist<1||jiki.x>50||jiki.y>50||jiki.x<-50||jiki.y<-50){//敵や壁にめり込まないための処理
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
void key_down(unsigned char key, int x, int y)//キーボードイベント
{
	if(key=='q')targetnum=(targetnum+9)%10;

	// wキー：前進
	if(key=='w')forward=true;
	// aキー：左
	if(key=='a')left=true;
	// sキー：後進
	if(key=='s')backward=true;
	// xキー：右
	if(key=='d')right=true;

	// fキー：ロックオン切り替え
	if(key=='f'){ 
		if(!lockon&&!game_clear)lockon=true;
		else {
			lockon=false;
		}
	}
	//スペースキー：攻撃
	if(key==' '){
		if(lockon)if(!fire)fire=true;
	}

	// Escキー：強制終了
	if(key==27){
		exit(0);
	}

	if(key==13){//ゲームスタート
		scene=(scene+=1)%2;
	}

}
void key_up(unsigned char key, int x, int y)//キーボードイベント
{
	if(key=='w')forward=false;

	if(key=='a')left=seeleft=false;

	if(key=='s')backward=false;

	if(key=='d')right=seeright=false;
}

void target_change(){
	int gekiha=0;
	for(int i=0;i<enemy_num;i++){
		if(!enemy[targetnum].exist){//今標的としている敵が破壊されたら
			targetnum=(targetnum+1)%enemy_num;//次の存在している標的に切り替える
			gekiha++;
		}
		else{
			break;
		}
	}
	if(gekiha==enemy_num){//敵を全て破壊したら
		game_clear=true;//ゲームクリア
		lockon=false;
	}

	if(!game_clear){
		if(next||prev){//ロックオン中に左右キーが押されたら
			//次の存在している標的まで標的番号を増やす（減らす）
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