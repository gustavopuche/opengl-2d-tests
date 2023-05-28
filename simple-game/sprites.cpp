#include "sprites.h"
#include <GL/glut.h>

void Sprite::paint()
{
  glEnable(GL_TEXTURE_2D);
  glBegin(GL_QUADS);
  glColor3f(r,g,b);
  glTexCoord2f(1  , 1);  glVertex2f(0+x,0+y);
  glTexCoord2f(0.5, 1);  glVertex2f(side+x,0+y);
  glTexCoord2f(0.5, 0);  glVertex2f(side+x,side+y);
  glTexCoord2f(1  , 0);  glVertex2f(0+x,side+y);
  glEnd();
  glDisable(GL_TEXTURE_2D);
}

void Sprite::setTexture()
{
}

void Sprite::setColor(float r, float g, float b)
{
  this->r = r;
  this->g = g;
  this->b = b;
}
