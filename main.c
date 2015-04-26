
#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <math.h>
#include <GL/glext.h>



void display();									//displays/ renders to screen
void init();									//initalizes some values before start
void keyboard(unsigned char , int , int);		//handles keyboard characters
void special(int , int , int);		//handles special keys
void mouse(int , int , int , int);				//handles mouse
void reshape();									//handles resizing of window
void fence();
void ground();
void road();

float angle = 0.0f;
float lx = 0.0f, lz = -1.0f;
float x = 0.0f, z = 20.0f;

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);											//initiates the glut library
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA |GL_MULTISAMPLE);	//RGB is used to use RGB framebuffers and doble means to use two buffers
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
  glEnable( GL_DEPTH_TEST );										//make 3D objects non transparent
	//glEnable(GL_SMOOTH);
	glEnable( GL_MULTISAMPLE );
}

void display(){

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity(); //reset transformation
	//set camera view
	gluLookAt(x,3.0f,z,
						x+lx,3.0f,z+lz,
						0,1,0); // (eyex,eyey,eyez,eye center, eye center, eye center,up,up,up)
   glxinfo();
	ground();
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

	//right back fence
	glPushMatrix();
	glRotatef(90,0,1,0);
	glTranslatef(10,0,10);
	fence();
	glPopMatrix();

	//right front fence
	glPushMatrix();
	glRotatef(90,0,1,0);
	glTranslatef(-10,0,10);
	fence();
	glPopMatrix();

	//left front fence
	glPushMatrix();
	glRotatef(-90,0,1,0);
	glTranslatef(10,0,10);
	fence();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.8,0.8,0);
	glScalef(10,10,10);
	//glTranslatef(10,0,0);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0,1,0);
	glScalef(10,10,1000);
	glTranslatef(10,0,0);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-30,0,0);
	road();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(40,0,0);
	road();
	glPopMatrix();


	//seawall
	glPushMatrix();
	glColor3f(0,1,0);
	glScalef(10,10,1000);
	glTranslatef(10,0,0);
	glutSolidCube(1);
	glPopMatrix();

	glutSwapBuffers();
}

void reshape(int w, int h){
	glViewport( 0, 0, w, h );
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	gluPerspective( 45, (float)w/h, 1, 200); //used with GL_PROJECTION
  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity();
  //glOrtho(20,20,20,20,10,100);
	//used with GL_MODELVIEW
	//gluLookAt(0,1,10,0,0,0,0,1,0);
}

void keyboard(unsigned char key, int x, int y){

	switch(key){

		case 'W':
							break;
    	case 'A':
    						break;
    	case 'S':
    						break;
    	case 'D':
    						break;
    	default: return;
	}

}

void special(int key, int xx, int yy){

	float fraction = 0.1f;

	switch(key){

		case GLUT_KEY_LEFT:
							angle -= 0.01f;
							lx = sin(angle);
							lz = -cos(angle);
							break;
    case GLUT_KEY_RIGHT:
							angle += 0.01f;
							lx =sin(angle);
							lz = -cos(angle);
    					break;
    case GLUT_KEY_UP:
							x += lx *fraction;
							z += lz * fraction;
    					break;
    case GLUT_KEY_DOWN:
							x -= lx *fraction;
							z -= lz * fraction;
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

void ground(){
	glPushMatrix();
	glColor3f(0.9,0.9,0.9);
	glTranslatef(0,-4,0);
	glScalef(1000,0,1000);
	glutSolidCube(1);
	glPopMatrix();

}

void road(){

	glPushMatrix();
	glColor3f(0.5,0.5,0.5);
	glScalef(10,0,1000);
	glutSolidCube(1);
	glPopMatrix();

}
