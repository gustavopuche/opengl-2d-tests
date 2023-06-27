#include "sprites.h"
#include <GL/glut.h>
#include <random>

// Debug. remove later.
#include <iostream>
//////////////////////////////////////////////////////////////////////

Sprite& Sprite::paint()
{
  Position2D pos = screenPos(x, y, mBlockSide);

  glEnable(GL_TEXTURE_2D);
  glBegin(GL_QUADS);
  glColor3f(r,g,b);
  glTexCoord2f(u1  , v1);  glVertex2f(0+pos.x,0+pos.y);
  glTexCoord2f(u0, v1);  glVertex2f(side+pos.x,0+pos.y);
  glTexCoord2f(u0, v0);  glVertex2f(side+pos.x,side+pos.y);
  glTexCoord2f(u1  , v0);  glVertex2f(0+pos.x,side+pos.y);
  glEnd();
  glDisable(GL_TEXTURE_2D);

  return *this;
}

// Paint value in internal quads.
Sprite& Sprite::paintValue()
{
  Position2D pos = screenPos(x, y, mBlockSide);
  size_t x0, x1,y0,y1;
  size_t units, tens;
  units = mValue % 10;
  tens  = mValue / 10;

  float lu0, lu1,lv0,lv1;
  size_t row = 1;

  if (tens > 0)
  {
    // Tens texture.
    lu0 = 0.0 + tens * 1.0 / mMaxTextures;
    lu1 = lu0 + 1.0 / mMaxTextures;
    lv0 = 0.0 + row * 1.0 / mMaxTextures;
    lv1 = lv0 + 1.0 / mMaxTextures;

    x0 = 10; x1 = 20;
    y0 = 10; y1 = 30;

    randColor();

    glEnable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);
    glColor3f(r,g,b);
    glTexCoord2f(lu0, lv1);  glVertex2f(x0+pos.x,y0+pos.y);
    glTexCoord2f(lu1, lv1);  glVertex2f(x1+pos.x,y0+pos.y);
    glTexCoord2f(lu1, lv0);  glVertex2f(x1+pos.x,y1+pos.y);
    glTexCoord2f(lu0, lv0);  glVertex2f(x0+pos.x,y1+pos.y);
    glEnd();
    glDisable(GL_TEXTURE_2D);
  }

  // Unit texture.
  lu0 = 0.0 + units * 1.0 / mMaxTextures;
  lu1 = lu0 + 1.0 / mMaxTextures;
  lv0 = 0.0 + row * 1.0 / mMaxTextures;
  lv1 = lv0 + 1.0 / mMaxTextures;

  x0 = 20; x1 = 30;
  y0 = 10; y1 = 30;

  randColor();

  glEnable(GL_TEXTURE_2D);
  glBegin(GL_QUADS);
  glColor3f(r,g,b);
  glTexCoord2f(lu0, lv1);  glVertex2f(x0+pos.x,y0+pos.y);
  glTexCoord2f(lu1, lv1);  glVertex2f(x1+pos.x,y0+pos.y);
  glTexCoord2f(lu1, lv0);  glVertex2f(x1+pos.x,y1+pos.y);
  glTexCoord2f(lu0, lv0);  glVertex2f(x0+pos.x,y1+pos.y);
  glEnd();
  glDisable(GL_TEXTURE_2D);

  return *this;
}

Sprite& Sprite::setColor(float r, float g, float b)
{
  this->r = r;
  this->g = g;
  this->b = b;

  return *this;
}

// Todo calcualte this using an Interface.
Sprite& Sprite::setTexture (int row,int column)
{
  u0 = 0.0 + column * 1.0 / mMaxTextures;
  u1 = u0 + 1.0 / mMaxTextures;
  v0 = 0.0 + row * 1.0 / mMaxTextures;
  v1 = v0 + 1.0 / mMaxTextures;

  return *this;
}

Position2D Sprite::getPos()
{
  return Position2D(x,y);
}

Sprite &Sprite::randColor()
{
  r = (float)(1.0 / ((rand() % 100) + 1.0));
  g = (float)(1.0 / ((rand() % 100) + 1.0));
  b = (float)(1.0 / ((rand() % 100) + 1.0));

  return *this;
}
