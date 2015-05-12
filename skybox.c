#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <math.h>
#include <GL/glext.h>
#include <stdio.h>
#include <stdlib.h>
#include "skybox.h"
#include "texture.h"

void loadskyimage(){

	skytexture[0] = LoadTexture("txStormydays_back.bmp", 0, 1024, 1024);  //BACK
  skytexture[1] = LoadTexture("txStormydays_front.bmp", 0, 1024, 1024); //FRONT
  skytexture[2] = LoadTexture("txStormydays_right.bmp", 0, 1024, 1024);  //RIGHT
  skytexture[3] = LoadTexture("txStormydays_left.bmp", 0, 1024, 1024); //LEFT
  skytexture[4] = LoadTexture("txStormydays_down.bmp", 0, 1024, 1024);  //DOWN
  skytexture[5] = LoadTexture("txStormydays_up.bmp", 0, 1024, 1024);    //UP

}

void SkyFrameWork(){

	// Enable/Disable features
	glPushAttrib(GL_ENABLE_BIT);
	glEnable(GL_TEXTURE_2D);

	// Bind the BACK texture of the sky map to the BACK side of the cube
	glBindTexture(GL_TEXTURE_2D, skytexture[0]);
	glBegin(GL_QUADS);
			glNormal3f(0,0,-1);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(-1, -1, 1);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(-1, 1, 1);
			glTexCoord2f(0.018f, 1.0f); glVertex3f(1, 1, 1);
			glTexCoord2f(0.018f, 0.018f); glVertex3f(1, -1, 1);
	glEnd();

	//FRONT
	glBindTexture(GL_TEXTURE_2D, skytexture[1]);
	glBegin(GL_QUADS);
			glNormal3f(0,0,1);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(1, -1, -1);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(1, 1, -1);
			glTexCoord2f(0.018f, 1.0f); glVertex3f(-1, 1, -1);
			glTexCoord2f(0.018f, 0.018f); glVertex3f(-1, -1, -1);
	glEnd();

	//BOTTOM
	glBindTexture(GL_TEXTURE_2D, skytexture[4]);
	glBegin(GL_QUADS);
			glNormal3f(0,1,0);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(1, -1, -1);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(1, -1, 1);
			glTexCoord2f(0.018f, 1.0f); glVertex3f(-1, -1, 1);
			glTexCoord2f(0.018f, 0.018f); glVertex3f(-1, -1, -1);
	glEnd();

	//TOP
	glBindTexture(GL_TEXTURE_2D, skytexture[5]);
	glBegin(GL_QUADS);
			glNormal3f(0,-1,0);
			glTexCoord2f(0.018f, 0.018f); glVertex3f(-1, 1, 1);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(-1, 1, -1);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(1, 1, -1);
			glTexCoord2f(0.018f, 1.0f); glVertex3f(1, 1, 1);
	glEnd();

	//LEFT
	glBindTexture(GL_TEXTURE_2D, skytexture[2]);
	glBegin(GL_QUADS);
			glNormal3f(-1,0,0);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(-1, 1, -1);
			glTexCoord2f(0.018f, 1.0f); glVertex3f(-1, 1, 1);
			glTexCoord2f(0.018f, 0.018f); glVertex3f(-1, -1, 1);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(-1, -1, -1);
	glEnd();

	//RIGHT
	glBindTexture(GL_TEXTURE_2D, skytexture[3]);
	glBegin(GL_QUADS);
			glNormal3f(-1,0,0);
			glTexCoord2f(0.018f, 0.018f); glVertex3f(1, -1, -1);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(1, -1, 1);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(1, 1, 1);
			glTexCoord2f(0.018f, 1.0f); glVertex3f(1, 1, -1);
	glEnd();

	glPopAttrib();
	glDisable( GL_TEXTURE_2D );
  //Reset and transform the matrix.
  glLoadIdentity();

}
