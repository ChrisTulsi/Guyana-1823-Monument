#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

void fence(){

	glColor3f(1.0, 1.0, 1.0);
	glPushMatrix();
	glScalef(0.9,4,0.1);
	glutSolidCube(1);
	glColor3f(0, 0, 0);
	glutWireCube(1.001);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.5,0,0);
	glScalef(0.9,4,0.1);
	glColor3f(1.0, 1.0, 1.0);
	glutSolidCube(1);
	glColor3f(0, 0, 0);
	glutWireCube(1.001);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.5,0,0);
	glScalef(0.9,4,0.1);
	glColor3f(1.0, 1.0, 1.0);
	glutSolidCube(1);
	glColor3f(0, 0, 0);
	glutWireCube(1.001);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(3,0,0);
	glScalef(0.9,4,0.1);
	glColor3f(1.0, 1.0, 1.0);
	glutSolidCube(1);
	glColor3f(0, 0, 0);
	glutWireCube(1.001);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-3,0,0);
	glScalef(0.9,4,0.1);
	glColor3f(1.0, 1.0, 1.0);
	glutSolidCube(1);
	glColor3f(0, 0, 0);
	glutWireCube(1.001);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(4.5,0,0);
	glScalef(0.9,4,0.1);
	glColor3f(1.0, 1.0, 1.0);
	glutSolidCube(1);
	glColor3f(0, 0, 0);
	glutWireCube(1.001);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-4.5,0,0);
	glScalef(0.9,4,0.1);
	glColor3f(1.0, 1.0, 1.0);
	glutSolidCube(1);
	glColor3f(0, 0, 0);
	glutWireCube(1.001);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(6,0,0);
	glScalef(0.9,4,0.1);
	glColor3f(1.0, 1.0, 1.0);
	glutSolidCube(1);
	glColor3f(0, 0, 0);
	glutWireCube(1.001);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-6,0,0);
	glScalef(0.9,4,0.1);
	glColor3f(1.0, 1.0, 1.0);
	glutSolidCube(1);
	glColor3f(0, 0, 0);
	glutWireCube(1.001);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(7.5,0,0);
	glScalef(0.9,4,0.1);
	glColor3f(1.0, 1.0, 1.0);
	glutSolidCube(1);
	glColor3f(0, 0, 0);
	glutWireCube(1.001);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-7.5,0,0);
	glScalef(0.9,4,0.1);
	glColor3f(1.0, 1.0, 1.0);
	glutSolidCube(1);
	glColor3f(0, 0, 0);
	glutWireCube(1.001);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(9,0,0);
	glScalef(0.9,4,0.1);
	glColor3f(1.0, 1.0, 1.0);
	glutSolidCube(1);
	glColor3f(0, 0, 0);
	glutWireCube(1.001);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-9,0,0);
	glScalef(0.9,4,0.1);
	glColor3f(1.0, 1.0, 1.0);
	glutSolidCube(1);
	glColor3f(0, 0, 0);
	glutWireCube(1.001);
	glPopMatrix();

	//top rails
	glPushMatrix();
	glTranslatef(0,1,0.1);
	glScalef(22,0.8,0.1);
	glColor3f(1.0, 0.0, 0.0);
	glutSolidCube(1);
	glColor3f(0, 0, 0);
	glutWireCube(1.001);
	glPopMatrix();

	//bottom rail
	glPushMatrix();
	glTranslatef(0, -1, 0.1);
	glScalef(22,0.8,0.1);
	glColor3f(1.0, 0.0, 0.0);
	glutSolidCube(1);
	glColor3f(0, 0, 0);
	glutWireCube(1.001);
	glPopMatrix();
}
