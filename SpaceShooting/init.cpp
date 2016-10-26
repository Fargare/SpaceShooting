#include<windows.h>
#include<GL/gl.h>
#include<GL/glu.h> 


void gl_init(void)
{

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glEnable(GL_DEPTH_TEST);
}

void lighting_init(void)
{
	static GLfloat position[] = {-10.0, 10.0, 10.0, 1.0};
	static GLfloat ambient[] = {0.3, 0.3, 0.3, 1.0};
	static GLfloat diffuse[] = {0.4, 0.4, 0.4, 1.0};
	static GLfloat specular[] = {1.0, 1.0, 1.0, 1.0};

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_POSITION, position);

	glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);


	glEnable(GL_LIGHT0);
}