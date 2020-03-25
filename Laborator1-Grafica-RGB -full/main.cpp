#include <windows.h>  // sunt mentionate fisiere (biblioteci) care urmeaza sa fie incluse
#include <gl/freeglut.h> // nu trebuie uitat freeglut.h (sau glut.h sau gl.h & glu.h)

void init (void)  // initializare fereastra de vizualizare
{
	glClearColor (1.0, 1.0, 1.0, 0.0); // precizeaza culoarea de fond a ferestrei de vizualizare

    glMatrixMode (GL_PROJECTION);  // se precizeaza este vorba de o reprezentare 2D, realizata prin proiectie ortogonala
	gluOrtho2D (0.0, 500.0, 0.0, 500.0); // sunt indicate coordonatele extreme ale ferestrei de vizualizare
}

void desen (void) // procedura desenare
{
    glShadeModel(GL_SMOOTH);
    glLineWidth(5.0);

    glBegin(GL_POLYGON);
    glColor3f (0.0, 0.0, 0.0);
    glVertex2i(200,180);
    glColor3f (0.0, 0.0, 1.0);
    glVertex2i(400,180);
    glColor3f (1.0, 0.0, 1.0);
    glVertex2i(350,150);
    glColor3f (1.0, 0.0, 0.0);
    glVertex2i(150,150);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f (0.0, 1.0, 0.0);
    glVertex2i(200,380);
    glColor3f (1.0, 1.0, 0.0);
    glVertex2i(150,350);
    glColor3f (1.0, 0.0, 0.0);
    glVertex2i(150,150);
    glColor3f (0.0, 0.0, 0.0);
    glVertex2i(200,180);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f (0.0, 1.0, 0.0);
    glVertex2i(200,380);
    glColor3f (0.0, 1.0, 1.0);
    glVertex2i(400,380);
    glColor3f (0.0, 0.0, 1.0);
    glVertex2i(400,180);
    glColor3f (0.0, 0.0, 0.0);
    glVertex2i(200,180);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f (1.0, 0.0, 0.0);
    glVertex2i(150,150);
    glColor3f (1.0, 0.0, 1.0);
    glVertex2i(350,150);
    glColor3f (1.0, 1.0, 1.0);
    glVertex2i(350,350);
    glColor3f (1.0, 1.0, 0.0);
    glVertex2i(150,350);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f (1.0, 0.0, 1.0);
    glVertex2i(350,150);
    glColor3f (0.0, 0.0, 1.0);
    glVertex2i(400,180);
    glColor3f (0.0, 1.0, 1.0);
    glVertex2i(400,380);
    glColor3f (1.0, 1.0, 1.0);
    glVertex2i(350,350);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f (0.0, 1.0, 0.0);
    glVertex2i(200,380);
    glColor3f (1.0, 1.0, 0.0);
    glVertex2i(150,350);
    glColor3f (1.0, 1.0, 1.0);
    glVertex2i(350,350);
    glColor3f (0.0, 1.0, 1.0);
    glVertex2i(400,380);
    glEnd();

   glFlush ( ); // proceseaza procedurile OpenGL cat mai rapid
}
int main (int argc, char** argv)
{
	glutInit (&argc, argv); // initializare GLUT
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB); // se utilizeaza un singur buffer | modul de colorare RedGreenBlue (= default)
	glutInitWindowPosition (50, 50); // pozitia initiala a ferestrei de vizualizare (in coordonate ecran)
	glutInitWindowSize (600, 600); // dimensiunile ferestrei
	glutCreateWindow ("Cub RGB - 2D"); // creeaza fereastra, indicand numele ferestrei de vizualizare - apare in partea superioara

	init (); // executa procedura de initializare
	glClear (GL_COLOR_BUFFER_BIT); // reprezentare si colorare fereastra de vizualizare
	glutDisplayFunc (desen); // procedura desen este invocata ori de cate ori este nevoie
	glutMainLoop ( ); // ultima instructiune a programului, asteapta (eventuale) noi date de intrare

}




