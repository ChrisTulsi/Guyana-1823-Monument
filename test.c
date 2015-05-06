
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <stdio.h>
#include <math.h>

GLuint texture[6];

float angle = 0.0f;
float lx = 0.0f, lz = -1.0f;
float x = 0.0f, z = 20.0f;

/**
 * Init function initializing the background to black.
 */
void init()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW | GL_PROJECTION);
    glEnable(GL_DEPTH_TEST);
}

void reshape(int w, int h)
{
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glFrustum(-1.0, 1.0, -1.0, 1.0, 0, 277.0);
   glMatrixMode(GL_MODELVIEW);
}

GLuint LoadTexture(const char * filename, int width, int height)
{
    GLuint texture;
    unsigned char * data;
    FILE * file;

    //Open the image file
    file = fopen(filename, "rb");
    //If it doesn't open just return 0
    if(file == NULL)
    {
        return 0;
    }

    //Allocate space for data and read
    data = (unsigned char *)malloc(width * height * 3);
    fread(data, width * height * 3, 1, file);

    //Close the file
    fclose(file);

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR );

    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );

    gluBuild2DMipmaps( GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, data );
    free(data);

    return texture;
}

void draw()
{
    int width = 1024;
    int height = 1024;
    int length = 1024;

    //start in this coordinates
    int x = 0;
    int y = 0;
    int z = 0;

    //center the square
    x = x - width / 2;
    y = y - height / 2;
    z = z - length / 2;

    // Bind the BACK texture of the sky map to the BACK side of the cube
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glBegin(GL_QUADS);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y,  z);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y + height, z);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + height, z);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z);
    glEnd();

    //FRONT
    glBindTexture(GL_TEXTURE_2D, texture[1]);
    glBegin(GL_QUADS);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y,  z + length);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + height, z + length);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height, z + length);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y,  z + length);
    glEnd();

    //BOTTOM
    glBindTexture(GL_TEXTURE_2D, texture[4]);
    glBegin(GL_QUADS);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y,  z);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y,  z + length);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y,  z + length);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y,  z);
    glEnd();

    //TOP
    glBindTexture(GL_TEXTURE_2D, texture[5]);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y + height, z);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y + height, z + length);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + height, z + length);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + height, z);
    glEnd();

    //LEFT
    glBindTexture(GL_TEXTURE_2D, texture[2]);
    glBegin(GL_QUADS);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + height, z);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + height, z + length);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y,  z + length);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y,  z);

    glEnd();

    //RIGHT
    glBindTexture(GL_TEXTURE_2D, texture[3]);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y,  z);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y,  z + length);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y + height, z + length);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height, z);
    glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT );
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    texture[0] = LoadTexture("txStormydays_back.bmp", 512, 512);
    /*texture[0] = SOIL_load_OGl_texture
    {
        "back.bmp",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    };*/
    texture[1] = LoadTexture("txStormydays_front.bmp", 512, 512);
    texture[2] = LoadTexture("txStormydays_left.bmp", 512, 512);
    texture[3] = LoadTexture("txStormydays_right.bmp", 512, 512);
    texture[4] = LoadTexture("txStormydays_down.bmp", 512, 512);
    texture[5] = LoadTexture("txStormydays_up.bmp", 512, 512);

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);

    draw();
    glutSwapBuffers();
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
    					break;
    case GLUT_KEY_DOWN:
							x -= lx *fraction;
							z -= lz * fraction;
							break;
    default: return;
	}
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_ALPHA);
    glutInitWindowSize(1000, 1000);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("blah");

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(special);

    glutMainLoop();

    return 0;
}
