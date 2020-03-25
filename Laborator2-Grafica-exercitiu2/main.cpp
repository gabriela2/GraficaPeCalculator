#include <gl/freeglut.h> // nu trebuie uitat freeglut.h (sau glut.h sau gl.h & glu.h)
#include <iostream>
using namespace std;
float X[100];
float Y[100];
int nr_puncte;
float x_intersect[100];
float y_intersect[100];
int nr_intersectari;

int intersectii[99];

float min_X = 0.0;
float max_X = 1200.0;
float min_Y = 0.0;
float max_y = 700.0;

void desen(void) // procedura desenare
{
	glClear(GL_COLOR_BUFFER_BIT); // reprezentare si colorare fereastra de vizualizare
	int i;

	// desenarea linilor intre puncte
	/*glLineWidth(10);
	glBegin(GL_LINE_STRIP);*/

	for (i = 0; i < nr_puncte; i++) {

		if (intersectii[i] == 0) {
		    glLineWidth(10);
            glBegin(GL_LINE_STRIP);
			glColor3f(0, 1, 1);
			glVertex2f(X[i], Y[i]);
			if (X[i + 1] != 0)
                glVertex2f(X[i + 1], Y[i + 1]);
            glEnd();
		}
		else {
            glLineWidth(20);
            glBegin(GL_LINE_STRIP);
			glColor3f(0, 0, 1);
			glVertex2f(X[i], Y[i]);
			if (X[i + 1] != 0)
                glVertex2f(X[i + 1], Y[i + 1]);
            glEnd();
		}
	}



	// desenarea punctelor
	glPointSize(10);
	glColor3f(0, 0, 0);

    glEnable(GL_POINT_SMOOTH);
	glBegin(GL_POINTS);

	for (i = 0; i < nr_puncte; i++)
		glVertex2f(X[i], Y[i]);

	glEnd();
    glDisable(GL_POINT_SMOOTH);

		// desenarea intersectarilor
		glColor3f(0, 0, 1);
			glBegin(GL_POINTS);

			for (i = 0; i < nr_intersectari; i++)
				glVertex2f(x_intersect[i], y_intersect[i]);
			glEnd();
	glFlush(); // proceseaza procedurile OpenGL cat mai rapid
}

bool ex1_verificare(float xA, float yA, float xB, float yB, float xC, float yC, float xD, float yD) {
	// determinam ecuatia dreptei [AB]
	// x(yB-yA) + y(xA-xB) = 0
	// daca punctul C sau D apartine dreptei, este colin:
	//(x - xb)/(xb-xa)=(y-yb)/(yb-ya) ==> (x-xb)(yb-ya)=(y-yb)(xb-xa) ==>
	//	x * yb - x * ya + xb * ya = y * xb - y * xa + yb * xa
	//	x(yb-ya) + xb*ya = y(xb-xa)+yb*xa
	//	dreapta pt AB: x(yB - yA) - y(xB - xA) + xB * yA - yB * xA = 0
	//	dreapta pt CD: x(yD - yC) - y(xD - xC) + xD * yC - yD * xC = 0
	float x_inters = 0.0;
	float y_inters = 0.0;
	float c1, m1, c2, m2;
	bool intersectie = false;


	m1 = (yB - yA) / (xB - xA);
	c1 = yA - m1 * xA;
	m2 = (yD - yC) / (xD - xC);
	c2 = yC - m2 * xC;

	//este colin
	if ((xC * (yB - yA) + yC * (xA - xB) == 0) || (xD * (yB - yA) + yD * (xA - xB) == 0)) intersectie = false;
	else
	{
		// se intersecteaza
		if ((((xC * (yB - yA) - yC * (xB - xA) + xB * yA - yB * xA) * (xD * (yB - yA) - yD * (xB - xA) + xB * yA - yB * xA)) < 0) && (((xA * (yD - yC) - yA * (xD - xC) + xD * yC - yD * xC) * (xB * (yD - yC) - yB * (xD - xC) + xD * yC - yD * xC))) < 0) {
			if (xB != xC && yB != yC) {

				x_inters = (c2 - c1) / (m1 - m2);
				y_inters = m1 * x_inters + c1;

				x_intersect[nr_intersectari] = x_inters;
				y_intersect[nr_intersectari] = y_inters;

				nr_intersectari++;
				intersectie = true;
			}
			else intersectie = false;
			//cout << "Puncte de intersectie\nx: " << x_inters << ", y:" << y_inters << endl;
		}
		// nu se intersecteaza
		else intersectie = false;
	}

	return intersectie;
}

void ex2_intersectare() {
	float x1, y1, x2, y2, x3, y3, x4, y4;

	for (int i = 0; i < nr_puncte; i++) {
		// luam perechi de 2 puncte
		if (intersectii[((2 * i) + 1) / 2] == 0) {
			x1 = X[i];					//xA
			y1 = Y[i];					//yA
			x2 = X[i + 1];				//xB
			y2 = Y[i + 1];				//yB

			for (int j = 0; j < nr_puncte; j++) {
				if (j != i && x2 != 0) {
					x3 = X[j];				//xC
					y3 = Y[j];				//yC
					x4 = X[j + 1];			//xD
					y4 = Y[j + 1];			//yD
					if (ex1_verificare(x1, y1, x2, y2, x3, y3, x4, y4)) {
						cout << "dreapta " << x1 << "->" << x2 << " se int. cu " << x3 << "->" << x4 << endl;
						intersectii[(2 * i + 1) / 2] = 1;
						intersectii[(2 * j + 1) / 2] = 1;
					}
				}
			}
		}
	}

	cout << "---------------------------------\n";
	for (int k = 0; k < 10; k++)
		cout << k << ". " << intersectii[k] << " " << endl;
	cout << "---------------------------------\n";
}

void functie_pentru_click(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		//store the x,y value where the click happened
		X[nr_puncte] = x;
		Y[nr_puncte] = max_y - y;
		nr_puncte++;
		cout << x << " " << max_y - y << endl;
		if (nr_puncte >= 4) ex2_intersectare();
		/*
		if (nr_puncte == 4) {
			ex1_verificare(X[0], Y[0], X[1], Y[1], X[2], Y[2], X[3], Y[3]);
		}
		*/
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
	gluOrtho2D(min_X, max_X, min_Y, max_y); // sunt indicate coordonatele extreme ale ferestrei de vizualizare

	glClearColor(1.0, 1.0, 1.0, 0.0); // precizeaza culoarea de fond a ferestrei de vizualizare


	glutMouseFunc(functie_pentru_click);
	glutDisplayFunc(desen); // procedura desen este invocata ori de cate ori este nevoie
	glutMainLoop(); // ultima instructiune a programului, asteapta (eventuale) noi date de intrare

	return 0;
}

