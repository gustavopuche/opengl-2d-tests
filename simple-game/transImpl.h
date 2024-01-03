#ifndef TRANS_INTERFACE_H
#define TRANS_INTERFACE_H

#include "transInterface.h"

class TransformImpl : public TransformInterface
{
 public:
  Position2D transformPos(size_t x, size_t y, size_t limit)
  {
    return Position2D(x,limit - 1 - y);
  }

  virtual Position2D screenPos(size_t x, size_t y, size_t blockSide)
  {
    return Position2D(x * blockSide, y * blockSide);
  }
};

#endif
