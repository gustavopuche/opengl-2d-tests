#include "transImpl.h"

class Sprite : public TransformImpl
{
 public:
  Sprite(size_t side = 40, size_t x = 0, size_t y = 0, size_t value = 0, size_t blockSide = 40, size_t maxTextures= 20) :
    side{side},
    x{x},
    y{y},
    mValue{value},
    mBlockSide{blockSide},
    mMaxTextures{maxTextures},
    mMainColor{ColorRGB(1.0,0.0,0.0)},
    mValueColor1{ColorRGB(1.0,0.0,0.0)},
    mValueColor2{ColorRGB(1.0,0.0,0.0)}
  {
    mMainColor   = PredefinedColors::get().randColor();
    mValueColor1 = PredefinedColors::get().randColor();
    mValueColor2 = PredefinedColors::get().randColor();
  }

  // Implements fluent builder pattern.
  Sprite& paint();
  Sprite& paintValue();
  Sprite& setColor(float r, float g, float b);
  Sprite& setTexture(int row, int column);
  Position2D getPos();
  size_t getValue(){return mValue;};
 private:
  size_t side;
  ColorRGB mMainColor;
  ColorRGB mValueColor1;
  ColorRGB mValueColor2;
  float u0,u1,v0,v1;
  size_t x, y;
  size_t mValue;
  size_t mBlockSide;
  size_t mMaxTextures;
};
