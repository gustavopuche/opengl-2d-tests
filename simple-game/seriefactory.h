#include "sprites.h"
#include <vector>

class SerieFactory
{
 public:
  SerieFactory(std::vector<std::vector<int>> map, int side = 16, int x = 0, int y = 0) :
    mMap{map},
    mSide{side},
    x{x},
    y{y}
  {
    r = 1.0;
    g = 1.0;
    b = 1.0;

    generate();
  }

  void paint();
 private:
  std::vector<Sprite> mVectorSerie;
  std::vector<std::vector<int>> mMap;
  int mSide;
  float r,g,b;
  int x, y;

  void generate();
};
