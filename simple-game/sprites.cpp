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
  glColor3f(mMainColor.r,mMainColor.g,mMainColor.b);
  glTexCoord2f(u1, v1);  glVertex2f(0+pos.x,0+pos.y);
  glTexCoord2f(u0, v1);  glVertex2f(side+pos.x,0+pos.y);
  glTexCoord2f(u0, v0);  glVertex2f(side+pos.x,side+pos.y);
  glTexCoord2f(u1, v0);  glVertex2f(0+pos.x,side+pos.y);
  glEnd();
  glDisable(GL_TEXTURE_2D);

  return *this;
}

Sprite &Sprite::setFPS(size_t fps)
{
  mFPS = fps;

  return *this;
}

Sprite& Sprite::setFame(size_t frame)
{
  // if (mFrame > frame)
  // {
  //   mCurrentAnimation = 0;
  // }
  // else
  // {
  //   size_t frame2Change = mFPS / mMaxAnimationFrames;

  //   if ( frame % frame2Change == 0)
  //   {
  //     mCurrentAnimation++;
  //   }
  // }
  mFrame = frame;
  calculateAnimation();

  return *this;
}

Sprite& Sprite::setPixelPos (size_t xpixel,size_t ypixel)
{
  mXpixel = xpixel;
  mYpixel = ypixel;

  return *this;
}

Sprite& Sprite::setDirection(SpriteDirection direction)
{
  mCurrentSpriteDirection = direction;

  return *this;
}

Sprite& Sprite::paintAnimationFrame()
{
  float lu0, lu1,lv0,lv1;

  // Animation Frame texture.
  lu0 = 0.0 + mCurrentAnimation * 1.0 / mMaxTextures;
  lu1 = lu0 + 1.0 / mMaxTextures;
  lv0 = 0.0 + mTexRow * 1.0 / mMaxTextures;
  lv1 = lv0 + 1.0 / mMaxTextures;

  glEnable(GL_TEXTURE_2D);
  glBegin(GL_QUADS);
  glColor3f(mMainColor.r,mMainColor.g,mMainColor.b);
  switch(mCurrentSpriteDirection){
  case SpriteDirection::LEFT:
    glTexCoord2f(lu1, lv1); glVertex2f(0+mXpixel,0+mYpixel);
    glTexCoord2f(lu0, lv1); glVertex2f(side+mXpixel,0+mYpixel);
    glTexCoord2f(lu0, lv0); glVertex2f(side+mXpixel,side+mYpixel);
    glTexCoord2f(lu1, lv0); glVertex2f(0+mXpixel,side+mYpixel);
    break;
  case SpriteDirection::RIGHT:
    glTexCoord2f(lu0, lv1); glVertex2f(0+mXpixel,0+mYpixel);
    glTexCoord2f(lu1, lv1); glVertex2f(side+mXpixel,0+mYpixel);
    glTexCoord2f(lu1, lv0); glVertex2f(side+mXpixel,side+mYpixel);
    glTexCoord2f(lu0, lv0); glVertex2f(0+mXpixel,side+mYpixel);
    break;
  case SpriteDirection::UP:
    glTexCoord2f(lu0, lv0); glVertex2f(0+mXpixel,0+mYpixel);
    glTexCoord2f(lu0, lv1); glVertex2f(side+mXpixel,0+mYpixel);
    glTexCoord2f(lu1, lv1); glVertex2f(side+mXpixel,side+mYpixel);
    glTexCoord2f(lu1, lv0); glVertex2f(0+mXpixel,side+mYpixel);
    break;
  case SpriteDirection::DOWN:
    glTexCoord2f(lu1, lv0); glVertex2f(0+mXpixel,0+mYpixel);
    glTexCoord2f(lu1, lv1); glVertex2f(side+mXpixel,0+mYpixel);
    glTexCoord2f(lu0, lv1); glVertex2f(side+mXpixel,side+mYpixel);
    glTexCoord2f(lu0, lv0); glVertex2f(0+mXpixel,side+mYpixel);
    break;
  }
  glEnd();
  glDisable(GL_TEXTURE_2D);

  return *this;
}

void Sprite::calculateAnimation()
{
  size_t speedFactor = 3;
  if (mFrame % ((mFPS / speedFactor) / mMaxAnimationFrames) == 0)
  {
    switch (mSpriteAnimDir){
      case SpriteAnimationDirection::OPEN:
        if (mCurrentAnimation == (mMaxAnimationFrames - 1))
        {
          mSpriteAnimDir = SpriteAnimationDirection::CLOSE;
          mCurrentAnimation--;
        }
        else
        {
          mCurrentAnimation++;
        }
        break;
     case SpriteAnimationDirection::CLOSE:
       if (mCurrentAnimation == 0)
       {
         mSpriteAnimDir = SpriteAnimationDirection::OPEN;
         mCurrentAnimation++;
       }
       else
       {
         mCurrentAnimation--;
       }
       break;
    }
  }
}

// Paint value in internal quads.
Sprite& Sprite::paintValue()
{
  Position2D pos = screenPos(x, y, mBlockSide);
  size_t x0, x1,y0,y1;
  size_t units, tens;
  units = mValue % 10;
  tens  = (mValue% 100) / 10;

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

    glEnable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);
    glColor3f(mValueColor1.r,mValueColor1.g,mValueColor1.b);
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

  glEnable(GL_TEXTURE_2D);
  glBegin(GL_QUADS);
  glColor3f(mValueColor2.r,mValueColor2.g,mValueColor2.b);
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
  mMainColor.r = r;
  mMainColor.g = g;
  mMainColor.b = b;

  return *this;
}

// Todo calcualte this using an Interface.
Sprite& Sprite::setTexture (int row,int column)
{
  mTexRow = row;
  mTexColumn = column;

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

void Sprite::setPos(size_t x, size_t y)
{

  this->x = x;
  this->y = y;
}
