#ifndef GAME_TOOLS_H
#define GAME_TOOLS_H

#include <aio.h>
#include <vector>
#include <iostream>
#include <iomanip>

enum class SpriteAnimationDirection {OPEN,CLOSE};
enum class SpriteDirection {LEFT,UP,RIGHT,DOWN};
enum class SpriteMove {HORIZONTAL,VERTICAL};

constexpr static int NO_LIMIT = -1;

/// @brief 2D position limit class
///
/// NO_LIMIT (-1) means ignore limit
/// Limit check is in Position2D class
struct Limit2D
{
  Limit2D(int x, int y) : x{x}, y{y}
  {
  }

  int x;
  int y;
};

/// @brief 2D position class
///
/// Chech if the limits are reched with
/// bool LimitReached(Limit2D limit)
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

SpriteDirection InverseDir(SpriteDirection dir);

#endif
