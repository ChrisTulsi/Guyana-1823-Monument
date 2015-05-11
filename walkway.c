#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <math.h>
#include <GL/glext.h>
#include <stdio.h>
#include <stdlib.h>
#include "walkway.h"
#include "texture.h"
#include "stand.h"

void walkway(){

	glPushMatrix();
	glColor3f(1,1,1);
	stand();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(10,0,0);
	stand();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(20,0,0);
	stand();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(30,0,0);
	stand();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(40,0,0);
	stand();
	glPopMatrix();


}
