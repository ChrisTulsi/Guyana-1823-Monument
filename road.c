#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <math.h>
#include <GL/glext.h>
#include <stdio.h>
#include <stdlib.h>
#include "road.h"
#include "texture.h"

void loadroadimage(){
	roadtexture = LoadTexture("/home/chris/Desktop/images/asphalt.bmp", 1, 2048, 2048);  //BACK
}

void road(){

	// Enable/Disable features
	glPushAttrib(GL_ENABLE_BIT);
	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, roadtexture);
	glBegin(GL_QUADS);
			glNormal3f(0,1,0);
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mColor);
			glTexCoord2f(0.0, 0.0f); glVertex3f(-10, 1, 1000);
			glTexCoord2f(500.0f, 0.0f); glVertex3f(-10, 1, -1000);
			glTexCoord2f(500.0f, 20.0f); glVertex3f(10, 1, -1000);
			glTexCoord2f(0.0f, 20.0f); glVertex3f(10, 1, 1000);
	glEnd();

	glPopAttrib();
	glDisable( GL_TEXTURE_2D );
  //Reset and transform the matrix.
  glLoadIdentity();

}
