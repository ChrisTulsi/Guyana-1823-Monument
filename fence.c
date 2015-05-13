#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include "fence.h"

void loadfenceimage(){

	fencetexture = LoadTexture("/home/chris/Desktop/images/whitepaint.bmp", 0, 2048, 2048);
}

void fence(){

	glColor3f(1.0, 1.0, 1.0);
	glPushMatrix();
	glScalef(0.4,3,0.1);
	picket();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1,0,0);
	glScalef(0.4,3,0.1);
	glColor3f(1.0, 1.0, 1.0);
	picket();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1,0,0);
	glScalef(0.4,3,0.1);
	glColor3f(1.0, 1.0, 1.0);
	picket();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(2,0,0);
	glScalef(0.4,3,0.1);
	glColor3f(1.0, 1.0, 1.0);
	picket();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-2,0,0);
	glScalef(0.4,3,0.1);
	glColor3f(1.0, 1.0, 1.0);
	picket();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(3,0,0);
	glScalef(0.4,3,0.1);
	glColor3f(1.0, 1.0, 1.0);
	picket();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-3,0,0);
	glScalef(0.4,3,0.1);
	glColor3f(1.0, 1.0, 1.0);
	picket();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(4,0,0);
	glScalef(0.4,3,0.1);
	glColor3f(1.0, 1.0, 1.0);
	picket();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-4,0,0);
	glScalef(0.4,3,0.1);
	glColor3f(1.0, 1.0, 1.0);
	picket();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(5,0,0);
	glScalef(0.4,3,0.1);
	glColor3f(1.0, 1.0, 1.0);
	picket();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-5,0,0);
	glScalef(0.4,3,0.1);
	glColor3f(1.0, 1.0, 1.0);
	picket();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(6,0,0);
	glScalef(0.4,3,0.1);
	glColor3f(1.0, 1.0, 1.0);
	picket();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-6,0,0);
	glScalef(0.4,3,0.1);
	glColor3f(1.0, 1.0, 1.0);
	picket();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(7,0,0);
	glScalef(0.4,3,0.1);
	glColor3f(1.0, 1.0, 1.0);
	picket();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-7,0,0);
	glScalef(0.4,3,0.1);
	glColor3f(1.0, 1.0, 1.0);
	picket();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-8,0,0);
	glScalef(0.4,3,0.1);
	glColor3f(1.0, 1.0, 1.0);
	picket();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-9,0,0);
	glScalef(0.4,3,0.1);
	glColor3f(1.0, 1.0, 1.0);
	picket();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-10,0,0);
	glScalef(0.4,3,0.1);
	glColor3f(1.0, 1.0, 1.0);
	picket();
	glPopMatrix();

	//pole
	glPushMatrix();
	glTranslatef(8,0,-0.4);
	glScalef(0.4,3,0.4);
	glColor3f(1.0, 1.0, 1.0);
	picket();
	glPopMatrix();

	//top rails
	glPushMatrix();
	glTranslatef(-1.5,1,0.1);
	glScalef(10,0.4,0.1);
	glColor3f(1.0, 1.0, 1.0);
	picket();
	glPopMatrix();

	//bottom rail
	glPushMatrix();
	glTranslatef(-1.5, -1, 0.1);
	glScalef(10,0.4,0.1);
	glColor3f(1.0, 1.0, 1.0);
	picket();
	glPopMatrix();
}

void picket(){

	// Enable/Disable features
	glPushAttrib(GL_ENABLE_BIT);
	glEnable(GL_TEXTURE_2D);

	// Bind the BACK texture of the sky map to the BACK side of the cube
	glBindTexture(GL_TEXTURE_2D, fencetexture);

	glBegin(GL_QUADS);
			glNormal3f(0,0,1);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(-1, -1, 1);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(-1, 1, 1);
			glTexCoord2f(0.0, 1.0f); glVertex3f(1, 1, 1);
			glTexCoord2f(0.0, 0.0); glVertex3f(1, -1, 1);
	glEnd();

	//FRONT
	glBindTexture(GL_TEXTURE_2D, fencetexture);
	glBegin(GL_QUADS);
			glNormal3f(0,0,-1);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(1, -1, -1);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(1, 1, -1);
			glTexCoord2f(0.0, 1.0f); glVertex3f(-1, 1, -1);
			glTexCoord2f(0.0, 0.0); glVertex3f(-1, -1, -1);
	glEnd();

	//BOTTOM
	glBindTexture(GL_TEXTURE_2D, fencetexture);
	glBegin(GL_QUADS);
			glNormal3f(0,-1,0);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(1, -1, -1);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(1, -1, 1);
			glTexCoord2f(0.0, 1.0f); glVertex3f(-1, -1, 1);
			glTexCoord2f(0.0, 0.0); glVertex3f(-1, -1, -1);
	glEnd();

	//TOP
	glBindTexture(GL_TEXTURE_2D, fencetexture);
	glBegin(GL_QUADS);
			glNormal3f(0,1,0);
			glTexCoord2f(0.0, 0.0); glVertex3f(-1, 1, 1);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(-1, 1, -1);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(1, 1, -1);
			glTexCoord2f(0.0, 1.0f); glVertex3f(1, 1, 1);
	glEnd();

	//LEFT
	glBindTexture(GL_TEXTURE_2D, fencetexture);
	glBegin(GL_QUADS);
			glNormal3f(-1,0,0);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(-1, 1, -1);
			glTexCoord2f(0.0, 1.0f); glVertex3f(-1, 1, 1);
			glTexCoord2f(0.0, 0.0); glVertex3f(-1, -1, 1);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(-1, -1, -1);
	glEnd();

	//RIGHT
	glBindTexture(GL_TEXTURE_2D, fencetexture);
	glBegin(GL_QUADS);
			glNormal3f(1,0,0);
			glTexCoord2f(0.0, 0.0); glVertex3f(1, -1, -1);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(1, -1, 1);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(1, 1, 1);
			glTexCoord2f(0.0, 1.0f); glVertex3f(1, 1, -1);
	glEnd();

	glPopAttrib();
	glDisable( GL_TEXTURE_2D );
  //Reset and transform the matrix.
  glLoadIdentity();


}
