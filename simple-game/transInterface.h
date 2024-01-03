#ifndef TRANS_IMPL_H
#define TRANS_IMPL_H

#include "gameTools.h"

class TransformInterface
{
 public:
  virtual Position2D transformPos(size_t x, size_t y, size_t limit) = 0;
  virtual Position2D screenPos(size_t x, size_t y, size_t blockSide) = 0;
};

#endif
