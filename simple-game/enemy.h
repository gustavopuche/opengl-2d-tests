#ifndef ENEMY_H
#define ENEMY_H
#include "sprites.h"
#include <functional>

class Enemy : public Sprite
{
 public:
  Enemy(size_t side = 40, size_t x = 0, size_t y = 0, size_t value = 0, size_t blockSide = 40, size_t maxTextures= 20) :
    Sprite(side, x, y, value, blockSide, maxTextures)
  {
  }

  void setBehaviour(size_t behavior);
  Enemy& moveEnemy(){run(); return *this;}
 private:
  std::function<void()> run;

};
#endif // ENEMY_H
