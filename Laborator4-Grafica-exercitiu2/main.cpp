

#include<windows.h>
#include <gl/freeglut.h>


double i = 0.0;
double j = 0.0;
double alpha = 1.0;
void init(void)
{
   glClearColor (1.0, 1.0, 1.0, 0.0);
   glMatrixMode (GL_PROJECTION);
   glOrtho(-20.0, 1500.0, 0.0, 1500.0, -1.0, 1.0);

}
void deseneazaScena(void)
{
   glClear(GL_COLOR_BUFFER_BIT);
   // axa de rostogolire in afara transformarii
   glColor3f(0,0,0);
   glBegin(GL_LINES);
   glVertex2i(-30,300);
   glVertex2i(780,300);
   glEnd();


   // patratul
   glPushMatrix ( );
   glTranslated (i, 300.0, 0.0);
   glPushMatrix ( );
   glRotated (j, 0.0, 0.0, 1.0);
   glTranslated(-30.0, -30.0, 0.0);
   glBegin(GL_POLYGON);
   glColor3f(1, 0.5, 1);
   glVertex2i(20, 60);
   glColor3f(1 ,0.5, 0.5);
   glVertex2i(40, 60);
   glColor3f(1, 0.2, 0.47);
   glVertex2i(40, 50);
   glColor3f(1, 0.73, 0.6);
   glVertex2i(60, 40);
   glColor3f(0.9, 0.9, 0);
   glVertex2i(60, 20);
   glColor3f(0, 0.6, 0);
   glVertex2i(40, 10);
   glColor3f(0.3, 1, 0.76);
   glVertex2i(40, 0);
   glColor3f(0.4, 1, 1);
   glVertex2i(20, 0);
   glColor3f(0, 0.32, 0.8);
   glVertex2i(20, 10);
   glColor3f(0.67, 0, 0.9);
   glVertex2i(0, 20);
   glColor3f(0.8, 0, 0);
   glVertex2i(0, 40);
   glColor3f(1, 0.6, 0);
   glVertex2i(20, 50);
   glEnd();
   glPopMatrix ( );
   glPopMatrix ( );

   glutSwapBuffers();
   glFlush ( );
}

void reshape(int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(-20.0, 780.0, 0.0, 600.0, -1.0, 1.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

void miscad (void)
{
	i = i + alpha;
  if ( i > 750.0 )
	  alpha = -1.0;
  else if ( i < 0.0 )
		alpha = 1.0;
  j = j + 5.0;
  Sleep(10);
  glutPostRedisplay ( );
}

void miscas (void)
{
	i = i + alpha;
  if ( i < 0.0 )
	  alpha = 1.0;
  else if ( i > 750.0 )
		alpha = -1.0;
  j = j + 5.0;
  Sleep(10);

  glutPostRedisplay ( );
}
void mouse(int button, int state, int x, int y)
{
   switch (button) {
      case GLUT_LEFT_BUTTON:
         if (state == GLUT_DOWN)
            alpha = -1.0; glutIdleFunc(miscas);
         break;
      case GLUT_RIGHT_BUTTON:
         if (state == GLUT_DOWN)
            alpha = 1.0; glutIdleFunc(miscad);
         break;
      default:
         break;
   }
}


int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize (800, 600);
   glutInitWindowPosition (100, 100);
   glutCreateWindow ("Patrat care se rostogoleste");
   init ();
   glutDisplayFunc(deseneazaScena);
   glutReshapeFunc(reshape);
   glutMouseFunc(mouse);
   glutMainLoop();
}





