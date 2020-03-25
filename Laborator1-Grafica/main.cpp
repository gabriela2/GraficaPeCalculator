#include <windows.h>  // sunt mentionate fisiere (biblioteci) care urmeaza sa fie incluse
#include <gl/freeglut.h> // nu trebuie uitat freeglut.h (sau glut.h sau gl.h & glu.h)

void init (void)  // initializare fereastra de vizualizare
{
	glClearColor (1.0, 1.0, 1.0, 0.0); // precizeaza culoarea de fond a ferestrei de vizualizare

    glMatrixMode (GL_PROJECTION);  // se precizeaza este vorba de o reprezentare 2D, realizata prin proiectie ortogonala
	gluOrtho2D (0.0, 1300.0, 0.0, 600.0); // sunt indicate coordonatele extreme ale ferestrei de vizualizare
}


void desen (void) // procedura desenare
{

	glColor3f (0.25, 0.05, 0.75); // culoarea punctelor: albastru
	{
		 glPointSize (10.0);
		glBegin (GL_POINTS); // reprezinta puncte
		glVertex2i (20, 20);
		glVertex2i (21, 21);
		glVertex2i (22, 22);
		glVertex2i (23, 23);
		glVertex2i (24, 24);
		glVertex2i (27, 27);
		glVertex2i (100, 100);
		glEnd ( );

	}


	glColor3d (0.25, 0.05, 0.75);
	// glPointSize (6.0);
	glBegin (GL_POINTS);
	   glVertex2i (100, 400);
	   glColor3f (0.25, 0.05, 0.75);
	   glVertex2i (300, 500);
    glEnd ( );


   glColor3f (0.75, 0.5, 0.25); // culoarea liniei: rosu
       // reprezinta o linie franta
     //  glLineWidth (2.0);
	  //  glEnable (GL_LINE_STIPPLE);
	 //  glLineStipple (1, 0x1EED);
	   glBegin (GL_LINE_STRIP);
       glVertex2i (0,100);
	   glVertex2i (400, 500);
   glEnd ( );
  // glDisable (GL_LINE_STIPPLE);

    glColor3f (0.75, 0.5, 0.25);
	//	   glLineWidth (6.0);
       glBegin (GL_LINES); // reprezinta o reuniune de segmente
       glVertex2i (400,400);
	   glVertex2i (600, 500);
	   glVertex2i (700, 520);
	   glVertex2i (655, 690);
   glEnd ( );


   glColor3f(1.0, 0.0, 0.0);
    glPointSize(20.0);
    glEnable(GL_POINT_SMOOTH);
    glBegin (GL_POINTS);
        glVertex2i(150,150);
        glVertex2i(250,250);
        glVertex2i(350,350);
        glVertex2i(450,450);

    glEnd();
 glDisable(GL_POINT_SMOOTH);

   glFlush ( ); // proceseaza procedurile OpenGL cat mai rapid
}
int main (int argc, char** argv)
{
	glutInit (&argc, argv); // initializare GLUT
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB); // se utilizeaza un singur buffer | modul de colorare RedGreenBlue (= default)
	glutInitWindowPosition (50, 50); // pozitia initiala a ferestrei de vizualizare (in coordonate ecran)
	glutInitWindowSize (1000, 1000); // dimensiunile ferestrei
	glutCreateWindow ("Puncte & Segmente"); // creeaza fereastra, indicand numele ferestrei de vizualizare - apare in partea superioara

	init (); // executa procedura de initializare
	glClear (GL_COLOR_BUFFER_BIT); // reprezentare si colorare fereastra de vizualizare
	glutDisplayFunc (desen); // procedura desen este invocata ori de cate ori este nevoie
	glutMainLoop ( ); // ultima instructiune a programului, asteapta (eventuale) noi date de intrare

}
