#include <gl/freeglut.h> // nu trebuie uitat freeglut.h (sau glut.h sau gl.h & glu.h)
#include <iostream>
using namespace std;
int X[100];
int Y[100];
int nr_puncte;


void desen(void) // procedura desenare
{
	glClear(GL_COLOR_BUFFER_BIT); // reprezentare si colorare fereastra de vizualizare
	int i;
	glPointSize(20);
	glLineWidth(15);


	glColor3f(1, 0, 0);

	glBegin(GL_LINE_STRIP);

	for (i = 0; i < nr_puncte; i++)
		glVertex2i(X[i], Y[i]);

	glEnd();


	glColor3f(0, 0, 1);

	glBegin(GL_POINTS);

	for (i = 0; i < nr_puncte; i++)
		glVertex2i(X[i], Y[i]);
	glEnd();

	glFlush(); // proceseaza procedurile OpenGL cat mai rapid
}

void functie_pentru_click(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		//store the x,y value where the click happened
		cout << "click " << x << " " << y << endl;
		X[nr_puncte] = x;
		Y[nr_puncte] = 700 - y;
		nr_puncte++;

	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv); // initializare GLUT
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // se utilizeaza un singur buffer | modul de colorare RedGreenBlue (= default)
	glutInitWindowPosition(100, 100); // pozitia initiala a ferestrei de vizualizare (in coordonate ecran)
	glutInitWindowSize(1200, 700); // dimensiunile ferestrei
	glutCreateWindow("Puncte & Segmente"); // creeaza fereastra, indicand numele ferestrei de vizualizare - apare in partea superioara

	glMatrixMode(GL_PROJECTION);  // se precizeaza este vorba de o reprezentare 2D, realizata prin proiectie ortogonala
	gluOrtho2D(0.0, 1200.0, 0.0, 700.0); // sunt indicate coordonatele extreme ale ferestrei de vizualizare

	glClearColor(1.0, 1.0, 1.0, 0.0); // precizeaza culoarea de fond a ferestrei de vizualizare


	glutMouseFunc(functie_pentru_click);
	glutDisplayFunc(desen); // procedura desen este invocata ori de cate ori este nevoie
	glutMainLoop(); // ultima instructiune a programului, asteapta (eventuale) noi date de intrare
	return 0;
}
