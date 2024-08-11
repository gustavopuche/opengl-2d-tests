#ifndef SPRITE_H
#define SPRITE_H
#include "transImpl.h"
#include "screens.h"

class Sprite : public TransformImpl
{
 public:
  Sprite(Screen &screen, size_t side = 40, size_t x = 0, size_t y = 0, size_t value = 0, size_t blockSide = 40, size_t maxTextures= 20) :
    mScreen{screen},
    mSide{side},
    mX{x},
    mY{y},
    mValue{value},
    mBlockSide{blockSide},
    mMaxTextures{maxTextures},
    mMainColor{ColorRGB(1.0,1.0,1.0)},
    mValueColor1{ColorRGB(1.0,0.0,0.0)},
    mValueColor2{ColorRGB(1.0,0.0,0.0)},
    mCurrentAnimation{0},
    mMaxAnimationFrames{3},
    mFPS(60),
    mFrame(0),
    mCurrentSpriteDirection{SpriteDirection::LEFT},
    mSpriteAnimDir{SpriteAnimationDirection::OPEN}
  {
    // mMainColor   = PredefinedColors::get().randColor();
    mValueColor1 = PredefinedColors::get().randColor();
    mValueColor2 = PredefinedColors::get().randColor();
  }

  // Implements fluent builder pattern.
  Sprite& paint();
  Sprite& paintAnimationFrame();
  Sprite& paintValue();
  Sprite& setColor(float r, float g, float b);
  Sprite& setTexture(int row, int column);
  Sprite& setPixelPos(size_t xpixel, size_t ypixel);
  Sprite& setDirection(SpriteDirection direction);
  Sprite& setFPS(size_t fps);
  Sprite& setFame(size_t frame);
  Sprite& advance();
  Sprite& getPixelPos(size_t& xpixel, size_t& ypixel);

  Position2D getPos();
  Position2D getOffsets();
  void setPos(size_t x, size_t y);
  size_t getValue(){return mValue;};
  void setAnimation(size_t anim){mCurrentAnimation = anim;};
  void setMaxAnimation(size_t anim){mMaxAnimationFrames = anim;};

  bool Collision(SpriteDirection dir);
  Screen                    mScreen;

 private:
  size_t                    mSide;             // Sprite side in pixels
  ColorRGB                  mMainColor;
  ColorRGB                  mValueColor1;
  ColorRGB                  mValueColor2;
  float                     mU0,mU1,mV0,mV1;
  size_t                    mX,mY;
  size_t                    mXoffset,mYoffset;
  size_t                    mXpixel,mYpixel;
  size_t                    mValue;
  size_t                    mBlockSide;        // Map block side in pixels
  size_t                    mTexRow;
  size_t                    mTexColumn;
  size_t                    mMaxTextures;
  size_t                    mCurrentAnimation;
  size_t                    mMaxAnimationFrames;
  size_t                    mFPS;
  size_t                    mFrame;
  SpriteDirection           mCurrentSpriteDirection;
  SpriteAnimationDirection  mSpriteAnimDir;

  void calculateAnimation();
};
#endif
