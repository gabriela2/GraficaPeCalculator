#include <gl/freeglut.h> // nu trebuie uitat freeglut.h (sau glut.h sau gl.h & glu.h)
#include <iostream>
using namespace std;
//Nu se intersecteaza
/*
int X[4]={220,400,150,300};
int Y[4]={400,300,400,300};
// se intersecteaza
*/
int X[4]={200, 200 ,300, 300};
int Y[4]={200,400,400,100};
float panta[2];
float pIntersectie[2];
int nr_puncte;

float ecuatie(float x, float y, char tip[]){
    if(strcmp(tip,"AB")==0){
        return x*(Y[1]-Y[0])-y*(X[1]-X[0])-(X[0]*Y[1]-X[1]*Y[0]);
    }
    else if(strcmp(tip,"CD")==0){
        return x*(Y[3]-Y[2])-y*(X[3]-X[2])-(X[2]*Y[3]-X[3]*Y[2]);
    }

}

void desen(void) // procedura desenare
{
	glClear(GL_COLOR_BUFFER_BIT); // reprezentare si colorare fereastra de vizualizare
	int i,x,y;
	glPointSize(20);
	glLineWidth(15);
	glColor3f(1, 0, 0);
    glBegin(GL_LINES);

	for (i = 0; i < 4; i++)
		glVertex2i(X[i], Y[i]);

	glEnd();
	panta[0]=(Y[1]-Y[0])/(X[1]-X[0]);
	panta[1]=(Y[3]-Y[2])/(X[3]-X[2]);
	int determinant1=X[0]*(Y[1]-Y[2])-Y[0]*(X[1]-X[2])+(X[1]*Y[2]-X[2]*Y[1]);
	int determinant2=X[1]*(Y[2]-Y[3])-Y[1]*(X[2]-X[3])+(X[2]*Y[3]-X[3]*Y[2]);
    if ( determinant1!= 0 && determinant2 != 0){
        cout<<"Punctele sunt necoliniare"<<endl;
        float ecC=ecuatie(X[2],Y[2],"AB");
        float ecD=ecuatie(X[3],Y[3],"AB");
        if(ecC*ecD < 0){
            cout<<"Punctele se intersecteaza"<<endl;
            float c1=Y[0]-panta[0]*X[0];
            float c2=Y[2]-panta[1]*X[2];
            cout<<"Ecuatia AB: Y = "<<panta[0]<<" * X +"<<c1<<endl;
            cout<<"Ecuatia CD: Y = "<<panta[1]<<" * X +"<<c2<<endl;
            pIntersectie[0]=(c2-c1)/(panta[0]-panta[1]);
            pIntersectie[1]= panta[0]*pIntersectie[0]+c1;
            cout<<"Intersectia celor doua segmente este Punctul de coordonate ("<<pIntersectie[0]<<" , "<<pIntersectie[1]<<") "<<endl;
            glColor3f(0, 0, 0);
            glEnable(GL_POINT_SMOOTH);
            glBegin(GL_POINTS);
                glVertex2i(pIntersectie[0], pIntersectie[1]);
            glEnd();
            glDisable(GL_POINT_SMOOTH);

        }
        else
            cout<<"Punctele nu se intersecteaza"<<endl;

    }

	glFlush(); // proceseaza procedurile OpenGL cat mai rapid
}
/*
void functie_pentru_click(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		//store the x,y value where the click happened
		cout << "click " << x << " " << y << endl;
		X[nr_puncte] = x;
		Y[nr_puncte] = 700 - y;
		nr_puncte++;
        if (nr_puncte==4)
            return;
	}

}

*/
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


	//glutMouseFunc(functie_pentru_click);
    glutDisplayFunc(desen); // procedura desen este invocata ori de cate ori este nevoie
	glutMainLoop(); // ultima instructiune a programului, asteapta (eventuale) noi date de intrare

	return 0;
}
