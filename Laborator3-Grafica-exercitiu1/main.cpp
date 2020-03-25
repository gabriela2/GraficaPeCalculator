/*Hearn & Baker */
#include <windows.h>
#include <math.h>
#include <stdlib.h>
#include <GL/freeglut.h>

const double TWO_PI = 6.2831853;

GLsizei winWidth = 700, winHeight = 700;
GLuint regHex;
GLuint regHex2;
GLuint regHex3;
GLuint regHex4;

static GLfloat rotTheta = 0.0;

class scrPt
{
public:
	GLint x, y;
};

static void init (void)
{
	scrPt hexVertex;
	GLdouble hexTheta;
	GLint k;

	glClearColor(1.0, 1.0, 1.0, 1.0);
	regHex = glGenLists(1);
	glNewList(regHex, GL_COMPILE);
	glColor3f(1.0, 0.0, 0.0);
	//deseneaza primul poligon
	glBegin(GL_POLYGON);
	for (k = 0; k < 100; k++)
	{
		hexTheta = TWO_PI * double(k) / 100;
		hexVertex.x = 150 + 100 * cos(hexTheta);
		hexVertex.y = 150 + 100 * sin(hexTheta);
		glVertex2i(hexVertex.x, hexVertex.y);
	}
	glEnd();
	//deseneaza centrul
	glColor3f(1.0, 1.0, 1.0);
	glPointSize(5.0);
	glBegin(GL_POINTS);
	glVertex2i(150, 150);
	glEnd();
	glColor3f(0.0, 0.0, 0.0);
	glRasterPos2i(120, 130);
	const unsigned char* t = reinterpret_cast<const unsigned char*>("(150, 150)");
	glutBitmapString(GLUT_BITMAP_HELVETICA_10, t);
	//deseneaza raza
	glColor3f(1.0, 0.56, 0.23);
	glPointSize(1.0);
	glBegin(GL_LINES);
	glVertex2i(150, 150);
	glVertex2i(250, 150);
	glEnd();
	glColor3f(0.0, 0.0, 0.0);
	glRasterPos2i(140, 170);
	t = reinterpret_cast<const unsigned char*>("R = 100");
	glutBitmapString(GLUT_BITMAP_HELVETICA_10, t);

	glColor3f(1.0, 1.0, 1.0);
	//deseneaza al doilea poligon
	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	for (k = 0; k < 200; k++)
	{
		hexTheta = TWO_PI * k / 200;
		hexVertex.x = 50 + 20 * cos(hexTheta);
		hexVertex.y = 50 + 20 * sin(hexTheta);
		glVertex2i(hexVertex.x, hexVertex.y);
	}
	glEnd();
	//deseneaza centrul
	glColor3f(1.0, 1.0, 1.0);
	glPointSize(5.0);
	glBegin(GL_POINTS);
	glVertex2i(50, 50);
	glEnd();
	glColor3f(0.0, 0.0, 0.0);
	glRasterPos2i(20, 30);
	t = reinterpret_cast<const unsigned char*>("(50, 50)");
	glutBitmapString(GLUT_BITMAP_HELVETICA_10, t);
	//deseneaza raza
	glColor3f(1.0, 0.56, 0.23);
	glPointSize(1.0);
	glBegin(GL_LINES);
	glVertex2i(50, 50);
	glVertex2i(70, 50);
	glEnd();
	glColor3f(0.0, 0.0, 0.0);
	glRasterPos2i(40, 60);
	t = reinterpret_cast<const unsigned char*>("R = 20");
	glutBitmapString(GLUT_BITMAP_HELVETICA_10, t);
	//deseneaza al treilea poligon
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_POLYGON);
	for (k = 0; k < 200; k++)
	{
		hexTheta = TWO_PI * k / 200;
		hexVertex.x = 0 + 30 * cos(hexTheta);
		hexVertex.y = 0 + 30 * sin(hexTheta);
		glVertex2i(hexVertex.x, hexVertex.y);
	}
	glEnd();

	//deseneaza centrul
	glColor3f(1.0, 1.0, 1.0);
	glPointSize(5.0);
	glBegin(GL_POINTS);
	glVertex2i(0, 0);
	glEnd();
	glColor3f(0.0, 0.0, 0.0);
	glRasterPos2i(0, -20);
	t = reinterpret_cast<const unsigned char*>("(0,0)");
	glutBitmapString(GLUT_BITMAP_HELVETICA_10, t);
	//deseneaza raza
	glColor3f(1.0, 0.56, 0.23);
	glPointSize(1.0);
	glBegin(GL_LINES);
	glVertex2i(0, 0);
	glVertex2i(30, 0);
	glEnd();
	glColor3f(0.0, 0.0, 0.0);
	glRasterPos2i(0, -30);
	t = reinterpret_cast<const unsigned char*>("R = 30");
	glutBitmapString(GLUT_BITMAP_HELVETICA_10, t);
	glEndList();
}
void displayHex (void)
{
	glClear (GL_COLOR_BUFFER_BIT);


	glCallList (regHex);
	glPopMatrix ( );


	glFlush ( );
}



void winReshapeFcn (GLint newWidth, GLint newHeight)
{
	glViewport (0, 0, (GLsizei) newWidth, (GLsizei) newHeight);

	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ( );
	gluOrtho2D (-320.0, 320.0, -320.0, 320.0);

	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity ( );

	glClear (GL_COLOR_BUFFER_BIT);
}


int main (int argc, char **argv)
{
	glutInit (&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition (150, 150);
	glutInitWindowSize (winWidth, winHeight);
	glutCreateWindow ("Hexagon - utilizarea listelor de display");

	init ( );
	glutDisplayFunc (displayHex);
	glutReshapeFunc (winReshapeFcn);

	glutMainLoop ( );

}



