#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <math.h>
#include <GL/glext.h>
#include <stdio.h>
#include <stdlib.h>
#include "pedestal.h"
#include "texture.h"

void loadpedestalimage(){

  pedestaltexture[0] = LoadTexture("/home/chris/Desktop/images/concrete.bmp", 0, 2048, 2048);  //BACK
  pedestaltexture[1] = LoadTexture("/home/chris/Desktop/images/concrete_1823.bmp", 0, 2048, 2048);//front
  pedestaltexture[2] = LoadTexture("/home/chris/Desktop/images/concrete_left.bmp", 0, 2048, 2048);//left
  pedestaltexture[3] = LoadTexture("/home/chris/Desktop/images/concrete_right.bmp", 0, 2048, 2048);//right
}

void pedestal(){

	// Enable/Disable features
	glPushAttrib(GL_ENABLE_BIT);
	glEnable(GL_TEXTURE_2D);

	// Bind the BACK texture of the sky map to the BACK side of the cube
	glBindTexture(GL_TEXTURE_2D, pedestaltexture[0]);
	glBegin(GL_QUADS);
      glNormal3f(0,0,1);
      glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mColor);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(-1, -1, 1);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(-1, 1, 0.5);
			glTexCoord2f(0.018f, 1.0f); glVertex3f(1, 1, 0.5);
			glTexCoord2f(0.018f, 0.018f); glVertex3f(1, -1, 1);
	glEnd();

	//FRONT
	glBindTexture(GL_TEXTURE_2D, pedestaltexture[1]);
	glBegin(GL_QUADS);
      glNormal3f(0,0,-1);
      glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mColor);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(-1, -1, -1);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(-1, 1, -1);
			glTexCoord2f(0.018f, 1.0f); glVertex3f(1, 1, -1);
			glTexCoord2f(0.018f, 0.018f); glVertex3f(1, -1, -1);
	glEnd();

	//BOTTOM
	glBindTexture(GL_TEXTURE_2D, pedestaltexture[0]);
	glBegin(GL_QUADS);
      glNormal3f(0,-1,0);
      glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mColor);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(1, -1, -1);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(1, -1, 1);
			glTexCoord2f(0.018f, 1.0f); glVertex3f(-1, -1, 1);
			glTexCoord2f(0.018f, 0.018f); glVertex3f(-1, -1, -1);
	glEnd();

	//TOP
	glBindTexture(GL_TEXTURE_2D, pedestaltexture[0]);
	glBegin(GL_QUADS);
      glNormal3f(0,1,0);
      glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mColor);
			glTexCoord2f(0.018f, 0.018f); glVertex3f(-1, 1, 0.5);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(-1, 1, -1);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(1, 1, -1);
			glTexCoord2f(0.018f, 1.0f); glVertex3f(1, 1, 0.5);
	glEnd();

	//LEFT
	glBindTexture(GL_TEXTURE_2D, pedestaltexture[3]);
	glBegin(GL_QUADS);
      glNormal3f(-1,0,0);
      glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mColor);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(-1, 1, -1);
			glTexCoord2f(0.018f, 1.0f); glVertex3f(-1, 1, 0.5);
			glTexCoord2f(0.018f, 0.018f); glVertex3f(-1, -1, 1);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(-1, -1, -1);
	glEnd();

	//RIGHT
	glBindTexture(GL_TEXTURE_2D, pedestaltexture[2]);
	glBegin(GL_QUADS);
      glNormal3f(1,0,0);
      glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mColor);
			glTexCoord2f(0.018f, 0.018f); glVertex3f(1, -1, -1);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(1, -1, 1);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(1, 1, 0.5);
			glTexCoord2f(0.018f, 1.0f); glVertex3f(1, 1, -1);
	glEnd();

	glPopAttrib();
	glDisable( GL_TEXTURE_2D );
  //Reset and transform the matrix.
  glLoadIdentity();

}
