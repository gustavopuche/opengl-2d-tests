#include <GL/glut.h>
#include <stdlib.h>
#include<iostream>
#include<array>

using namespace std;

// Global variables to move the object.
float xr = 0, yr = 0;

array<array<int,10>,10> gameMap = {{
  {1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,1,1,1,1,1},
  {1,0,0,0,0,1,1,1,1,1},
  {1,0,0,0,0,1,1,1,1,1},
  {1,0,0,0,0,1,1,1,1,1},
  {1,1,1,1,1,1,1,1,1,1}
  }};

void paintBlock(void)
{
  glBegin(GL_QUADS);
  glColor3f(1 ,0.5 ,0);
  glVertex2f(0,0);
  glVertex2f(10,0);
  glVertex2f(10,10);
  glVertex2f(0,10);
  glEnd();

}

void paintMap(void)
{
  for (int y=0; y < 10; y++)
    for (int x=0; x < 10; x++)
    {
      if (gameMap[x][9-y] == 1)
      {
	glPushMatrix();
	glTranslatef(10*x,10*y,0);
	paintBlock();
	glPopMatrix();
      }
    }
}

void paintSprite(void)
{
  glBegin(GL_QUADS);
  glColor3f(1 ,1 ,0);
  glVertex2f(0+xr,0+yr);
  glVertex2f(40+xr,0+yr);
  glVertex2f(40+xr,40+yr);
  glVertex2f(0+xr,40+yr);
  glEnd();
}

void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT);
  // glMatrixMode(GL_MODELVIEW);      // To operate on Model-View matrix
  // glLoadIdentity();                // Reset the model-view matrix

  paintSprite();

  paintMap();

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
  glutInitWindowPosition(50, 50);
  glutCreateWindow("sIMPle gAMe!");

  glutDisplayFunc(display); // display callback function.

  glClearColor(0,0,0,0);
  gluOrtho2D(0.0,400,0.0,400);
  glutSpecialFunc(specialKey); // kayboard callback function.

  glutMainLoop();
  return 0;
}
