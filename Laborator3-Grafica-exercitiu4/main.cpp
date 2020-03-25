#include <gl/freeglut.h> // nu trebuie uitat freeglut.h (sau glut.h sau gl.h & glu.h)
#include <iostream>
#include <math.h>
using namespace std;

GLint winWidth = 600, winHeight = 600;							//marimea ferestrei
GLfloat xx0 = 20.0, yy0 = 20.0, zz0 = 20.0;						//punct de observare
GLfloat xref = 0.0, yref = 0.0, zref = 0.0;						//punctul de referinta
GLfloat Vx = 8.0, Vy = 0.0, Vz = -8.0;
GLfloat xwMin = -20.0, ywMin = -20.0, xwMax = 20.0, ywMax = 20.0;
GLfloat dnear = 0.0, dfar = 60.0;								//distanta de observare

int puncte[5][3]={{2,2,0},{15,2,0},{5,5,0},{15,15,0},{2,15,0}};
int vectori[5][3];
int ProdusV[5][3];
int semn[5];
float determinant[4];
float n[3];


void ConvexConcav(float xA, float yA, float xB, float yB, float xC, float yC, float xD, float yD) {
	determinant[0] = (xB - xA) * (yD - yB) - (yB - yA) * (xD - xB);
	determinant[1] = (xD - xB) * (yC - yD) - (yD - yB) * (xC - xD);
	determinant[2] = (xC - xD) * (yA - yC) - (yC - yD) * (xA - xC);
	determinant[3] = (xA - xC) * (yB - yA) - (yA - yC) * (xB - xA);

	bool concav = true;

	cout << "determinantA:" << determinant[0] <<endl;
	cout << "determinantB:" << determinant[1] <<endl;
	cout << "determinantC:" << determinant[2] <<endl;
	cout << "determinantD:" << determinant[3] <<endl;
	for (int i = 0; i < 4; i++) {
	    for(int j = i+1; j < 4; j++){
            if((determinant[i]> 0.0 && determinant[j]<0.0)||(determinant[i]< 0.0 && determinant[j]>0.0)){
                concav=false;
                break;
            }
	    }
	}
	if (concav == true)
        cout << "Patrulater concav." << endl;
	else
        cout << "Patrulater convex." << endl;
}


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

void ProdusVectorial(int x1,int y1,int z1,int x2,int y2,int z2, int *x3,int *y3,int *z3){
    *x3= y1 * z2 - y2 * z1;
    *y3= x2 * z1 - x1 * z2;
    *z3= x1 * y2 - x2 * y1;

}

void Verificare(){

   /* for(int i=0;i<5;i++){
        for(int j=0;j<3;j++){
                cin>>puncte[i][j];
        }
    }
    */
    for(int i=0;i<5;i++){
        for(int j=0;j<3;j++){
            if(i!=4)
                vectori[i][j]=puncte[i+1][j]-puncte[i][j];
            else
                vectori[i][j]=puncte[i][j]- puncte[0][j];
        }
    }

    for(int i=0;i<5;i++){
            if(i!=4)
                ProdusVectorial(vectori[i][0],vectori[i][1],vectori[i][2],vectori[i+1][0],vectori[i+1][0],vectori[i+1][0],&ProdusV[i][0],&ProdusV[i][1],&ProdusV[i][2]);
            else
                ProdusVectorial(vectori[i][0],vectori[i][1],vectori[i][2],vectori[0][0],vectori[0][0],vectori[0][0],&ProdusV[i][0],&ProdusV[i][1],&ProdusV[i][2]);
        }
    for(int i=0;i<5;i++){
        if(ProdusV[i][2]<0)
            semn[i]=-1;
        else
            semn[i]=1;
    }


    semn[3]=-1;


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



	// Desenarea punctelor


	glLineWidth(5.0);
	glFrontFace(GL_CW);
	glCullFace(GL_BACK);
	glShadeModel(GL_FLAT);
	glBegin(GL_POLYGON);
		glColor3f(0.0, 0.0, 0.0);
		glVertex3i(puncte[0][0],puncte[0][1],puncte[0][2]);
		glVertex3i(puncte[1][0],puncte[1][1],puncte[1][2]);
		glVertex3i(puncte[2][0],puncte[2][1],puncte[2][2]);
		glVertex3i(puncte[3][0],puncte[3][1],puncte[3][2]);
		glVertex3i(puncte[4][0],puncte[4][1],puncte[4][2]);
		glVertex3i(puncte[0][0],puncte[0][1],puncte[0][2]);
	glEnd();

    glPointSize(10);
	glEnable(GL_POINT_SMOOTH);
	glBegin(GL_POINTS);
	for(int i=0;i<5;i++){
        if(semn[i]==-1){
            glColor3f(1.0,1.0,0.0);
            glVertex2i(puncte[i][0],puncte[i][1]);
        }
        else{
            glColor3f(1.0,0.0,1.0);
            glVertex2i(puncte[i][0],puncte[i][1]);
        }
	}
	glEnd();
	glDisable(GL_POINT_SMOOTH);



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
