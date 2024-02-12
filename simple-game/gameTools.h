#ifndef GAME_TOOLS_H
#define GAME_TOOLS_H

#include <aio.h>
#include <vector>
#include <iostream>
#include <iomanip>

struct Position2D
{
  Position2D(size_t x, size_t y) : x{x}, y{y}
  {
  }

  size_t x;
  size_t y;
};

struct ColorRGB
{
  ColorRGB(float r, float g, float b) : r{r},g{g},b{b}
  {
  }

  float r,g,b;

};

class PredefinedColors
{
 protected:
  PredefinedColors()
  {
    mPredefined = {ColorRGB(1.0,0.1,0.1),ColorRGB(1.0,1.0,0.5),
      ColorRGB(0.5,1.0,1.0),ColorRGB(0.2,0.9,0.2),
      ColorRGB(1.0,0.2,1.0),ColorRGB(0.6,1.0,0.6),
      ColorRGB(1.0,1.0,1.0),ColorRGB(0.5,0.8,0.9),
      ColorRGB(1.0,0.8,0.0),ColorRGB(0.6,0.6,1.0)};
  }

 public:
  static PredefinedColors& get()
  {
    static PredefinedColors instance;
    return instance;
  }

  ColorRGB& randColor();

 private:
  std::vector<ColorRGB> mPredefined;
};

// Dump container<container <elemtype>>
template <typename T>
void dump(const T& container)
{
  for (const auto& inner : container)
  {
    for (const auto& x : inner)
    {
      std::cout << std::right << std::setw(6) << x;
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

#endif
