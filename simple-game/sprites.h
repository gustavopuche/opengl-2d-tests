#include "transImpl.h"

class Sprite : public TransformImpl
{
 public:
  Sprite(size_t side = 40, size_t x = 0, size_t y = 0, size_t value = 0, size_t blockSide = 10) :
    side{side},
    x{x},
    y{y},
    mValue{value},
    mBlockSide{blockSide}
  {
    r = 1.0;
    g = 0.0;
    b = 0.0;
  }
  void paint();
  void setColor(float r, float g, float b);
  void setTexture(int row, int column, int maxTextures);
 private:
  size_t side;
  float r,g,b;
  float u0,u1,v0,v1;
  size_t x, y;
  size_t mValue;
  size_t mBlockSide;
};
