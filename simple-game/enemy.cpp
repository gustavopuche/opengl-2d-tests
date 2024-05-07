#include "enemy.h"

void Enemy::setBehaviour(size_t behavior)
{
  std::function<void()> behaviour0 = [this]()
  {
    Position2D pos = getPos();
    if ( pos.x < 40)
    {
      setPos(pos.x + 1, pos.y);

      // Debug. Remove later.
      std::cout << "Enemy pos x = " << pos.x << std::endl;
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
