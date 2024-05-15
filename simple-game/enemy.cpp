#include "enemy.h"

void Enemy::setBehaviour(size_t behavior)
{
  std::function<void()> behaviour0 = [this]()
  {
    size_t screenX, screenY;
    getPixelPos(screenX, screenY);
    if ( screenX < 200)
    {
      setPixelPos(screenX + 1, screenY);

      // Debug. Remove later.
      Position2D pos = getPos();
      std::cout << "Enemy sceen x = " << screenX
                << " pos.x = " << pos.x << std::endl;
    }
  };

  std::function<void()> behaviour1 = [this]()
  {

  };

  std::function<void()> behaviour2 = [this]()
  {

  };

  std::function<void()> behaviour3 = [this]()
  {

  };

  switch(behavior)
  {
   case 0:
     run = behaviour0;
     mPathQueue.push(SpriteDirection::LEFT);
     mPathQueue.push(SpriteDirection::DOWN);
     mPathQueue.push(SpriteDirection::RIGHT);
     mPathQueue.push(SpriteDirection::UP);
     break;
   case 1:
     run = behaviour1;
     break;
   case 2:
     run = behaviour2;
     break;
   case 3:
     run = behaviour3;
     break;
  }
}
