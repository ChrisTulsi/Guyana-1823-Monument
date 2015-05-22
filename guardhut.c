#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <math.h>
#include <GL/glext.h>
#include <stdio.h>
#include <stdlib.h>
#include "guardhut.h"
#include "texture.h"


void loadguardhutimage(){
	guardhuttexture = LoadTexture("/home/chris/Desktop/images/concrete.bmp", 1, 2048, 2048);  //BACK
	windowtexture = LoadTexture("/home/chris/Desktop/images/window.bmp", 1, 2048, 2048);  //BACK
	rooftexture = LoadTexture("/home/chris/Desktop/images/roof.bmp", 1, 2048, 2048);  //BACK
}

void guardhut(){
  // Enable/Disable features
	glPushAttrib(GL_ENABLE_BIT);
	glEnable(GL_TEXTURE_2D);

	// Bind the BACK texture of the sky map to the BACK side of the cube
	glBindTexture(GL_TEXTURE_2D, guardhuttexture);
	glBegin(GL_QUADS);
			glNormal3f(0,0,1);
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mColor);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(-1, -1, 1);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(-1, 1, 1);
			glTexCoord2f(0.018f, 1.0f); glVertex3f(1, 1, 1);
			glTexCoord2f(0.018f, 0.018f); glVertex3f(1, -1, 1);
	glEnd();

	//FRONT
	glBindTexture(GL_TEXTURE_2D, guardhuttexture);
	glBegin(GL_QUADS);
			glNormal3f(0,0,-1);
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mColor);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(1, -1, -1);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(1, 1, -1);
			glTexCoord2f(0.018f, 1.0f); glVertex3f(-1, 1, -1);
			glTexCoord2f(0.018f, 0.018f); glVertex3f(-1, -1, -1);
	glEnd();

	//BOTTOM
	glBindTexture(GL_TEXTURE_2D, guardhuttexture);
	glBegin(GL_QUADS);
	    glNormal3f(0,-1,0);
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mColor);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(1, -1, -1);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(1, -1, 1);
			glTexCoord2f(0.018f, 1.0f); glVertex3f(-1, -1, 1);
			glTexCoord2f(0.018f, 0.018f); glVertex3f(-1, -1, -1);
	glEnd();

	//TOP
	glBindTexture(GL_TEXTURE_2D, guardhuttexture);
	glBegin(GL_QUADS);
	    glNormal3f(0,1,0);
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mColor);
			glTexCoord2f(0.018f, 0.018f); glVertex3f(-1, 1, 1);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(-1, 1, -1);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(1, 1, -1);
			glTexCoord2f(0.018f, 1.0f); glVertex3f(1, 1, 1);
	glEnd();

	//LEFT
	glBindTexture(GL_TEXTURE_2D, guardhuttexture);
	glBegin(GL_QUADS);
			glNormal3f(-1,0,0);
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mColor);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(-1, 1, -1);
			glTexCoord2f(0.018f, 1.0f); glVertex3f(-1, 1, 1);
			glTexCoord2f(0.018f, 0.018f); glVertex3f(-1, -1, 1);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(-1, -1, -1);
	glEnd();

	//RIGHT
	glBindTexture(GL_TEXTURE_2D, guardhuttexture);
	glBegin(GL_QUADS);
			glNormal3f(1,0,0);
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mColor);
			glTexCoord2f(0.018f, 0.018f); glVertex3f(1, -1, -1);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(1, -1, 1);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(1, 1, 1);
			glTexCoord2f(0.018f, 1.0f); glVertex3f(1, 1, -1);
	glEnd();

	//LEFTSide window
	glBindTexture(GL_TEXTURE_2D, windowtexture);
	glBegin(GL_QUADS);
			glNormal3f(-1,0,0);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, mColor);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.001, 0.8, -0.6);
			glTexCoord2f(0.018f, 1.0f); glVertex3f(-1.001, 0.8, 0.6);
			glTexCoord2f(0.018f, 0.018f); glVertex3f(-1.001, -0.4, 0.6);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.001, -0.4, -0.6);
	glEnd();

	//back window
	glBindTexture(GL_TEXTURE_2D, windowtexture);
	glBegin(GL_QUADS);
			glNormal3f(0,0,1);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, mColor);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.6, -0.4, 1.001);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.6, 0.8, 1.001);
			glTexCoord2f(0.018f, 1.0f); glVertex3f(0.6, 0.8, 1.001);
			glTexCoord2f(0.018f, 0.018f); glVertex3f(0.6, -0.4, 1.001);
	glEnd();

	//left roof
	glBindTexture(GL_TEXTURE_2D, rooftexture);
	glBegin(GL_QUADS);
			glNormal3f(-1,0,0);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, mColor);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(0, 2, -0.7);
			glTexCoord2f(0.018f, 1.0f); glVertex3f(0, 2, 0.7);
			glTexCoord2f(0.018f, 0.018f); glVertex3f(-1.5, 0.9, 1.5);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.5, 0.9, -1.5);
	glEnd();

	//RIGHT roof
	glBindTexture(GL_TEXTURE_2D, rooftexture);
	glBegin(GL_QUADS);
			glNormal3f(1,0,0);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, mColor);
			glTexCoord2f(0.018f, 0.018f); glVertex3f(1.5, 0.9, -1.5);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(1.5, 0.9, 1.5);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(0, 2, 0.7);
			glTexCoord2f(0.018f, 1.0f); glVertex3f(0, 2, -0.7);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, rooftexture);
	glBegin(GL_TRIANGLES);
			glNormal3f(0,0,1);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, mColor);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.5, 0.9, 1.5);
			glTexCoord2f(0.5f, 1.0f); glVertex3f(0, 2, 0.7);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(1.5, 0.9, 1.5);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, rooftexture);
	glBegin(GL_TRIANGLES);
			glNormal3f(0,0,-1);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, mColor);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.5, 0.9, -1.5);
			glTexCoord2f(0.5f, 1.0f); glVertex3f(0, 2, -0.7);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(1.5, 0.9, -1.5);
	glEnd();

	glPopAttrib();
	glDisable( GL_TEXTURE_2D );
  //Reset and transform the matrix.
  glLoadIdentity();
}
