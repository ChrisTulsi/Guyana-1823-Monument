#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <math.h>
#include <GL/glext.h>
#include <stdio.h>
#include <stdlib.h>
#include "tile.h"
#include "texture.h"

void loadtileimage(){

  tiletexture = LoadTexture("/home/chris/Desktop/tile.bmp", 1, 2048, 2048);  //BACK
}

void tile(){

	// Enable/Disable features
	glPushAttrib(GL_ENABLE_BIT);
	glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, tiletexture);
  GLUquadricObj *quadratic;
  quadratic=gluNewQuadric();			// Create A Pointer To The Quadric Object ( NEW )
  gluQuadricNormals(quadratic, GLU_SMOOTH);	// Create Smooth Normals ( NEW )
  gluQuadricTexture(quadratic, GL_TRUE);		// Create Texture Coords ( NEW )
  gluCylinder(quadratic/*quad*/,1.0/*base*/,20.0/*top*/,0.5/*height*/,100 /*slices*/,1/*stacks*/);

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
