#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <math.h>
#include <GL/glext.h>

#include "texture.h"
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

void shadowMatrix(GLfloat shadowMat[4][4], GLfloat groundplane[4], GLfloat lightPosition[4]);
void findPlane(GLfloat plane[4], GLfloat v0[3], GLfloat v1[3], GLfloat v2[3]);


float angle = 0.0f, angle1 = 0.0f;
float lx = 0.0f, ly = 0.0f, lz = -1.0f;
float x = 0.0f, y = 3.0f ,z = 20.0f ;

GLfloat floorPlane[4];
GLfloat floorShadow[4][4];
GLfloat lightPosition[] = { -700.0f, 700.0f, -700.0f, 1.0f};

enum {
  X, Y, Z, W
};
enum {
  A, B, C, D
};

int i;
static int window;

static GLfloat floorVertices[4][3] = {
  { -1000.0, -5.0, 1000.0 },
  { 1000.0, -5.0, 1000.0 },
  { 1000.0, -5.0, -1000.0 },
  { -1000.0, -5.0, -1000.0 },
};

static GLfloat floorVertices2[4][3] = {
  { -50.0, -3, 50.0 },
  { 50.0, -3, 50.0 },
  { 50.0, -3, -50.0 },
  { -50.0, -3, -50.0 },
};

static GLfloat floorVertices3[4][3] = {
  { -50.0, -5, 50.0 },
  { 50.0, -5, 50.0 },
  { 50.0, 2, -50.0 },
  { -50.0, 2, -50.0 },
};

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

	glClearColor(0.0f,0.0f,0.0f,1);

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

	glClearStencil(0); //clear the stencil buffer
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glLoadIdentity(); //reset transformation
	//set camera view
	gluLookAt(x,y,z,
						x+lx,y+ly,z+lz,
						0,1,0); // (eyex,eyey,eyez,eye center, eye center, eye center,up,up,up)

  //Shadowing
  findPlane(floorPlane, floorVertices[1], floorVertices[2], floorVertices[3]);
  shadowMatrix(floorShadow, floorPlane, lightPosition);

  glStencilFunc(GL_LESS, 3, 0xffffffff);  /* draw if ==1 */
  glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glDisable(GL_LIGHTING);  /* Force the 50% black. */
  glColor4f(0.0, 0.0, 0.0, 0.5);

  glEnable(GL_POLYGON_OFFSET_FILL);
  glPolygonOffset(1.0, 1.0);

  //platform
	glPushMatrix();
  glColor4f(0.0, 0.0, 0.0, 0.5);
  glMultMatrixf((GLfloat *) floorShadow);
	glTranslatef(0,-4.0,0);
  glScalef (50.0, 1.0, 50.0);
  glPolygonMode (GL_FRONT_AND_BACK, GL_FILL);
	platform();
  glPolygonMode (GL_FRONT_AND_BACK, GL_FILL);
	glPopMatrix();

  //walkway platform shadow
  glPushMatrix();
  glColor4f(0.0, 0.0, 0.0, 0.5);
  glMultMatrixf((GLfloat *) floorShadow);
  glTranslatef(80,-4.0,0);
  glScalef(30.0, 1.0, 10.0);
  glPolygonMode (GL_FRONT_AND_BACK, GL_FILL);
  platform();
  glPopMatrix();

  //guardhut
  glPushMatrix();
  glColor4f(0.0, 0.0, 0.0, 0.5);
  glMultMatrixf((GLfloat *) floorShadow);
  glTranslatef(80,0,-35);
  glScalef(6,5,6);
  guardhut();
  glPopMatrix();

  //sign
  glPushMatrix();
  glColor4f(0.0, 0.0, 0.0, 0.5);
  glMultMatrixf((GLfloat *) floorShadow);
  glTranslatef(60,0,20);
  sign();
  glPopMatrix();

  //seawall shadow
  glPushMatrix();
  glColor4f(0.0, 0.0, 0.0, 0.5);
  glMultMatrixf((GLfloat *) floorShadow);
  glTranslatef(150,0,0);
  seawall();
  glPopMatrix();

  //walkway stone
  glPushMatrix();
  glColor4f(0.0, 0.0, 0.0, 0.5);
  glMultMatrixf((GLfloat *) floorShadow);
  glTranslatef(55,-3,11);
  glScalef(1,2,1);
  walkway();
  glPopMatrix();

  //walkway stone
  glPushMatrix();
  glColor4f(0.0, 0.0, 0.0, 0.5);
  glMultMatrixf((GLfloat *) floorShadow);
  glTranslatef(95,-3,-11);
  glScalef(1,2,1);
  glRotatef(180,0,1,0);
  walkway();
  glPopMatrix();

  //lower fence
	glPushMatrix();
  glColor4f(0.0, 0.0, 0.0, 0.5);
  glMultMatrixf((GLfloat *) floorShadow);
  glTranslatef(-49.5,-2,60);
	glRotatef(-90,0,1,0);
	fence();
	glPopMatrix();

	glPushMatrix();
  glColor4f(0.0, 0.0, 0.0, 0.5);
  glMultMatrixf((GLfloat *) floorShadow);
  glTranslatef(-49.5,-2,79);
	glRotatef(-90,0,1,0);
	fence();
	glPopMatrix();

	glPushMatrix();
  glColor4f(0.0, 0.0, 0.0, 0.5);
  glMultMatrixf((GLfloat *) floorShadow);
  glTranslatef(-49.5,-2,98);
	glRotatef(-90,0,1,0);
	fence();
	glPopMatrix();

  //backfence
	glPushMatrix();
  glColor4f(0.0, 0.0, 0.0, 0.5);
  glMultMatrixf((GLfloat *) floorShadow);
	glTranslatef(-38,-2,106.5);
	fence();
	glPopMatrix();

	glPushMatrix();
  glColor4f(0.0, 0.0, 0.0, 0.5);
  glMultMatrixf((GLfloat *) floorShadow);
	glTranslatef(-19,-2,106.5);
	fence();
	glPopMatrix();

	glPushMatrix();
  glColor4f(0.0, 0.0, 0.0, 0.5);
  glMultMatrixf((GLfloat *) floorShadow);
	glTranslatef(-0,-2,106.5);
	fence();
	glPopMatrix();

	glPushMatrix();
  glColor4f(0.0, 0.0, 0.0, 0.5);
  glMultMatrixf((GLfloat *) floorShadow);
	glTranslatef(19,-2,106.5);
	fence();
	glPopMatrix();

  //pickets
  glPushMatrix();
  glColor4f(0.0, 0.0, 0.0, 0.5);
  glMultMatrixf((GLfloat *) floorShadow);
  glTranslatef(-49.5,0,46.5);
  glScalef(0.1,3,0.4);
  picket();
  glPopMatrix();

  glPushMatrix();
  glColor4f(0.0, 0.0, 0.0, 0.5);
  glMultMatrixf((GLfloat *) floorShadow);
  glTranslatef(-49.5,0,47.5);
  glScalef(0.1,3,0.4);
  picket();
  glPopMatrix();

  glPushMatrix();
  glColor4f(0.0, 0.0, 0.0, 0.5);
  glMultMatrixf((GLfloat *) floorShadow);
  glTranslatef(-49.5,0,48.5);
  glScalef(0.1,3,0.4);
  picket();
  glPopMatrix();

  glPushMatrix();
  glColor4f(0.0, 0.0, 0.0, 0.5);
  glMultMatrixf((GLfloat *) floorShadow);
  glTranslatef(-49.5,0,49);
  glScalef(0.1,3,0.4);
  picket();
  glPopMatrix();

  findPlane(floorPlane, floorVertices2[1], floorVertices2[2], floorVertices2[3]);
  shadowMatrix(floorShadow, floorPlane, lightPosition);

  //front fence
	glPushMatrix();
  glColor4f(0.0, 0.0, 0.0, 0.5);
  glMultMatrixf((GLfloat *) floorShadow);
  glTranslatef(-41,0,-50);
	glRotatef(180,0,1,0);
  fence();
	glPopMatrix();

	glPushMatrix();
  glColor4f(0.0, 0.0, 0.0, 0.5);
  glMultMatrixf((GLfloat *) floorShadow);
  glTranslatef(-22,0,-50);
	glRotatef(180,0,1,0);
	fence();
	glPopMatrix();

	glPushMatrix();
  glColor4f(0.0, 0.0, 0.0, 0.5);
  glMultMatrixf((GLfloat *) floorShadow);
  glTranslatef(-3,0,-50);
	glRotatef(180,0,1,0);
	fence();
	glPopMatrix();

	glPushMatrix();
  glColor4f(0.0, 0.0, 0.0, 0.5);
  glMultMatrixf((GLfloat *) floorShadow);
  glTranslatef(16,0,-50);
	glRotatef(180,0,1,0);
	fence();
	glPopMatrix();

	glPushMatrix();
  glColor4f(0.0, 0.0, 0.0, 0.5);
  glMultMatrixf((GLfloat *) floorShadow);
  glTranslatef(35,0,-50);
	glRotatef(180,0,1,0);
	fence();
	glPopMatrix();

  //left fence
	glPushMatrix();
  glColor4f(0.0, 0.0, 0.0, 0.5);
  glMultMatrixf((GLfloat *) floorShadow);
  glTranslatef(-49.5,-0,-38.5);
	glRotatef(-90,0,1,0);
	fence();
	glPopMatrix();

	glPushMatrix();
  glColor4f(0.0, 0.0, 0.0, 0.5);
  glMultMatrixf((GLfloat *) floorShadow);
  glTranslatef(-49.5,0,-19.5);
	glRotatef(-90,0,1,0);
	fence();
	glPopMatrix();

	glPushMatrix();
  glColor4f(0.0, 0.0, 0.0, 0.5);
  glMultMatrixf((GLfloat *) floorShadow);
	glTranslatef(-49.5,0,-0.5);
  glRotatef(-90,0,1,0);
	fence();
	glPopMatrix();

	glPushMatrix();
  glColor4f(0.0, 0.0, 0.0, 0.5);
  glMultMatrixf((GLfloat *) floorShadow);
  glTranslatef(-49.5,0,18.5);
	glRotatef(-90,0,1,0);
	fence();
	glPopMatrix();

	glPushMatrix();
  glColor4f(0.0, 0.0, 0.0, 0.5);
  glMultMatrixf((GLfloat *) floorShadow);
  glTranslatef(-49.5,0,37.5);
	glRotatef(-90,0,1,0);
	fence();
	glPopMatrix();

  //bench shadow
  glPushMatrix();
  glColor4f(0.0, 0.0, 0.0, 0.5);
  glMultMatrixf((GLfloat *) floorShadow);
  glTranslatef(-40,-2.5,0);
  glRotatef(90,0,1,0);
  bench();
  glPopMatrix();

  //bench shadow
  glPushMatrix();
  glColor4f(0.0, 0.0, 0.0, 0.5);
  glMultMatrixf((GLfloat *) floorShadow);
  glTranslatef(40,-2.5,0);
  glRotatef(90,0,1,0);
  bench();
  glPopMatrix();

  //bench shadow
  glPushMatrix();
  glColor4f(0.0, 0.0, 0.0, 0.5);
  glMultMatrixf((GLfloat *) floorShadow);
  glTranslatef(35,-2.5,20);
  glRotatef(45,0,1,0);
  bench();
  glPopMatrix();

  //bench shadow
  glPushMatrix();
  glColor4f(0.0, 0.0, 0.0, 0.5);
  glMultMatrixf((GLfloat *) floorShadow);
  glTranslatef(35,-2.5,-20);
  glRotatef(-45,0,1,0);
  bench();
  glPopMatrix();


  findPlane(floorPlane, floorVertices3[1], floorVertices3[2], floorVertices3[3]);
  shadowMatrix(floorShadow, floorPlane, lightPosition);

  //stand shadow
	glPushMatrix();
  glColor4f(0.0, 0.0, 0.0, 0.5);
  glMultMatrixf((GLfloat *) floorShadow);
  glTranslatef(0,4,0);
	glScalef(4,4,4);
  glRotatef(180,0,1,0);
	stand();
	glPopMatrix();

	//stone shadow
	glPushMatrix();
  glColor4f(0.0, 0.0, 0.0, 0.5);
  glMultMatrixf((GLfloat *) floorShadow);
  glTranslatef(0,-0.5,0);
	glScalef(7,0.5,7);
	stone();
	glPopMatrix();

  glDisable(GL_BLEND);
  glEnable(GL_LIGHTING);
  glDisable(GL_STENCIL_TEST);


	//LIGHTING
	GLfloat ambientColor[] = {3.5f, 3.5f, 3.5f, 1.0f};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);

	//add positioned lighting
	GLfloat lightColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor);
	glLightfv(GL_LIGHT0, GL_POSITION,lightPosition);

  //Fogging
	GLfloat fogColor[] = { 0.5f, 0.5f, 0.5f ,0.1 };
	glFogfv(GL_FOG_COLOR, fogColor);
	glFogi(GL_FOG_MODE, GL_LINEAR);
	glFogf(GL_FOG_START, 10.0f);
	glFogf(GL_FOG_END, 1800.0f);

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
	glTranslatef(0,-4.0,0);
  glScalef (50.0, 1.0, 50.0);
	platform();
	glPopMatrix();

	//walkway platform
	glPushMatrix();
	glColor3f(1,1,1);
  glTranslatef(80,-4.0,0);
	glScalef(30.0, 1.0, 10.0);
	platform();
	glPopMatrix();

	//front fence
	glPushMatrix();
  glTranslatef(-41,0,-50);
	glRotatef(180,0,1,0);
	fence();
	glPopMatrix();

	glPushMatrix();
  glTranslatef(-22,0,-50);
	glRotatef(180,0,1,0);
	fence();
	glPopMatrix();

	glPushMatrix();
  glTranslatef(-3,0,-50);
	glRotatef(180,0,1,0);
	fence();
	glPopMatrix();

	glPushMatrix();
  glTranslatef(16,0,-50);
	glRotatef(180,0,1,0);
	fence();
	glPopMatrix();

	glPushMatrix();
  glTranslatef(35,0,-50);
	glRotatef(180,0,1,0);
	fence();
	glPopMatrix();


	//left fence
	glPushMatrix();
  glTranslatef(-49.5,-0,-38.5);
	glRotatef(-90,0,1,0);
	fence();
	glPopMatrix();

	glPushMatrix();
  glTranslatef(-49.5,0,-19.5);
	glRotatef(-90,0,1,0);
	fence();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-49.5,0,-0.5);
  glRotatef(-90,0,1,0);
	fence();
	glPopMatrix();

	glPushMatrix();
  glTranslatef(-49.5,0,18.5);
	glRotatef(-90,0,1,0);
	fence();
	glPopMatrix();

	glPushMatrix();
  glTranslatef(-49.5,0,37.5);
	glRotatef(-90,0,1,0);
	fence();
	glPopMatrix();

  glPushMatrix();
  glTranslatef(-49.5,0,46.5);
  glScalef(0.1,3,0.4);
	picket();
	glPopMatrix();

  glPushMatrix();
  glTranslatef(-49.5,0,47.5);
  glScalef(0.1,3,0.4);
	picket();
	glPopMatrix();

  glPushMatrix();
  glTranslatef(-49.5,0,48.5);
  glScalef(0.1,3,0.4);
	picket();
	glPopMatrix();

  glPushMatrix();
  glTranslatef(-49.5,0,49);
  glScalef(0.1,3,0.4);
	picket();
	glPopMatrix();

  //lower fence
	glPushMatrix();
  glTranslatef(-49.5,-2,60);
	glRotatef(-90,0,1,0);
	fence();
	glPopMatrix();

	glPushMatrix();
  glTranslatef(-49.5,-2,79);
	glRotatef(-90,0,1,0);
	fence();
	glPopMatrix();

	glPushMatrix();
  glTranslatef(-49.5,-2,98);
	glRotatef(-90,0,1,0);
	fence();
	glPopMatrix();

  //backfence
	glPushMatrix();
	glTranslatef(-38,-2,106.5);
	fence();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-19,-2,106.5);
	fence();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0,-2,106.5);
	fence();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(19,-2,106.5);
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
  glTranslatef(0,4,0);
	glScalef(4,4,4);
  glRotatef(180,0,1,0);
	stand();
	glPopMatrix();

	//stone
	glPushMatrix();
	glColor3f(1,1,1);
  glTranslatef(0,-0.5,0);
	glScalef(7,0.5,7);
	stone();
	glPopMatrix();

	//circleplatform
	glPushMatrix();
	glColor3f(1,1,1);
  glTranslatef(0,-1,0);
	glScalef(2,1,2);
	glRotatef(90,1,0,0);
	circleplatform();
	glPopMatrix();

  //tile
  glPushMatrix();
  glColor3f(1,1,1);
  glTranslatef(0,-2.5,0);
  glScalef(1.0, 1.0, 1.0);
  glRotatef(90,1, 0, 0);
  tile();
  glPopMatrix();

	//walkway stone
	glPushMatrix();
	glColor3f(1,1,1);
	glTranslatef(55,-3.5,11);
	glScalef(1,1.5,1);
	walkway();
	glPopMatrix();

	//walkway stone
	glPushMatrix();
	glColor3f(1,1,1);
	glTranslatef(95,-3.5,-11);
	glScalef(1,1.5,1);
  glRotatef(180,0,1,0);
	walkway();
	glPopMatrix();

	//bench
	glPushMatrix();
	glColor3f(1,1,1);
	glTranslatef(-40,-2.5,0);
	glRotatef(90,0,1,0);
	bench();
	glPopMatrix();

	//bench
	glPushMatrix();
	glColor3f(1,1,1);
	glTranslatef(40,-2.5,0);
	glRotatef(90,0,1,0);
	bench();
	glPopMatrix();

	//bench
	glPushMatrix();
	glColor3f(1,1,1);
	glTranslatef(35,-2.5,20);
	glRotatef(45,0,1,0);
	bench();
	glPopMatrix();

	//bench
	glPushMatrix();
	glColor3f(1,1,1);
	glTranslatef(35,-2.5 ,-20);
	glRotatef(-45,0,1,0);
	bench();
	glPopMatrix();

  //guardhut
  glPushMatrix();
  glColor3f(1,1,1);
  glTranslatef(80,0,-35);
  glScalef(6,5,6);
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
							if(y < -1 && angle1 < 0.00f){break;}  //collision of floor
							x += lx *fraction;
							z += lz * fraction;
							y += ly *fraction;
    					break;
    case GLUT_KEY_DOWN:
							if(y < -1 && angle1 > 0.00f){break;}  //collision of floor
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

void shadowMatrix(GLfloat shadowMat[4][4], GLfloat groundplane[4], GLfloat lightpos[4])
{
  GLfloat dot;

  /* Find dot product between light position vector and ground plane normal. */
  dot = groundplane[X] * lightpos[X] + groundplane[Y] * lightpos[Y] + groundplane[Z] * lightpos[Z] +
    groundplane[W] * lightpos[W];

  shadowMat[0][0] = dot - lightpos[X] * groundplane[X];
  shadowMat[1][0] = 0.f - lightpos[X] * groundplane[Y];
  shadowMat[2][0] = 0.f - lightpos[X] * groundplane[Z];
  shadowMat[3][0] = 0.f - lightpos[X] * groundplane[W];

  shadowMat[X][1] = 0.f - lightpos[Y] * groundplane[X];
  shadowMat[1][1] = dot - lightpos[Y] * groundplane[Y];
  shadowMat[2][1] = 0.f - lightpos[Y] * groundplane[Z];
  shadowMat[3][1] = 0.f - lightpos[Y] * groundplane[W];

  shadowMat[X][2] = 0.f - lightpos[Z] * groundplane[X];
  shadowMat[1][2] = 0.f - lightpos[Z] * groundplane[Y];
  shadowMat[2][2] = dot - lightpos[Z] * groundplane[Z];
  shadowMat[3][2] = 0.f - lightpos[Z] * groundplane[W];

  shadowMat[X][3] = 0.f - lightpos[W] * groundplane[X];
  shadowMat[1][3] = 0.f - lightpos[W] * groundplane[Y];
  shadowMat[2][3] = 0.f - lightpos[W] * groundplane[Z];
  shadowMat[3][3] = dot - lightpos[W] * groundplane[W];

}

void findPlane(GLfloat plane[4], GLfloat v0[3], GLfloat v1[3], GLfloat v2[3]){
  GLfloat vec0[3], vec1[3];

  /* Need 2 vectors to find cross product. */
  vec0[X] = v1[X] - v0[X];
  vec0[Y] = v1[Y] - v0[Y];
  vec0[Z] = v1[Z] - v0[Z];

  vec1[X] = v2[X] - v0[X];
  vec1[Y] = v2[Y] - v0[Y];
  vec1[Z] = v2[Z] - v0[Z];

  /* find cross product to get A, B, and C of plane equation */
  plane[A] = vec0[Y] * vec1[Z] - vec0[Z] * vec1[Y];
  plane[B] = -(vec0[X] * vec1[Z] - vec0[Z] * vec1[X]);
  plane[C] = vec0[X] * vec1[Y] - vec0[Y] * vec1[X];

  plane[D] = -(plane[A] * v0[X] + plane[B] * v0[Y] + plane[C] * v0[Z]);
}
