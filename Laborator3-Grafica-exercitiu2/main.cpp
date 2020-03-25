#include <gl/freeglut.h> // nu trebuie uitat freeglut.h (sau glut.h sau gl.h & glu.h)
#include <iostream>
#include <math.h>
using namespace std;

GLint winWidth = 600, winHeight = 600;							//marimea ferestrei
GLfloat xx0 = 20.0, yy0 = 20.0, zz0 = 20.0;						//punct de observare
GLfloat xref = 0.0, yref = 0.0, zref = 0.0;						//punctul de referinta
GLfloat Vx = 8.0, Vy = 0.0, Vz = -8.0;
GLfloat xwMin = -20.0, ywMin = -20.0, xwMax = 20.0, ywMax = 20.0;
GLfloat dnear = 0.0, dfar = 50.0;								//distanta de observare


int A[] = { 5, 9, 0 };
int B[] = { 2, -3, 0 };
int C[] = { 9, 8, 0 }; // C = 9, 10, 0 pt convexitate
int D[3], O1[3], O2[3], M[3], n[3], perpendicular[3];
float Z[4];				// pentru calculul produselor vectoriale


void Calcul();

void produs_vectorial(int V[], int U[], int Produs_vectorial[]) {
	Produs_vectorial[0] = V[1] * U[2] - V[2] * U[1];
	Produs_vectorial[1] = V[2] * U[0] - V[0] * U[2];
	Produs_vectorial[2] = V[0] * U[1] - V[1] * U[0];
}

void init(void)
{
	Calcul();
	glClearColor(1.0, 1.0, 1.0, 0.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(xx0, yy0, zz0, xref, yref, zref, Vx, Vy, Vz);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(xwMin, xwMax, ywMin, ywMax, dnear, dfar);
}

void convexitate(float xA, float yA, float xB, float yB, float xC, float yC, float xD, float yD) {
	Z[0] = (xB - xA) * (yD - yB) - (yB - yA) * (xD - xB);
	Z[1] = (xD - xB) * (yC - yD) - (yD - yB) * (xC - xD);
	Z[2] = (xC - xD) * (yA - yC) - (yC - yD) * (xA - xC);
	Z[3] = (xA - xC) * (yB - yA) - (yA - yC) * (xB - xA);

	bool concav = true;

	cout << "A:" << Z[0] << " B:" << Z[1] << " C:" << Z[2] << " D:" << Z[3] << endl;
	for (int i = 1; i < 4; i++) {
		if ((Z[i] > 0.0 && Z[0] > 0.0) || (Z[i] < 0.0 && Z[0] < 0.0)) concav = false;
		else {
			concav = true;
			break;
		}
	}
	if (concav) cout << "Patrulaterul este concav." << endl;
	else cout << "Patrulatrul este convex." << endl;
}

void interior_sau_pe_latura(float xA, float yA, float xB, float yB, float xC, float yC, float xM, float yM) {
	if (((xM * (yB - yA) - yM * (xB - xA) + xB * yA - yB * xA) == 0) || ((xM * (yC - yB) - yM * (xC - xB) + xC * yB - yC * xB) == 0) || ((xM * (yA - yC) - yM * (xA - xC) + xA * yC - yA * xC) == 0)) {
		cout << "Punctul M(" << xM << ", " << yM << ") se afla pe una din laturile triunghiului ABC." << endl;
	}
	else {
		float aria1 = abs(0.5 * ((xB * yM) - (xM * yB) - (xA * yM) + (xM * yA) + (xA * yB) - (xB * yA)));
		float aria2 = abs(0.5 * ((xM * yC) - (xC * yM) - (xA * yC) + (xC * yA) + (xA * yM) - (xM * yA)));
		float aria3 = abs(0.5 * ((xB * yC) - (xC * yB) - (xM * yC) + (xC * yM) + (xM * yB) - (xB * yM)));

		float aria_totala = aria1 + aria2 + aria3;

		float arie_triunghi = abs(0.5 * ((xB * yC) - (xC * yB) - (xA * yC) + (xC * yA) + (xA * yB) - (xB * yA)));

		if (aria_totala == arie_triunghi) cout << "Punctul M(" << xM << ", " << yM << ") se afla in interiorul triunghiului ABC." << endl;
		else cout << "Punctul M(" << xM << ", " << yM << ") se afla inafara triunghiului ABC." << endl;
	}
}

void Calcul() {
	float Pabxbc, A_, B_, C_, D_, xM, yM, zM;
	// Ex. 2, punctul a)
	// Determinati un punct M in interiorul sau pe laturile triunghiului;
	for (int i = 0; i < 3; i++) M[i] = (A[i] + B[i] + C[i]) / 3;

	// Ex. 2, punctul b)
	// Deteminati D in planul triunghiului asa incat ABDC sa fie un patrulater convex;
	for (int i = 0; i < 3; i++) D[i] = B[i] + C[i] - A[i];

	// Ex. 2, punctul c)
	// Determinati vectorul n normal la patrulaterul ABDC;
	A_ = (B[1] * C[2]) - (C[1] * B[2]) - (A[1] * C[2]) + (C[1] * A[2]) + (A[1] * B[2]) - (B[1] * A[2]);
	B_ = -(B[0] * C[2]) + (C[0] * B[2]) + (A[0] * C[2]) - (C[0] * A[2]) - (A[0] * B[2]) + (B[0] * A[2]);
	C_ = (B[0] * C[1]) - (C[0] * B[1]) - (A[0] * C[1]) + (C[0] * A[1]) + (A[0] * B[1]) - (B[0] * A[1]);
	D_ = -A[2] * ((B[0] * C[1]) - (C[0] * B[1])) + B[2] * ((A[0] * C[1]) - (C[0] * A[1])) - C[2] * ((A[0] * B[1]) - (B[0] * A[1]));
	n[0] = A_ / sqrt(A_ * A_ + B_ * B_ + C_ * C_);
	n[1] = B_ / sqrt(A_ * A_ + B_ * B_ + C_ * C_);
	n[2] = C_ / sqrt(A_ * A_ + B_ * B_ + C_ * C_);

	// Ex. 2, punctul d)
	// Folosind M si n construiti un punct O1 in fata patrulaterului si un punct O2 in spatele acestuia;
	for (int i = 0; i < 3; i++) {
		O1[i] = M[i] + 2 * n[i];
		O2[i] = M[i] - 2 * n[i];
	}

	// Pabxbc = (yB - yA) * (zC - zB) - (zB - zA) * (yC - yB) - (xB - xA) * (zC - zB) + (zB - zA) * (xC - xB) + (xB - xA) * (yC - yB) - (yB - yA) * (xC - xB);
	// Verificare:
	if ((M[0] * A_ + M[1] * B_ + M[2] * C_ + D_) == 0) interior_sau_pe_latura(A[0], A[1], B[0], B[1], C[0], C[1], M[0], M[1]);
	if ((D[0] * A_ + D[1] * B_ + D[2] * C_ + D_) == 0) convexitate(A[0], A[1], B[0], B[1], C[0], C[1], D[0], D[1]);

	perpendicular[0] = n[0];
	perpendicular[1] = n[1];
	perpendicular[2] = 0;
}

void desen2(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_LINE);

	// Desenarea punctelor
	glPointSize(25);
	glBegin(GL_POINTS);
		glColor3f(1.0, 0.0, 0.0);
		glVertex3iv(A);
		glColor3f(0.4, 0.4, 0.4);
		glVertex3iv(B);
		glColor3f(0.5, 0.5, 1.5);
		glVertex3iv(D);
		glColor3f(0.0, 0.0, 1.0);
		glVertex3iv(C);
		glColor3f(0.5, 0.5, 0.5);
		glVertex3iv(M);
	//	glColor3f(1.0, 0.0, 0.0);
	//	glVertex3iv(n);				//desenarea normalei
	glEnd();

	// Desenarea patrulaterului
	glLineWidth(6.0);
	glFrontFace(GL_CW);
	glCullFace(GL_BACK);
	glShadeModel(GL_FLAT);
	glBegin(GL_POLYGON);
		glColor3f(1.0, 0.0, 0.0);
		glVertex3iv(A);
		glColor3f(0.0, 1.0, 0.0);
		glVertex3iv(B);
		glColor3f(0.5, 0.5, 1.0);
		glVertex3iv(D);
		glColor3f(0.0, 0.0, 1.0);
		glVertex3iv(C);
	glEnd();

	glutPostRedisplay();

	glFlush();
	// Desenarea normalei la suprafata
	//glBegin(GL_POLYGON);
	//	glColor3f(0.0, 0.0, 1.0);
	//	glVertex3iv(n);
	//	glVertex3iv(perpendicular);
	//glEnd();

	/*
	TRIUNGHIUL ABC
	glLineWidth(6.0);
	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3iv(A);
	glVertex3iv(B);
	glVertex3iv(C);
	glEnd();
	*/
}

void mouse2(int button, int state, int x, int y)
{
	switch (button) {
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN)
			//xx0 = 13.0, yy0 = 11.0, zz0 = 14.0;
			xx0 = 20.0, yy0 = 20.0, zz0 = 20.0;
		init();
		desen2();
		break;
	case GLUT_RIGHT_BUTTON:
		if (state == GLUT_DOWN)
			//xx0 = -7.0, yy0 = -9.0, zz0 = -6.0;
			xx0 = -20.0, yy0 = -20.0, zz0 = -20.0;
		init();
		desen2();
		break;

	}
}

void reshapeFcn(GLint newWidth, GLint newHeight)
{
	glViewport(0, 0, newWidth, newHeight);

	winWidth = newWidth;
	winHeight = newHeight;
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("Poligoane in context 3D. Fata si spatele unui poligon");

	init();
	glutMouseFunc(mouse2);
	glutDisplayFunc(desen2);
	glutMainLoop();
}
