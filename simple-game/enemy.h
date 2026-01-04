#ifndef ENEMY_H
#define ENEMY_H
#include "sprites.h"
#include <functional>
#include <queue>

using PathLimit = std::pair<SpriteDirection, Limit2D>;

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
  Enemy& setHeroData(Sprite hero);
  void   resetPathStack();
  void   addNewDir(PathLimit path);
  bool   LimitReached(PathLimit path);
  bool   isHeroVisible(Position2D pos);

 private:
  std::function<void()>  run;
  size_t                 mBehavior;
  std::stack<PathLimit>  mPathStack;
  Position2D             mHeroPos{0,0};
  SpriteDirection        mHeroDirection{SpriteDirection::LEFT};
  SpriteDirection        mChaseDirection{SpriteDirection::LEFT};
  bool                   mHeroVisible{false};
};
#endif // ENEMY_H
