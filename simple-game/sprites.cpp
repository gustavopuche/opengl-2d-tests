#include "sprites.h"
#include <GL/glut.h>

// Debug. remove later.
#include <iostream>
//////////////////////////////////////////////////////////////////////

void Sprite::paint()
{
  glEnable(GL_TEXTURE_2D);
  glBegin(GL_QUADS);
  glColor3f(r,g,b);
  glTexCoord2f(u1  , v1);  glVertex2f(0+x,0+y);
  glTexCoord2f(u0, v1);  glVertex2f(side+x,0+y);
  glTexCoord2f(u0, v0);  glVertex2f(side+x,side+y);
  glTexCoord2f(u1  , v0);  glVertex2f(0+x,side+y);
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

// Todo calcualte this using an Interface.
void Sprite::setTexture (int row,int column,int maxTextures)
{
  u0 = 0.0 + column * 1.0 / maxTextures;
  u1 = u0 + 1.0 / maxTextures;
  v0 = 0.0 + row * 1.0 / maxTextures;
  v1 = v0 + 1.0 / maxTextures;

  // Debug. Remove later.
  std::cout << "(" << u0 << "," << u1 << "," << v0 << "," << v1 << ")"<< std::endl;
  //////////////////////////////////////////////////////////////////////
}
