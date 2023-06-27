#include "transImpl.h"

class Sprite : public TransformImpl
{
 public:
  Sprite(size_t side = 40, size_t x = 0, size_t y = 0, size_t value = 0, size_t blockSide = 10, size_t maxTextures= 20) :
    side{side},
    x{x},
    y{y},
    mValue{value},
    mBlockSide{blockSide},
    mMaxTextures{maxTextures}
  {
    r = 1.0;
    g = 0.0;
    b = 0.0;
  }

  // Implements fluent builder pattern.
  Sprite& paint();
  Sprite& randColor();
  Sprite& paintValue();
  Sprite& setColor(float r, float g, float b);
  Sprite& setTexture(int row, int column);
  Position2D getPos();
 private:
  size_t side;
  float r,g,b;
  float u0,u1,v0,v1;
  size_t x, y;
  size_t mValue;
  size_t mBlockSide;
  size_t mMaxTextures;
};
