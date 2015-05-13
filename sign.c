#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <math.h>
#include <GL/glext.h>
#include <stdio.h>
#include <stdlib.h>
#include "sign.h"
#include "texture.h"

void loadsignimage(){

  signtexture = LoadTexture("/home/chris/Desktop/images/sign.bmp", 0, 2048, 2048);  //BACK
  blocktexture = LoadTexture("/home/chris/Desktop/images/concrete.bmp", 0, 2048, 2048);
}

void sign(){

  //block
	glPushMatrix();
	glColor3f(1,1,1);
	glTranslatef(-3,-4,0);
	block();
	glPopMatrix();

  //block
  glPushMatrix();
  glColor3f(1,1,1);
  glTranslatef(3,-4,0);
  block();
  glPopMatrix();

  //pole
  glPushMatrix();
  glColor3f(1,1,1);
  glTranslatef(-3,8,0);
  glScalef(1,3,1);
  glRotatef(90,1,0,0);
  pole();
  glPopMatrix();


  //pole
  glPushMatrix();
  glColor3f(1,1,1);
  glTranslatef(3,8,0);
  glScalef(1,3,1);
  glRotatef(90,1,0,0);
  pole();
  glPopMatrix();

  //sign
  glPushMatrix();
  glColor3f(1,1,1);
  glTranslatef(0,6,-1);
  glScalef(3,2,1);
  board();
  glPopMatrix();
}

void block(){

	// Enable/Disable features
	glPushAttrib(GL_ENABLE_BIT);
	glEnable(GL_TEXTURE_2D);

	// Bind the BACK texture of the sky map to the BACK side of the cube
	glBindTexture(GL_TEXTURE_2D, blocktexture);
	glBegin(GL_QUADS);
      glNormal3f(0,0,1);
			glTexCoord2f(1.0f, 0.0f);      glVertex3f(-1, -1, 1);
			glTexCoord2f(1.0f, 1.0f);      glVertex3f(-1, 1, 1);
			glTexCoord2f(0.018f, 1.0f);    glVertex3f(1, 1, 1);
			glTexCoord2f(0.018f, 0.018f);  glVertex3f(1, -1, 1);
	glEnd();

	//FRONT
	glBindTexture(GL_TEXTURE_2D, blocktexture);
	glBegin(GL_QUADS);
    glNormal3f(0,0,-1);
			glTexCoord2f(1.0f, 0.0f);      glVertex3f(1, -1, -1);
			glTexCoord2f(1.0f, 1.0f);      glVertex3f(1, 1, -1);
			glTexCoord2f(0.018f, 1.0f);    glVertex3f(-1, 1, -1);
			glTexCoord2f(0.018f, 0.018f);  glVertex3f(-1, -1, -1);
	glEnd();

	//BOTTOM
	glBindTexture(GL_TEXTURE_2D, blocktexture);
	glBegin(GL_QUADS);
      glNormal3f(0,-1,0);
			glTexCoord2f(1.0f, 0.0f);      glVertex3f(1, -1, -1);
			glTexCoord2f(1.0f, 1.0f);      glVertex3f(1, -1, 1);
			glTexCoord2f(0.018f, 1.0f);    glVertex3f(-1, -1, 1);
			glTexCoord2f(0.018f, 0.018f);  glVertex3f(-1, -1, -1);
	glEnd();

	//TOP
	glBindTexture(GL_TEXTURE_2D, blocktexture);
	glBegin(GL_QUADS);
      glNormal3f(0,1,0);
			glTexCoord2f(0.018f, 0.018f); glVertex3f(-1, 1, 1);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(-1, 1, -1);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(1, 1, -1);
			glTexCoord2f(0.018f, 1.0f); glVertex3f(1, 1, 1);
	glEnd();

	//LEFT
	glBindTexture(GL_TEXTURE_2D, blocktexture);
	glBegin(GL_QUADS);
      glNormal3f(-1,0,0);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(-1, 1, -1);
			glTexCoord2f(0.018f, 1.0f); glVertex3f(-1, 1, 1);
			glTexCoord2f(0.018f, 0.018f); glVertex3f(-1, -1, 1);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(-1, -1, -1);
	glEnd();

	//RIGHT
	glBindTexture(GL_TEXTURE_2D, blocktexture);
	glBegin(GL_QUADS);
      glNormal3f(1,0,0);
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

void pole(){

  // Enable/Disable features
	glPushAttrib(GL_ENABLE_BIT);
	glEnable(GL_TEXTURE_2D);
  GLUquadricObj *quadratic;
  quadratic=gluNewQuadric();			// Create A Pointer To The Quadric Object ( NEW )
  gluQuadricNormals(quadratic, GLU_SMOOTH);	// Create Smooth Normals ( NEW )
  gluQuadricTexture(quadratic, GL_TRUE);		// Create Texture Coords ( NEW )
  gluCylinder(quadratic/*quad*/,0.1/*base*/,0.1/*top*/,4.0/*height*/,60 /*slices*/,1/*stacks*/);

  glTranslatef(0.0,0.0,3.5);
  GLUquadricObj *quadraticBase;
  quadraticBase=gluNewQuadric();			// Create A Pointer To The Quadric Object ( NEW )
  gluQuadricNormals(quadraticBase, GLU_SMOOTH);	// Create Smooth Normals ( NEW )
  gluQuadricTexture(quadraticBase, GL_TRUE);		// Create Texture Coords ( NEW )
  //gluCylinder(quadraticBase/*quad*/,6.5/*base*/,6.5/*top*/,1.0/*height*/,60 /*slices*/,1/*stacks*/);

	glPopAttrib();
	glDisable( GL_TEXTURE_2D );
  //Reset and transform the matrix.
  glLoadIdentity();


}

void board(){

	// Enable/Disable features
	glPushAttrib(GL_ENABLE_BIT);
	glEnable(GL_TEXTURE_2D);

	// Bind the BACK texture of the sky map to the BACK side of the cube
	glBindTexture(GL_TEXTURE_2D, signtexture);
	glBegin(GL_QUADS);
      glNormal3f(0,0,1);
			glTexCoord2f(1.0f, 0.0f);      glVertex3f(-1, -1, 1);
			glTexCoord2f(1.0f, 1.0f);      glVertex3f(-1, 1, 1);
			glTexCoord2f(0.018f, 1.0f);    glVertex3f(1, 1, 1);
			glTexCoord2f(0.018f, 0.018f);  glVertex3f(1, -1, 1);
	glEnd();

	glPopAttrib();
	glDisable( GL_TEXTURE_2D );
  //Reset and transform the matrix.
  glLoadIdentity();

}
