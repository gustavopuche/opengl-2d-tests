#include "sprites.h"
#include <vector>

struct Position2D
{
  Position2D(size_t x, size_t y) : x{x}, y{y}
  {
  }

  size_t x;
  size_t y;
};

class SerieFactory
{
 public:
  SerieFactory(std::vector<std::vector<size_t>> map, size_t x = 0, size_t y = 0, size_t blockside = 10, size_t spriteside = 40) :
    mMap{map},
    mMapSide{map.size()},
    mBlockSide{blockside},
    mSpriteSide{spriteside},
    x{x},
    y{y}
  {
    r = 1.0;
    g = 1.0;
    b = 1.0;

    mBlockPerSprite = mSpriteSide / mBlockSide;
    generate();
  }

  void paint();
 private:
  std::vector<Sprite> mVectorSerie;
  std::vector<std::vector<size_t>> mMap;
  std::vector<Position2D> mVisit;
  size_t mSpriteSide;
  size_t mMapSide;
  size_t mBlockSide;
  size_t mBlockPerSprite;
  float r,g,b;
  size_t x, y;

  void generate();
  void addNeighborgs(size_t x, size_t y);
  void addElem(size_t x, size_t y);
  void emptyVisit();
};
