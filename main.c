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
#include "tile.h"
#include "guardhut.h"
#include "sign.h"



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
static int window;

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);											//initiates the glut library
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA | GLUT_STENCIL ); //|GL_MULTISAMPLE);	//RGB is used to use RGB framebuffers and doble means to use two buffers
	glutInitWindowPosition(100,100);							//window starting position
	glutInitWindowSize(1200,700);									//window size width x height
	window = glutCreateWindow("1823 Monument");										//create windows with title
	glutFullScreen();

	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);
	glutReshapeFunc(reshape);
	init();

	glutMainLoop();													//event loop
	return 0;
}

void init(){

	glShadeModel (GL_SMOOTH);							//set background color
  glEnable( GL_DEPTH_TEST );					//make 3D objects non transparent
	glEnable(GL_POINT_SMOOTH | GL_LINE_SMOOTH | GL_SMOOTH);

	glEnable(GL_FOG); //fogging

	// alphableding
	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

	//enable lighting
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);

	//anti alisising
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glHint(GL_TEXTURE_COMPRESSION_HINT, GL_NICEST);
	glHint(GL_GENERATE_MIPMAP_HINT, GL_NICEST);
	glHint(GL_FRAGMENT_SHADER_DERIVATIVE_HINT, GL_NICEST);
	glHint (GL_FOG_HINT, GL_NICEST);



	glClearColor(0.5f,0.5f,0.5f,1);

	loadskyimage();
	loadroadimage();
	loadseawallimage();
	loadgroundimage();
	loadstoneimage();
	loadplatformimage();
	loadstandimage();
	loadcircleplatformimage();
	loadbenchimage();
	loadfenceimage();
	loadtileimage();
	loadguardhutimage();
	loadsignimage();
}

void display(){

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glLoadIdentity(); //reset transformation
	//set camera view
	gluLookAt(x,y,z,
						x+lx,y+ly,z+lz,
						0,1,0); // (eyex,eyey,eyez,eye center, eye center, eye center,up,up,up)

	//LIGHTING
	GLfloat ambientColor[] = {3.5f, 3.5f, 3.5f, 1.0f};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);

	//add positioned lighting
	GLfloat lightColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat lightPosition[] = { -1100.0f, 1100.0f, -700.0f, 1.0f};
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor);
	glLightfv(GL_LIGHT0, GL_POSITION,lightPosition);

	//Fogging
	GLfloat fogColor[] = { 0.5f, 0.5f, 0.5f ,0.1 };
	glFogfv(GL_FOG_COLOR, fogColor);
	glFogi(GL_FOG_MODE, GL_LINEAR);
	glFogf(GL_FOG_START, 10.0f);
	glFogf(GL_FOG_END, 2000.0f);

	//skybox
	glPushMatrix();
	glColor3f(1,1,1);
	glScalef (1000.0, 1000.0, 1000.0);
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
	glScalef (50.0, 1.0, 50.0);
	glTranslatef(0,-5.0,0);
	platform();
	glPopMatrix();

	//walkway platform
	glPushMatrix();
	glColor3f(1,1,1);
	glScalef(30.0, 1.0, 10.0);
	glTranslatef(2.665,-5.0,0);
	platform();
	glPopMatrix();

	//tile
	glPushMatrix();
	glColor3f(1,1,1);
	glScalef(1.0, 1.0, 1.0);
	glTranslatef(0,-3,0);
	glRotatef(90,1, 0, 0);
	tile();
	glPopMatrix();

	//front fence
	glPushMatrix();
	glRotatef(180,0,1,0);
	glTranslatef(41,-1,50);
	fence();
	glPopMatrix();

	glPushMatrix();
	glRotatef(180,0,1,0);
	glTranslatef(22,-1,50);
	fence();
	glPopMatrix();

	glPushMatrix();
	glRotatef(180,0,1,0);
	glTranslatef(3,-1,50);
	fence();
	glPopMatrix();

	glPushMatrix();
	glRotatef(180,0,1,0);
	glTranslatef(-16,-1,50);
	fence();
	glPopMatrix();

	glPushMatrix();
	glRotatef(180,0,1,0);
	glTranslatef(-35,-1,50);
	fence();
	glPopMatrix();


	//left fence
	glPushMatrix();
	glRotatef(-90,0,1,0);
	glTranslatef(-39,-1,50);
	fence();
	glPopMatrix();

	glPushMatrix();
	glRotatef(-90,0,1,0);
	glTranslatef(-20,-1,50);
	fence();
	glPopMatrix();

	glPushMatrix();
	glRotatef(-90,0,1,0);
	glTranslatef(-1,-1,50);
	fence();
	glPopMatrix();

	glPushMatrix();
	glRotatef(-90,0,1,0);
	glTranslatef(18,-1,50);
	fence();
	glPopMatrix();

	glPushMatrix();
	glRotatef(-90,0,1,0);
	glTranslatef(37,-1,50);
	fence();
	glPopMatrix();

	glPushMatrix();
	glRotatef(-90,0,1,0);
	glTranslatef(56,-1,50);
	fence();
	glPopMatrix();

	glPushMatrix();
	glRotatef(-90,0,1,0);
	glTranslatef(75,-1,50);
	fence();
	glPopMatrix();

	glPushMatrix();
	glRotatef(-90,0,1,0);
	glTranslatef(94,-1,50);
	fence();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-38.5,-1,102.5);
	fence();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-19.5,-1,102.5);
	fence();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.5,-1,102.5);
	fence();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(18.5,-1,102.5);
	fence();
	glPopMatrix();


	//road
	glPushMatrix();
	glColor3f(1,1,1);
	glTranslatef(120,-5,0);
	road();
	glPopMatrix();

	//road
	glPushMatrix();
	glColor3f(1,1,1);
	glTranslatef(-100,-5,0);
	road();
	glPopMatrix();

	//seawall
	glPushMatrix();
	glColor3f(1,1,1);
	glTranslatef(150,0,0);
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
	glTranslatef(0,-2.5,0);
	stone();
	glutSolidCube(1);
	glPopMatrix();

	//circleplatform
	glPushMatrix();
	glColor3f(1,1,1);
	glScalef(2,1,2);
	glTranslatef(0,-1.8,0);
	glRotatef(90,1,0,0);
	circleplatform();
	glPopMatrix();

	//walkway stone
	glPushMatrix();
	glColor3f(1,1,1);
	glTranslatef(55,-5,11);
	glScalef(1,2,1);
	walkway();
	glPopMatrix();

	//walkway stone
	glPushMatrix();
	glColor3f(1,1,1);
	glRotatef(180,0,1,0);
	glTranslatef(-95,-5,11);
	glScalef(1,2,1);
	walkway();
	glPopMatrix();

	//bench
	glPushMatrix();
	glColor3f(1,1,1);
	glTranslatef(-40,-2,0);
	glRotatef(90,0,1,0);
	bench();
	glPopMatrix();

	//bench
	glPushMatrix();
	glColor3f(1,1,1);
	glTranslatef(40,-2,0);
	glRotatef(90,0,1,0);
	bench();
	glPopMatrix();

	//bench
	glPushMatrix();
	glColor3f(1,1,1);
	glTranslatef(35,-2,20);
	glRotatef(45,0,1,0);
	bench();
	glPopMatrix();

	//bench
	glPushMatrix();
	glColor3f(1,1,1);
	glTranslatef(35,-2,-20);
	glRotatef(-45,0,1,0);
	bench();
	glPopMatrix();

	//guardhut
	glPushMatrix();
	glColor3f(1,1,1);
	glScalef(6,5,6);
	glTranslatef(16,0,-8);
	guardhut();
	glPopMatrix();

	//sign
	glPushMatrix();
	glColor3f(1,1,1);
	glTranslatef(60,0,20);
	sign();
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
			case 27:	glutDestroyWindow(window);
								exit(0);
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
