#include "vector.h"

void draw_yuka(void);
void draw_enemy(int r);
void draw_missile(int r,bool e);
void draw_jiki(int r);
void draw_explosion(GLint r);
void draw_sphere(GLfloat dist);
void draw_map(Vector jiki,Vector missile[],Vector enemy[],Vector enemy_missile[],int targetnum,int enemy_num);
void draw_sight(void);
void draw_logo(void);
void draw_alert(void);
void draw_number(int n,double d,int keta);
void draw_game_clear(void);
void draw_percent(void);