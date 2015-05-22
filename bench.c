#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <math.h>
#include <GL/glext.h>
#include <stdio.h>
#include <stdlib.h>
#include "bench.h"
#include "texture.h"

void loadbenchimage(){

  benchtexture = LoadTexture("/home/chris/Desktop/images/whitepaint.bmp", 0, 2048, 2048);  //BACK
}

void benchcube(){

  // Enable/Disable features
	glPushAttrib(GL_ENABLE_BIT);
	glEnable(GL_TEXTURE_2D);

	// Bind the BACK texture of the sky map to the BACK side of the cube
	glBindTexture(GL_TEXTURE_2D, benchtexture);
	glBegin(GL_QUADS);
      glNormal3f(0,0,1);
      glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mColor);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(-1, -1, 1);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(-1, 1, 1);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(1, 1, 1);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(1, -1, 1);
	glEnd();

	//FRONT
	glBindTexture(GL_TEXTURE_2D, benchtexture);
	glBegin(GL_QUADS);
      glNormal3f(0,0,-1);
      glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mColor);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(1, -1, -1);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(1, 1, -1);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-1, 1, -1);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-1, -1, -1);
	glEnd();

	//BOTTOM
	glBindTexture(GL_TEXTURE_2D, benchtexture);
	glBegin(GL_QUADS);
      glNormal3f(0,-1,0);
      glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mColor);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(1, -1, -1);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(1, -1, 1);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-1, -1, 1);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-1, -1, -1);
	glEnd();

	//TOP
	glBindTexture(GL_TEXTURE_2D, benchtexture);
	glBegin(GL_QUADS);
      glNormal3f(0,1,0);
      glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mColor);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-1, 1, 1);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(-1, 1, -1);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(1, 1, -1);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(1, 1, 1);
	glEnd();

	//LEFT
	glBindTexture(GL_TEXTURE_2D, benchtexture);
	glBegin(GL_QUADS);
      glNormal3f(-1,0,0);
      glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mColor);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(-1, 1, -1);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-1, 1, 1);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-1, -1, 1);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(-1, -1, -1);
	glEnd();

	//RIGHT
	glBindTexture(GL_TEXTURE_2D, benchtexture);
	glBegin(GL_QUADS);
      glNormal3f(1,0,0);
      glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mColor);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(1, -1, -1);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(1, -1, 1);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(1, 1, 1);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(1, 1, -1);
	glEnd();

	glPopAttrib();
	glDisable( GL_TEXTURE_2D );
  //Reset and transform the matrix.
  glLoadIdentity();

}

void bench(){
  //top
  glPushMatrix();
  glTranslatef(0,1,0);
  glScalef(4,0.5,1);
  benchcube();
  glPopMatrix();
  //left
  glPushMatrix();
  glTranslatef(-3.0,0,0);
  glScalef(0.5,0.5,1);
  benchcube();
  glPopMatrix();
  //right
  glPushMatrix();
  glTranslatef(3.0,0,0);
  glScalef(0.5,0.5,1);
  benchcube();
  glPopMatrix();

}
