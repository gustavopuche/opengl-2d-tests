#include "gameTools.h"
#include <random>

ColorRGB& PredefinedColors::randColor()
{
  size_t iRandom = rand() % 10;

  return mPredefined[iRandom];
}
