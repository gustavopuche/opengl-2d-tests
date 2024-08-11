#ifndef ENEMY_H
#define ENEMY_H
#include "sprites.h"
#include <functional>
#include <queue>

class Enemy : public Sprite
{
 public:
  Enemy(Screen &screen,
        size_t side = 40,
        size_t x = 0,
        size_t y = 0,
        size_t value = 0,
        size_t blockSide = 40,
        size_t maxTextures= 20) :
    Sprite(screen, side, x, y, value, blockSide, maxTextures)
  {
  }

  void   setBehaviour(size_t behavior);
  Enemy& moveEnemy(){run(); return *this;}
  void   addNewDir(SpriteDirection dir);

 private:
  std::function<void()> run;
  size_t mBehavior;
  std::stack<SpriteDirection> mPathStack;

};
#endif // ENEMY_H
