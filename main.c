#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <math.h>
#include <GL/glext.h>

#include "skybox.h"
#include "fence.h"
#include "road.h"
#include "ground.h"
#include "stone.h"
#include "stand.h"
#include "platform.h"
#include "walkway.h"
#include "circleplatform.h"
#include "bench.h"



void display();									//displays/ renders to screen
void init();									//initalizes some values before start
void keyboard(unsigned char , int , int);		//handles keyboard characters
void special(int , int , int);		//handles special keys
void mouse(int , int , int , int);				//handles mouse
void reshape();									//handles resizing of window


float angle = 0.0f, angle1 = 0.0f;
float lx = 0.0f, ly = 0.0f, lz = -1.0f;
float x = 0.0f, y = 3.0f ,z = 20.0f ;

int i;

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);											//initiates the glut library
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA ); //|GL_MULTISAMPLE);	//RGB is used to use RGB framebuffers and doble means to use two buffers
	glutInitWindowPosition(100,100);								//window starting position
	glutInitWindowSize(1200,700);									//window size width x height
	glutCreateWindow("1823 Monument");										//create windows with title

	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);
	glutReshapeFunc(reshape);
	init();

	glutMainLoop();													//event loop
	return 0;
}

void init(){

	glClearColor(0,208,255, 0.0);
	glShadeModel (GL_FLAT);							//set background color
  glEnable( GL_DEPTH_TEST );					//make 3D objects non transparent
	glEnable(GL_POINT_SMOOTH | GL_LINE_SMOOTH | GL_SMOOTH);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
	// glEnable( GL_MULTISAMPLE );

	loadskyimage();
	loadroadimage();
	loadseawallimage();
	loadgroundimage();
	loadstoneimage();
	loadplatformimage();
	loadstandimage();
	loadcircleplatformimage();
	loadbenchimage();
}

void display(){

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity(); //reset transformation
	//set camera view
	gluLookAt(x,y,z,
						x+lx,y+ly,z+lz,
						0,1,0); // (eyex,eyey,eyez,eye center, eye center, eye center,up,up,up)

	//skybox
	glPushMatrix();
	glColor3f(1,1,1);
	glScalef (2000.0, 2000.0, 2000.0);
	SkyFrameWork();
	glPopMatrix();

	//ground
	glPushMatrix();
	glColor3f(1,1,1);
	ground();
	glPopMatrix();

	//platform
	glPushMatrix();
	glColor3f(1,1,1);
	glScalef (30.0, 1.0, 30.0);
	glTranslatef(0,-5.0,0);
	platform();
	glPopMatrix();

	//platform
	glPushMatrix();
	glColor3f(1,1,1);
	glScalef(30.0, 1.0, 10.0);
	glTranslatef(2.0,-5.0,0);
	platform();
	glPopMatrix();


	//left back fence
	glPushMatrix();
	glRotatef(-90,0,1,0);
	glTranslatef(-10,0,10);
	fence();
	glPopMatrix();

	//back fence
	glPushMatrix();
	glRotatef(180,0,1,0);
	glTranslatef(0,0,22);
	fence();
	glPopMatrix();

	//left front fence
	glPushMatrix();
	glRotatef(-90,0,1,0);
	glTranslatef(10,0,10);
	fence();
	glPopMatrix();

	//road
	glPushMatrix();
	glColor3f(1,1,1);
	glTranslatef(100,-5,0);
	road();
	glPopMatrix();

	//road
	glPushMatrix();
	glColor3f(1,1,1);
	glTranslatef(-60,-5,0);
	road();
	glPopMatrix();

	//seawall
	glPushMatrix();
	glColor3f(1,1,1);
	glTranslatef(130,0,0);
	seawall();
	glPopMatrix();

	//stand
	glPushMatrix();
	glColor3f(1,1,1);
	glRotatef(180,0,1,0);
	glScalef(4,4,4);
	glTranslatef(0,0.8,0);
	stand();
	glPopMatrix();

	//stone
	glPushMatrix();
	glColor3f(1,1,1);
	glScalef(7,0.5,7);
	glTranslatef(0,-2,0);
	stone();
	glutSolidCube(1);
	glPopMatrix();


	//circleplatform
	glPushMatrix();
	glColor3f(1,1,1);
	glScalef(2,1,2);
	glRotatef(90,1,0,0);
	//glTranslatef(0,10,0);
	circleplatform();
	glPopMatrix();

	//walkway
	glPushMatrix();
	glColor3f(1,1,1);
	glTranslatef(35,-5,11);
	glScalef(1,2,1);
	walkway();
	glPopMatrix();

	//walkway
	glPushMatrix();
	glColor3f(1,1,1);
	glRotatef(180,0,1,0);
	glTranslatef(-75,-5,11);
	glScalef(1,2,1);
	walkway();
	glPopMatrix();

	//bench
	glPushMatrix();
	glColor3f(1,1,1);
	//glRotatef(180,0,1,0);
	glTranslatef(-50,0,0);
	bench();
	glPopMatrix();

	glutSwapBuffers();
}

void reshape(int w, int h){
	glViewport( 0, 0, w, h );
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	gluPerspective( 45, (float)w/h, 1, 5000); //used with GL_PROJECTION
  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity();
  //glOrtho(20,20,20,20,10,100);
	//used with GL_MODELVIEW
	//gluLookAt(0,1,10,0,0,0,0,1,0);
}

void keyboard(unsigned char key, int x, int y){

	switch(key){

			case 'w':	if(angle1 < 1.6){
									angle1 += 0.03f;
									ly = sin(angle1);
								}
								break;
    	case 'a':
    						break;

			case 's': if(angle1 > -1.6){
									angle1 -= 0.03f;
									ly = sin(angle1);
								}
    						break;
    	case 'd':
    						break;

    	default: return;
	}
	glutPostRedisplay();

}

void special(int key, int xx, int yy){

	float fraction = 0.5f;

	switch(key){

		case GLUT_KEY_LEFT:
							angle -= 0.03f;
							lx = sin(angle);
							lz = -cos(angle);
							break;
    case GLUT_KEY_RIGHT:
							angle += 0.03f;
							lx =sin(angle);
							lz = -cos(angle);
    					break;
    case GLUT_KEY_UP:
							x += lx *fraction;
							z += lz * fraction;
							y += ly *fraction;
    					break;
    case GLUT_KEY_DOWN:
							x -= lx *fraction;
							z -= lz * fraction;
							y -= ly *fraction;
							break;
    default: return;
	}

	glutPostRedisplay();
}

void mouse( int button, int state , int x , int y){

	switch(button){

		case GLUT_LEFT_BUTTON:
							break;
    	case GLUT_RIGHT_BUTTON:
    						break;
    	default: return;
	}
}

// void ground(){
// 	glPushMatrix();
// 	glColor3f(0.9,0.9,0.9);
// 	glTranslatef(0,-4,0);
// 	glScalef(2000,0,2000);
// 	glutSolidCube(1);
// 	glPopMatrix();
//
// }
