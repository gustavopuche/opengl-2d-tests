#include "gameTools.h"
#include <random>

ColorRGB& PredefinedColors::randColor()
{
  size_t iRandom = rand() % 10;

  return mPredefined[iRandom];
}

SpriteDirection InverseDir(SpriteDirection dir)
{
  SpriteDirection inverse = SpriteDirection::LEFT;

  switch(dir)
  {
   case SpriteDirection::LEFT:
     inverse = SpriteDirection::RIGHT;
     break;
   case SpriteDirection::RIGHT:
     inverse = SpriteDirection::LEFT;
     break;
   case SpriteDirection::UP:
     inverse = SpriteDirection::DOWN;
     break;
   case SpriteDirection::DOWN:
     inverse = SpriteDirection::UP;
     break;
  }

  return inverse;
}
