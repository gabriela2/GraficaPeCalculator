//SURSA:  lighthouse3D:  http://www.lighthouse3d.com/tutorials/glut-tutorial/keyboard-example-moving-around-the-world/

#include<gl/freeglut.h>
#include<math.h>
// angle of rotation for the camera direction
float angle=0.0;
// actual vector representing the camera's direction
float lx=0.0f,lz=-1.0f;
// XZ position of the camera
float x=0.0f,z=5.0f;

void init (void)  // initializare fereastra de vizualizare
{
	glClearColor (0.0, 1.0, 1.0, 0.0); // precizeaza culoarea de fond a ferestrei de vizualizare

}
void init1 (void)  // initializare fereastra de vizualizare
{
	glClearColor (0.0, 0.0, 0.0, 0.0); // precizeaza culoarea de fond a ferestrei de vizualizare

}


enum{IARNA,PRIMAVARA};
int rendermode= IARNA;

void menu(int selection)
{
  rendermode = selection;
  glutPostRedisplay();
}

void changeSize(int w, int h)
{

// Prevent a divide by zero, when window is too short
// (you cant make a window of zero width).
if (h == 0)
h = 1;
float ratio = w * 1.0 / h;

// Use the Projection Matrix
glMatrixMode(GL_PROJECTION);

// Reset Matrix
glLoadIdentity();

// Set the viewport to be the entire window
glViewport(0, 0, w, h);

// Set the correct perspective.
gluPerspective(45.0f, ratio, 0.1f, 100.0f);

// Get Back to the Modelview
glMatrixMode(GL_MODELVIEW);
}

void drawTree() {

	//glColor3f(1.0f, 1.0f, 1.0f);

	// Draw Body
	glTranslatef(0.0f, 0.75f, 0.0f);
	//makeCylinder(3, 0.5);
	GLUquadric *obj = gluNewQuadric();
	glColor3f(0.64f, 0.16, 0.16f);
	glPushMatrix();
	glRotatef(-90, 1.0, 0.0, 0.0);
	gluCylinder(obj,0.2,0.1,1,3,10);
	glPopMatrix();


	// Draw Head
	glTranslatef(-0.25f, 1.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glutSolidSphere(0.25f, 20, 20);

	glTranslatef(-0.3f, 0.1f, 0.0f);
	glColor3f(0.0f, 0.9f, 0.0f);
	glutSolidSphere(0.25f, 20, 20);

	glTranslatef(0.75f, -0.1f, 0.0f);
	glColor3f(0.0f, 0.8f, 0.0f);
	glutSolidSphere(0.25f, 20, 20);

	glTranslatef(0.3f, 0.1f, 0.0f);
	glColor3f(0.0f, 0.9f, 0.0f);
	glutSolidSphere(0.25f, 20, 20);

	glTranslatef(-0.25f, 0.2f, 0.0f);
	glColor3f(0.0f, 0.7, 0.0f);
	glutSolidSphere(0.25f, 20, 20);

	glTranslatef(-0.3f, 0.f, 0.0f);
	glColor3f(0.0f, 0.85f, 0.0f);
	glutSolidSphere(0.25f, 20, 20);

    glTranslatef(-0.3f, 0.f, 0.0f);
	glColor3f(0.0f, 0.75f, 0.0f);
	glutSolidSphere(0.25f, 20, 20);

    glTranslatef(0.1f, 0.2f, 0.0f);
	glColor3f(0.0f, 0.95f, 0.0f);
	glutSolidSphere(0.25f, 20, 20);

	glTranslatef(0.2f, 0.f, 0.0f);
	glColor3f(0.0f, 0.65f, 0.0f);
	glutSolidSphere(0.25f, 20, 20);

	glTranslatef(0.3f, 0.f, 0.0f);
	glColor3f(0.0f, 0.55f, 0.0f);
	glutSolidSphere(0.25f, 20, 20);
}

void drawSnowMan() {

	glColor3f(1.0f, 1.0f, 1.0f);

// Draw Body
	glTranslatef(0.0f ,0.75f, 0.0f);
	glutSolidSphere(0.75f,20,20);

// Draw Head
	glTranslatef(0.0f, 1.0f, 0.0f);
	glutSolidSphere(0.25f,20,20);

// Draw Eyes
	glPushMatrix();
	glColor3f(0.0f,0.0f,0.0f);
	glTranslatef(0.05f, 0.10f, 0.18f);
	glutSolidSphere(0.05f,10,10);
	glTranslatef(-0.1f, 0.0f, 0.0f);
	glutSolidSphere(0.05f,10,10);
	glPopMatrix();

// Draw Nose
	glColor3f(1.0f, 0.5f , 0.5f);
	glutSolidCone(0.08f,0.5f,10,2);
}



void renderScene(void) {

	// Clear Color and Depth Buffers

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();
	// Set the camera
	gluLookAt(	x, 1.0f, z,
			x+lx, 1.0f,  z+lz,
			0.0f, 1.0f,  0.0f);

        // Draw ground
    switch(rendermode){
        case IARNA:
            init1();
            glColor3f(0.9f, 0.9f, 0.9f);
            glBegin(GL_QUADS);
                glVertex3f(-100.0f, 0.0f, -100.0f);
                glVertex3f(-100.0f, 0.0f,  100.0f);
                glVertex3f( 100.0f, 0.0f,  100.0f);
                glVertex3f( 100.0f, 0.0f, -100.0f);
            glEnd();

            // Draw 36 SnowMen
            for(int i = -3; i < 3; i++)
                for(int j=-3; j < 3; j++) {
                    glPushMatrix();
                    glTranslatef(i*10.0,0,j * 10.0);
                    drawSnowMan();
                    glPopMatrix();
                }
            break;

        case PRIMAVARA:
            init();
            glColor3f(0.0, 0.6, 0.0);
            glBegin(GL_QUADS);
                glVertex3f(-100.0f, 0.0f, -100.0f);
                glVertex3f(-100.0f, 0.0f,  100.0f);
                glVertex3f( 100.0f, 0.0f,  100.0f);
                glVertex3f( 100.0f, 0.0f, -100.0f);
            glEnd();
            glColor3f(0.0, 0.8, 1.0);
            for(int i = -3; i < 3; i++)
                for(int j=-3; j < 3; j++) {
                    glPushMatrix();
                    glTranslatef(i*10.0,0,j * 10.0);
                    drawTree();
                    glPopMatrix();
                }
            break;

    };

	glutSwapBuffers();
}

void processNormalKeys(unsigned char key, int x, int y)
{

	switch (key) {
		case 'l' :
			angle -= 0.01f;
			lx = sin(angle);
			lz = -cos(angle);
			break;

	}
if (key == 27)
exit(0);
}

void processSpecialKeys(unsigned char key, int xx, int yy) {

	float fraction = 0.1f;

	switch (key) {
		case 'a' :
			angle -= 0.01f;
			lx = sin(angle);
			lz = -cos(angle);
			break;
		case 'd' :
			angle += 0.01f;
			lx = sin(angle);
			lz = -cos(angle);
			break;
		case 'w':
			x += lx * fraction;
			z += lz * fraction;
			break;
		case 's':
			x -= lx * fraction;
			z -= lz * fraction;
			break;
	}
}


int main(int argc, char **argv) {

	// init GLUT and create window

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(320,320);
	glutCreateWindow("Scena 3D cu oameni de zapada");

	// register callbacks
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);
	glutKeyboardFunc(processSpecialKeys);
	//glutSpecialFunc(processSpecialKeys);

	// OpenGL init
	glEnable(GL_DEPTH_TEST);
	glutCreateMenu(menu);
    glutAddMenuEntry("Iarna", IARNA);
    glutAddMenuEntry("Primavara", PRIMAVARA);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

	// enter GLUT event processing cycle
	glutMainLoop();

	return 1;
}

