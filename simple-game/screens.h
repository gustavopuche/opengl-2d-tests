#ifndef SCREEN_H
#define SCREEN_H

#include "transImpl.h"
#include <vector>

class Screen : public TransformImpl
{
 public:
  Screen(std::vector<std::vector<size_t>> map, size_t blockside = 40) :
    mMap{map},
    mMapSide{map.size()},
    mBlockSide{blockside}
  {
    r = 1.0;
    g = 0.0;
    b = 1.0;
    mTextureInBlock = false;
  }
  void paint();
  void setColor(float r, float g, float b);
  void setTexture(int row, int column, int maxTextures);
  void setWall(size_t x, size_t y);
  bool inLimits(size_t x, size_t y); // True if x and y are in map bounds.
  bool getPos(size_t x, size_t y); // True means there is a wall and false there is a hole.
  size_t getSide(){return mMap.size();}
  size_t getValue(size_t x, size_t y);
  void setValue(size_t x, size_t y, size_t value);
  void dump();

 private:
  // Position2D transformPos(size_t x, size_t y);

  std::vector<std::vector<size_t>> mMap;
  size_t                           mMapSide;
  size_t                           mBlockSide;
  bool                             mTextureInBlock;
  float                            r,g,b;
  float                            u0,u1,v0,v1;
};
#endif
