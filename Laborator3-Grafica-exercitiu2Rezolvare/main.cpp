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


int A[] = { 2, 2, 0 };
int B[] = { 20, 2, 0 };
int C[] = { 6, 10, 0 };
int Min[] = { 5, 5, 0 };
int Mon[] = { 10, 2 , 0};
int Mout[] = { 20, 20, 0};

void VerificarePunctM(float xA, float yA, float xB, float yB, float xC, float yC, float xM, float yM) {
	if    (   (( xM * (yB - yA) - yM * (xB - xA) + xB * yA - yB * xA) == 0) ||
              (( xM * (yC - yB) - yM * (xC - xB) + xC * yB - yC * xB) == 0) ||
              (( xM * (yA - yC) - yM * (xA - xC) + xA * yC - yA * xC) == 0)) {

                  cout << "Punctul M(" << xM << ", " << yM << ") se afla pe una din laturile triunghiului ABC." << endl;
    }
	else {
		float ariaAMB = abs(0.5 * ((xB * yM) - (xM * yB) - (xA * yM) + (xM * yA) + (xA * yB) - (xB * yA)));
		float ariaAMC = abs(0.5 * ((xM * yC) - (xC * yM) - (xA * yC) + (xC * yA) + (xA * yM) - (xM * yA)));
		float ariaBMC = abs(0.5 * ((xB * yC) - (xC * yB) - (xM * yC) + (xC * yM) + (xM * yB) - (xB * yM)));
		float ariaTriunghiuri = ariaAMB + ariaAMC + ariaBMC;

		float arieABC = abs(0.5 * ((xB * yC) - (xC * yB) - (xA * yC) + (xC * yA) + (xA * yB) - (xB * yA)));

		if (arieABC == ariaTriunghiuri)
            cout << "Punctul M(" << xM << ", " << yM << ") se afla in interiorul triunghiului ABC." << endl;
		else
            cout << "Punctul M(" << xM << ", " << yM << ") se afla inafara triunghiului ABC." << endl;
	}
}

void Verificare(){
    VerificarePunctM(A[0], A[1], B[0], B[1], C[0], C[1], Min[0], Min[1]);
    cout<<"............................................................."<<endl;
    VerificarePunctM(A[0], A[1], B[0], B[1], C[0], C[1], Mon[0], Mon[1]);
    cout<<"............................................................."<<endl;
    VerificarePunctM(A[0], A[1], B[0], B[1], C[0], C[1], Mout[0], Mout[1]);
    cout<<"............................................................."<<endl;
}

void init(void)
{
    Verificare();

	glClearColor(1.0, 1.0, 1.0, 0.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(xx0, yy0, zz0, xref, yref, zref, Vx, Vy, Vz);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(xwMin, xwMax, ywMin, ywMax, dnear, dfar);
}




void desen2(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_LINE);
    glColor3f(0.0, 0.0, 0.0);

    glRasterPos2i(2, 0);
    const unsigned char* t1 = reinterpret_cast<const unsigned char*>("A");
    glutBitmapString(GLUT_BITMAP_HELVETICA_10, t1);

    glRasterPos2i(20, 0);
    const unsigned char* t2 = reinterpret_cast<const unsigned char*>("B");
    glutBitmapString(GLUT_BITMAP_HELVETICA_10, t2);

    glRasterPos2i(6, 12);
    const unsigned char* t3 = reinterpret_cast<const unsigned char*>("C");
    glutBitmapString(GLUT_BITMAP_HELVETICA_10, t3);

    glRasterPos2i(7, 8);
    const unsigned char* t4 = reinterpret_cast<const unsigned char*>("M interior (5,5)");
    glutBitmapString(GLUT_BITMAP_HELVETICA_10, t4);

    glRasterPos2i(20,30);
    const unsigned char* t5 = reinterpret_cast<const unsigned char*>("M exterior (20,20)");
    glutBitmapString(GLUT_BITMAP_HELVETICA_10, t5);

    glRasterPos2i(10, 0);
    const unsigned char* t6 = reinterpret_cast<const unsigned char*>("M latura (10,2)");
    glutBitmapString(GLUT_BITMAP_HELVETICA_10, t6);

	// Desenarea punctelor
	glPointSize(10);
	glEnable(GL_POINT_SMOOTH);
	glBegin(GL_POINTS);
        glColor3f(0.0, 0.0, 0.0);
		glVertex3iv(A);
		glColor3f(0.0, 0.0, 0.0);
		glVertex3iv(B);
		glColor3f(0.0, 0.0, 0.0);
		glVertex3iv(C);
		glColor3f(1.0, 0.0, 0.0);
		glVertex3iv(Min);
        glVertex3iv(Mout);
        glVertex3iv(Mon);

	glEnd();
	glDisable(GL_POINT_SMOOTH);

	// Desenarea patrulaterului
	glLineWidth(5.0);
	glFrontFace(GL_CW);
	glCullFace(GL_BACK);
	glShadeModel(GL_FLAT);
	glBegin(GL_POLYGON);
		glColor3f(0.0, 0.0, 0.0);
		glVertex3iv(A);
		glVertex3iv(B);
		glVertex3iv(C);
	glEnd();

	glutPostRedisplay();

	glFlush();

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
