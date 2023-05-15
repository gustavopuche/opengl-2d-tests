#include <GL/glut.h>
#include <stdlib.h>
#include<iostream>

using namespace std;

// Global variables to move the object.
float xr = 0, yr = 0;

void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(0 ,0 ,1);

  glBegin(GL_QUADS);
  glVertex2f(200+xr,100+yr);
  glVertex2f(300+xr,100+yr);
  glVertex2f(300+xr,200+yr);
  glVertex2f(200+xr,200+yr);
  glEnd();

  glFlush();
  glutPostRedisplay();
  glutSwapBuffers();
}

void specialKey(int key, int x, int y)
{
  switch(key){
   case GLUT_KEY_UP: // when the up key is pressed.
     yr++;
     cout << y << endl;
     glutPostRedisplay();
     break;
   case GLUT_KEY_DOWN: // when the down key is pressed.
     yr--;
     cout << y << endl;
     glutPostRedisplay();
     break;
   case GLUT_KEY_LEFT: // when the left key is pressed.
     xr--;
     cout << x << endl;
     glutPostRedisplay();
     break;
   case GLUT_KEY_RIGHT: // thwn the right key is pressed.
     xr++;
     cout << x << endl;
     break;
  }
}

int main(int argc, char** argv)
{
  cout << "Use arrow keys..." << endl;

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(400, 400);
  glutInitWindowPosition(600, 50);
  glutCreateWindow("sIMPle gAMe!");

  glutDisplayFunc(display); // display callback function.

  glClearColor(0,1,0,0);
  gluOrtho2D(0.0,400,0.0,400);
  glutSpecialFunc(specialKey); // kayboard callback function.

  glutMainLoop();
  return 0;
}
