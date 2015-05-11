#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <math.h>
#include <GL/glext.h>
#include <stdio.h>
#include <stdlib.h>
#include "circleplatform.h"
#include "texture.h"

void loadcircleplatformimage(){

  circleplatformtexture = LoadTexture("/home/chris/Desktop/concrete.bmp", 0, 2048, 2048);  //BACK
}

void circleplatform(){

	// Enable/Disable features
	glPushAttrib(GL_ENABLE_BIT);
	glEnable(GL_TEXTURE_2D);

  GLUquadricObj *quadratic;
  quadratic=gluNewQuadric();			// Create A Pointer To The Quadric Object ( NEW )
  gluQuadricNormals(quadratic, GLU_SMOOTH);	// Create Smooth Normals ( NEW )
  gluQuadricTexture(quadratic, GL_TRUE);		// Create Texture Coords ( NEW )
  gluCylinder(quadratic/*quad*/,1.0/*base*/,6.5/*top*/,4.0/*height*/,60 /*slices*/,1/*stacks*/);

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
