#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <math.h>
#include <GL/glext.h>
#include <stdio.h>
#include <stdlib.h>
#include "seawall.h"
#include "texture.h"

void loadseawallimage(){

	walltexture[0] = LoadTexture("/home/chris/Desktop/seawall.bmp", 1, 2048, 2048);  //BACK
  walltexture[1] = LoadTexture("/home/chris/Desktop/seawall.bmp", 1, 2048, 2048); //FRONT
  walltexture[2] = LoadTexture("/home/chris/Desktop/seawall.bmp", 1, 2048, 2048);  //RIGHT
  walltexture[3] = LoadTexture("/home/chris/Desktop/seawall.bmp", 1, 2048, 2048); //LEFT
  walltexture[4] = LoadTexture("/home/chris/Desktop/seawall.bmp", 1, 2048, 2048);  //DOWN
  walltexture[5] = LoadTexture("/home/chris/Desktop/seawall.bmp", 1, 2048, 2048);    //UP

}

void seawall(){

	// Enable/Disable features
	glPushAttrib(GL_ENABLE_BIT);
	glEnable(GL_TEXTURE_2D);

	// Bind the BACK texture of the sky map to the BACK side of the cube
	glBindTexture(GL_TEXTURE_2D, walltexture[0]);
	glBegin(GL_QUADS);
			glNormal3f(0,0,1);
			glTexCoord2f(500.0f, 0.0f); glVertex3f(-5, -5, 1000);
			glTexCoord2f(500.0f, 10.0f); glVertex3f(-5, 5, 1000);
			glTexCoord2f(0.0f, 10.0f); glVertex3f(5, 5, 1000);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(5, -5, 1000);
	glEnd();

	//FRONT
	glBindTexture(GL_TEXTURE_2D, walltexture[1]);
	glBegin(GL_QUADS);
			glNormal3f(0,0,-1);
			glTexCoord2f(500.0f, 0.0f); glVertex3f(5, -5, -1000);
			glTexCoord2f(500.0f, 10.0f); glVertex3f(5, 5, -1000);
			glTexCoord2f(0.0f, 10.0f); glVertex3f(-5, 5, -1000);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-5, -5, -1000);
	glEnd();

	//BOTTOM
	glBindTexture(GL_TEXTURE_2D, walltexture[4]);
	glBegin(GL_QUADS);
			glNormal3f(0,-1,0);
			glTexCoord2f(500.0f, 0.0f); glVertex3f(5, -5, -1000);
			glTexCoord2f(500.0f, 10.0f); glVertex3f(5, -5, 1000);
			glTexCoord2f(0.0f, 10.0f); glVertex3f(-5, -5, 1000);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-5, -5, -1000);
	glEnd();

	//TOP
	glBindTexture(GL_TEXTURE_2D, walltexture[5]);
	glBegin(GL_QUADS);
			glNormal3f(0,1,0);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-5, 5, 1000);
			glTexCoord2f(500.0f, 0.0f); glVertex3f(-5, 5, -1000);
			glTexCoord2f(500.0f, 10.0f); glVertex3f(5, 5, -1000);
			glTexCoord2f(0.0f, 10.0f); glVertex3f(5, 5, 1000);
	glEnd();

	//LEFT
	glBindTexture(GL_TEXTURE_2D, walltexture[2]);
	glBegin(GL_QUADS);
			glNormal3f(-1,0,0);
			glTexCoord2f(500.0f, 10.0f); glVertex3f(-5, 5, -1000);
			glTexCoord2f(0.0f, 10.0f); glVertex3f(-5, 5, 1000);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-5, -5, 1000);
			glTexCoord2f(500.0f, 0.0f); glVertex3f(-5, -5, -1000);
	glEnd();

	//RIGHT
	glBindTexture(GL_TEXTURE_2D, walltexture[3]);
	glBegin(GL_QUADS);
			glNormal3f(1,0,0);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(5, -5, -1000);
			glTexCoord2f(500.0f, 0.0f); glVertex3f(5, -5, 1000);
			glTexCoord2f(500.0f, 10.0f); glVertex3f(5, 5, 1000);
			glTexCoord2f(0.0f, 10.0f); glVertex3f(5, 5, -1000);
	glEnd();

	glPopAttrib();
	glDisable( GL_TEXTURE_2D );
  //Reset and transform the matrix.
  glLoadIdentity();

}
